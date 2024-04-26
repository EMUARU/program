package com.example.honinbo.game

import kotlin.math.sqrt
import kotlin.math.min
import android.content.Context
import android.util.Log
import kotlin.math.exp
import kotlin.math.tanh

class Network {
    var version: Int = 0
    var planes: Int = 18
    var blocks: Int = 0
    var channels: Int = 0
    var inLayers = mutableListOf<Array<Float>>()
    var resnetTower = mutableListOf<Array<Float>>()
    var policyHead = mutableListOf<Array<Float>>()
    var valueHead = mutableListOf<Array<Float>>()

    fun loadWeights(context: Context) {
        val buf = mutableListOf<String>()
        val inputStream = context.assets.open("weights.txt")
        inputStream.bufferedReader().forEachLine {  buf.add(it) }
        this.version = buf.removeAt(0).toInt()
        this.blocks = (buf.size  - (4 + 14))/8
        this.channels = buf[1].split(" ").size

        pushInLayer(buf)
        for (i in 0 until this.blocks) {
            pushResnetTower(buf)
        }
        pushPolicyHead(buf)
        pushValueHead(buf)
    }

    fun  pushInLayer(buf: MutableList<String>) {
        for (i in 0 until 4) {
            val raw = buf.removeAt(0).split(" ")
            var weights = raw.map { it.toFloat() }.toTypedArray()
            if (i == 3) {
                weights = processBatchNormVar(weights)
            }
            this.inLayers.add(weights)
        }
    }
    fun  pushResnetTower(buf: MutableList<String>) {
        for (i in 0 until 8) {
            val raw = buf.removeAt(0).split(" ")
            var weights = raw.map { it.toFloat() }.toTypedArray()
            if (i == 3 || i == 7) {
                weights = processBatchNormVar(weights)
            }
            this.resnetTower.add(weights)
        }
    }
    fun  pushPolicyHead(buf: MutableList<String>) {
        for (i in 0 until 6) {
            val raw = buf.removeAt(0).split(" ")
            var weights = raw.map { it.toFloat() }.toTypedArray()
            if (i == 3) {
                weights = processBatchNormVar(weights)
            }
            this.policyHead.add(weights)
        }
    }
    fun  pushValueHead(buf: MutableList<String>) {
        for (i in 0 until 8) {
            val raw = buf.removeAt(0).split(" ")
            var weights = raw.map { it.toFloat() }.toTypedArray()
            if (i == 3) {
                weights = processBatchNormVar(weights)
            }
            this.valueHead.add(weights)
        }
    }
    fun processBatchNormVar(weights: Array<Float>) : Array<Float> {
        val processed = weights.map {  1.0f / sqrt(it + 1e-5f) }.toTypedArray()
        return processed
    }

    fun blasGemm(TA: Boolean, TB: Boolean,
                 M: Int, N: Int, K: Int,
                 alpha: Float,
                 A: Array<Float>, lda: Int,
                 B: Array<Float>, ldb: Int,
                 beta: Float,
                 C: Array<Float>, ldc: Int) {
        for (i in 0 until M) {
            for (j in 0 until N) {
                C[i * ldc + j] *= beta
            }
        }
        if (TA && TB) {
            for (i in 0 until M) {
                for (j in 0 until N) {
                    var sum: Float = 0.0f
                    for (k in 0 until K) {
                        sum += alpha * A[i + k * lda] * B[k + j * ldb]
                    }
                    C[i * ldc + j] += sum;
                }
            }
        }
        if (TA && !TB) {
            for (i in 0 until M) {
                for (k in 0 until K) {
                    val A_PART: Float = alpha * A[k * lda + i]
                    for (j in 0 until N) {
                        C[i * ldc + j] += A_PART * B[k * ldb + j]
                    }
                }
            }
        }
        if (!TA && TB) {
            for (i in 0 until M) {
                for (j in 0 until N) {
                    var sum: Float = 0.0f
                    for (k in 0 until K) {
                        sum += alpha * A[i * lda + k] * B[j * ldb + k]
                    }
                    C[i * ldc + j] += sum;
                }
            }
        }
        if (!TA && !TB) {
            for (i in 0 until M) {
                for (k in 0 until K) {
                    val A_PART: Float = alpha * A[i * lda + k];
                    for (j in 0 until N) {
                        C[i * ldc + j] += A_PART * B[k * ldb + j];
                    }
                }
            }
        }
    }

    fun getConvolve3WorkspaceSize(board_size: Int, in_channels: Int) : Int {
        val width = board_size
        val height = board_size
        val filter_size = 3
        val filter_len = filter_size * filter_size
        val filter_dim = filter_len * in_channels
        return filter_dim * width * height
    }

    fun convolve1(board_size: Int,
                  in_channels: Int,
                  out_channels: Int,
                  input: Array<Float>,
                  weights: Array<Float>,
                  biases: Array<Float>,
                  output: Array<Float>) {
        val width = board_size
        val height = board_size
        val spatial = width * height
        blasGemm(
            false, false,
            out_channels, spatial, in_channels,
            1.0f,
            weights, in_channels,
            input, spatial,
            0.0f,
            output, spatial)
        for (c in 0 until out_channels) {
            val bias = biases[c];
            for (s in 0 until spatial) {
                output[c * spatial + s] += bias
            }
        }
    }

    fun im2col(board_size: Int,
               channels: Int,
               input: Array<Float>,
               output: Array<Float>) {
        val filter_size: Int = 3
        val width: Int = board_size
        val height: Int = board_size
        val spatial: Int = width * height

        val pad: Int = filter_size / 2;
        val output_h: Int = height + 2 * pad - filter_size + 1;
        val output_w: Int = width + 2 * pad - filter_size + 1;

        var data_im_idx: Int = 0
        var data_col_idx: Int = 0

        for (c in 0 until channels) {
            for (kernel_row in 0 until filter_size) {
                for (kernel_col in 0 until filter_size) {
                    var input_row = -pad + kernel_row
                    for (output_rows in 0 until output_h) {
                        if (input_row < height && input_row >= 0) {
                            var input_col = -pad + kernel_col;
                            for (output_col in 0 until output_w) {
                                if (input_col < width && input_col >= 0) {
                                    output[data_col_idx++] = input[data_im_idx + input_row * width + input_col];
                                } else {
                                    output[data_col_idx++] = 0.0f;
                                }
                                input_col++;
                            }
                        } else {
                            for (output_col in 0 until output_w) {
                                output[data_col_idx++] = 0.0f;
                            }
                        }
                        input_row++;
                    }
                }
            }
            data_im_idx += spatial
        }
    }

    fun convolve3(board_size: Int,
                  in_channels: Int,
                  out_channels: Int,
                  input: Array<Float>,
                  weights: Array<Float>,
                  biases: Array<Float>,
                  col: Array<Float>,
                  output: Array<Float>) {
        val filter_size = 3
        val width = board_size
        val height = board_size
        val spatial = width * height
        val filter_len = filter_size * filter_size;
        val filter_dim = filter_len * in_channels;

        im2col(board_size, in_channels, input, col);
        blasGemm(
            false, false,
            out_channels, spatial, filter_dim,
            1.0f,
            weights, filter_dim,
            col, spatial,
            0.0f,
            output, spatial)
        for (c in 0 until out_channels) {
            val bias = biases[c];
            for (s in 0 until spatial) {
                output[c * spatial + s] += bias
            }
        }
    }

    fun batchNorm(board_size: Int,
                  channels: Int,
                  input: Array<Float>,
                  means: Array<Float>,
                  stddevs: Array<Float>) {
        val ReLU = true
        val width = board_size
        val height = board_size
        val spatial = width * height

        for (c in 0 until channels) {
            val mean = means[c]
            val stddev = stddevs[c]
            for (s in 0 until spatial) {
                var value = input[c * spatial + s]
                value = stddev * (value - mean);
                if (value < 0.0f && ReLU) {
                    value = 0.0f
                }
                input[c * spatial + s] = value
            }
        }
    }

    fun batchNormMerge(board_size: Int,
                       channels: Int,
                       input: Array<Float>,
                       means: Array<Float>,
                       stddevs: Array<Float>,
                       residual: Array<Float>) {
        val ReLU = true
        val width = board_size
        val height = board_size
        val spatial = width * height

        for (c in 0.. channels-1) {
            val mean = means[c]
            val stddev = stddevs[c]
            for (s in 0.. spatial-1) {
                var value = input[c * spatial + s]
                value = stddev * (value - mean)
                value += residual[c * spatial + s]
                if (value < 0.0f && ReLU) {
                    value = 0.0f
                }
                residual[c * spatial + s] = value
            }
        }
    }

    fun Innerproduct(in_size: Int,
                     out_size: Int,
                     input: Array<Float>,
                     weights: Array<Float>,
                     biases: Array<Float>,
                     ReLU: Boolean) : Array<Float> {
        val output: Array<Float> = Array<Float>(out_size) { 0.0f }
        blasGemm(
            false, true,
            1, out_size, in_size,
            1.0f,
            input, in_size,
            weights, in_size,
            0.0f,
            output, out_size)
        for (i in 0 until out_size) {
            output[i] += biases[i]
            if (output[i] < 0.0f && ReLU) {
                output[i] = 0.0f
            }
        }
        return output
    }

    fun softmax(logits: Array<Float>) : Array<Float> {
        val out_size = logits.size
        val output: Array<Float> = Array<Float>(out_size) { 0.0f }

        var alpha: Float = logits[0]
        var denom: Float = 0.0f;
        for (i in 0 until out_size) {
            if (logits[i] > alpha) {
                alpha = logits[i]
            }
        }
        for (i in 0 until out_size) {
            val value = exp(logits[i] - alpha)
            denom += value
            output[i] = value
        }
        for (i in 0 until out_size) {
            output[i] /= denom
        }
        return output;
    }

    fun getFeatures(state: GameState) : Array<Float> {
        val boardSize = state.getBoardSize()
        val spatial = boardSize * boardSize
        val features: Array<Float> = Array<Float>(this.planes * spatial) { 0.0f }

        var blackIdx = 0
        var whiteIdx = 0
        var toMoveIdx = 0
        if (state.getToMove() == state.board.Black) {
            whiteIdx += 8 * spatial
            toMoveIdx = 16 * spatial
        } else {
            blackIdx += 8 * spatial
            toMoveIdx = 17 * spatial
        }

        val past = min(state.gameHistory.size, 8)
        val last = state.gameHistory.size - 1
        for (p in 0 until past) {
            val board = state.gameHistory[last - p]
            for (idx in 0 until spatial) {
                val x = idx % boardSize;
                val y = idx / boardSize;
                val vtx = state.getVertex(x,y)
                val color = board.state[vtx]
                if (color == board.Black) {
                    features[blackIdx + p * spatial + idx] = 1.0f
                } else if (color == state.board.White) {
                    features[whiteIdx + p * spatial + idx] = 1.0f
                }
            }
        }
        for (idx in 0 until spatial) {
            features[toMoveIdx + idx] = 1.0f
        }
        return features
    }

    fun forward(state: GameState) : Pair<Array<Float>, Array<Float>> {
        val boardSize = state.getBoardSize()
        val spatial = boardSize * boardSize
        val features = getFeatures(state)

        val workspace = Array<Float>(10 * getConvolve3WorkspaceSize(boardSize, this.channels)) { 0.0f }
        val convBuf1 = Array<Float>(this.channels * spatial) { 0.0f }
        val convBuf2 = Array<Float>(this.channels * spatial) { 0.0f }
        val convBuf3 = Array<Float>(this.channels * spatial) { 0.0f }
        val polBuf = Array<Float>(2 * spatial) { 0.0f }
        val valBuf = Array<Float>(1 * spatial) { 0.0f }

        // input layer
        convolve3(
            boardSize, this.planes, this.channels,
            features, this.inLayers[0], this.inLayers[1],
            workspace, convBuf1)
        batchNorm(
            boardSize, this.channels, convBuf1,
            this.inLayers[2], this.inLayers[3])

        // resnet tower
        for (b in 0 until this.blocks) {
            val towerOffset = 8 * b;
            convolve3(
                boardSize, this.channels, this.channels,
                convBuf1, this.resnetTower[towerOffset + 0],
                this.resnetTower[towerOffset + 1], workspace, convBuf2)
            batchNorm(
                boardSize, this.channels, convBuf2,
                this.resnetTower[towerOffset + 2],
                this.resnetTower[towerOffset + 3])

            convolve3(
                boardSize, this.channels, this.channels,
                convBuf2, this.resnetTower[towerOffset + 4],
                this.resnetTower[towerOffset + 5], workspace, convBuf3)
            batchNormMerge(
                boardSize, this.channels, convBuf3,
                this.resnetTower[towerOffset + 6],
                this.resnetTower[towerOffset + 7],
                convBuf1)
        }

        // policy head
        convolve1(
            boardSize, this.channels, 2, convBuf1,
            this.policyHead[0], this.policyHead[1], polBuf)
        batchNorm(
            boardSize, 2, polBuf,
            this.policyHead[2], this.policyHead[3])
        var polOuput = Innerproduct(
            2 * spatial, spatial+1, polBuf,
            this.policyHead[4], this.policyHead[5], false)
        polOuput = softmax(polOuput)

        // value head
        convolve1(
            boardSize, this.channels, 1, convBuf1,
            this.valueHead[0], this.valueHead[1], valBuf)
        batchNorm(
            boardSize, 1, valBuf,
            this.valueHead[2], this.valueHead[3])
        val valMiddel = Innerproduct(
            spatial, 256, valBuf,
            this.valueHead[4], this.valueHead[5], true)
        val valOuput = Innerproduct(
            256, 1, valMiddel,
            this.valueHead[6], this.valueHead[7], false)
        valOuput[0] = tanh(valOuput[0])
        if (this.version == 2 && state.getToMove() == state.board.Black) {
            valOuput[0] = 1.0f - valOuput[0]
        }

        return Pair(polOuput, valOuput)
    }

    fun dummyForward(state: GameState) : Pair<Array<Float>, Array<Float>>{
        val boardSize = state.getBoardSize()
        val spatial = boardSize * boardSize

        var polOuput: Array<Float> = Array<Float>(spatial + 1) { 0.0f }
        val valOuput: Array<Float> = Array<Float>(1) { 0.0f }

        polOuput = softmax(polOuput)
        valOuput[0] = tanh(valOuput[0])
        return Pair(polOuput, valOuput)
    }

    fun getResult(state: GameState) : Pair<Array<Float>, Array<Float>> {
        val boardSize = state.getBoardSize()
        val spatial = boardSize * boardSize

        var pair = dummyForward(state)
        if (this.version != 0) {
            // version 0: dummy
            // version 1: leelaz
            // version 2: elf
            pair = forward(state)
        }

        val policy = pair.first
        val winrate = pair.second

        var legasSum: Float = 0.0f
        for (idx in 0 until spatial) {
            val x = idx % boardSize;
            val y = idx / boardSize;
            val vtx = state.getVertex(x, y)
            val color = state.getToMove()
            if (state.isLegal(vtx, color)) {
                legasSum += policy[idx]
            } else {
                policy[idx] = 0.0f
            }
        }
        legasSum += policy[spatial]

        for (idx in 0 until spatial+1) {
            policy[idx] /= legasSum
        }
        return Pair(policy, winrate)
    }

    fun analyze(state: GameState) : Float {
        val pair = getResult(state)
        return (1.0f + pair.second[0]) / 2.0f
    }
}