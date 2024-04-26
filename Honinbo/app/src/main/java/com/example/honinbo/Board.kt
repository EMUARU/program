package com.example.honinbo.game

import androidx.lifecycle.viewmodel.CreationExtras

class Board(var boardSize: Int = 19, var komi: Float = 7.5f) {
    val Black: Int = 0;
    val White: Int = 1;
    val Empty: Int = 2;
    val Invalid: Int = 3;
    val maxBoardSize: Int = 19;
    val maxLetterBoxSize: Int = this.maxBoardSize + 2;
    val maxNumIntersections: Int = this.maxBoardSize * this.maxBoardSize;
    val maxNumVertices: Int = this.maxLetterBoxSize * this.maxLetterBoxSize;
    val passMove: Int = this.maxNumVertices + 1;
    val resignMove: Int = this.maxNumVertices + 2;
    val nullVertex: Int = this.maxNumVertices;

    var koMove: Int = this.nullVertex;
    var toMove: Int = this.Black;
    var lastMove: Int = this.nullVertex;
    var numPasses: Int = 0;
    var letterBoxSize: Int = 0;
    var numIntersections: Int = 0;
    var numVertices: Int = 0;
    var state: IntArray = IntArray(this.maxNumVertices);
    var stringNext: IntArray = IntArray(this.maxNumVertices+1);
    var stringParent: IntArray = IntArray(this.maxNumVertices+1);
    var stringLiberties: IntArray = IntArray(this.maxNumVertices+1);
    var stringStones: IntArray = IntArray(this.maxNumVertices+1);
    var directions: IntArray = IntArray(4);

    init {
        reset(this.boardSize, this.komi);
    }

    fun reset(boardSize: Int, komi: Float) {
        assert(boardSize <= this.maxBoardSize && boardSize >= 2);
        this.koMove = this.nullVertex;
        this.toMove = this.Black;
        this.numPasses = 0;
        this.boardSize = boardSize;
        this.komi = komi;
        this.lastMove = this.nullVertex
        this.letterBoxSize = this.boardSize + 2;
        this.numIntersections = this.boardSize * this.boardSize;
        this.numVertices = this.letterBoxSize * this.letterBoxSize;

        this.directions[0] = -this.letterBoxSize;
        this.directions[1] = -1;
        this.directions[2] = 1;
        this.directions[3] = this.letterBoxSize;

        for (vtx in 0..this.maxNumVertices-1) {
            this.state[vtx] = this.Invalid;
            this.stringNext[vtx] = this.maxNumVertices;
            this.stringParent[vtx] = this.maxNumVertices;
            this.stringLiberties[vtx] = 0;
            this.stringStones[vtx] = 0;
        }
        this.stringLiberties[this.maxNumVertices] = 16384;

        for (y in 0..this.boardSize-1) {
            for (x in 0..this.boardSize-1) {
                this.state[this.getVertex(x, y)] = this.Empty;
            }
        }
    }
    fun addStone(vtx: Int, color: Int) {
        val neighborParents: Array<Int> = arrayOf<Int>(0,0,0,0);
        var cnt = 0;
        this.state[vtx] = color;
        this.stringNext[vtx] = vtx;
        this.stringParent[vtx] = vtx;
        this.stringLiberties[vtx] = 4;
        this.stringStones[vtx] = 1;

        for (k in 0..3) {
            val avtx: Int = vtx + this.directions[k];
            val ip: Int = this.stringParent[avtx];
            val neighbor = this.state[avtx];
            var found: Boolean  = false;
            if (cnt > 0) {
                for (i in 0..cnt-1) {
                    if (neighborParents[i] == ip) {
                        found = true;
                        break;
                    }
                }
            }
            if (!found) {
                this.stringLiberties[ip] -= 1;
                neighborParents[cnt++] = ip;
            }
            if (neighbor != this.Empty) {
                this.stringLiberties[vtx] -= 1;
            }
        }
    }

    fun removeStone(vtx: Int) {
        val neighborParents: Array<Int> = arrayOf<Int>(0,0,0,0);
        var cnt = 0;
        this.state[vtx] = this.Empty;

        for (k in 0..3) {
            val avtx: Int = vtx + this.directions[k];
            val ip: Int = this.stringParent[avtx];
            var found: Boolean  = false;
            if (cnt > 0) {
                for (i in 0..cnt-1) {
                    if (neighborParents[i] == ip) {
                        found = true;
                        break;
                    }
                }
            }
            if (!found) {
                this.stringLiberties[ip] += 1;
                neighborParents[cnt++] = ip;
            }
        }
    }

    fun removeString(ip: Int) : Int {
        var pos: Int = ip;
        var removed: Int = 0;
        do {
            removeStone(pos);
            this.stringParent[pos] = this.maxNumVertices;
            removed += 1;
            pos = this.stringNext[pos];
        } while (pos != ip);
        return removed;
    }

    fun mergeStrings(ip: Int, aip: Int) {
        this.stringStones[ip] += this.stringStones[aip];
        var pos: Int = aip;
        do {
            for (k in 0..3) {
                val apos: Int = pos + this.directions[k];
                if (this.state[apos] == this.Empty) {
                    var found : Boolean = false;
                    for (kk in 0..3) {
                        val aapos: Int = apos + this.directions[kk];
                        if (this.stringParent[aapos] == ip) {
                            found = true;
                            break
                        }
                    }
                    if (!found) {
                        this.stringLiberties[ip] += 1;
                    }
                }
            }
            this.stringParent[pos] = ip;
            pos = this.stringNext[pos];
        } while (pos != aip)

        val temp : Int = this.stringNext[ip];
        this.stringNext[ip] = this.stringNext[aip];
        this.stringNext[aip] = temp;
    }

    fun updateBoard(vtx: Int, color: Int) : Int {
        addStone(vtx, color);
        var capturedStones: Int = 0;
        var capturedVtx: Int = this.nullVertex;
        var isEyePlay = true;

        for (k in 0..3) {
            val avtx: Int = vtx + this.directions[k];
            val aip: Int = this.stringParent[avtx];
            val state: Int = this.state[avtx];
            if (state == getOppColor(color)) {
                if (this.stringLiberties[aip] == 0) {
                    capturedStones += removeString(avtx);
                    capturedVtx = avtx;
                }
            } else if (state == color) {
                val ip: Int = this.stringParent[vtx];
                if (ip != aip) {
                    if (this.stringStones[ip] >= this.stringStones[aip]) {
                        mergeStrings(ip, aip);
                    } else {
                        mergeStrings(aip, ip);
                    }
                }
                isEyePlay = false;
            }
        }

        if (this.stringLiberties[this.stringParent[vtx]] == 0) {
            removeString(vtx);
        }

        if (capturedStones == 1 && isEyePlay) {
            return capturedVtx;
        }

        return this.nullVertex;
    }

    fun playMoveAssumeLegal(vtx: Int, color: Int) {
        this.toMove = color;

        if (vtx == this.passMove) {
            this.numPasses += 1;
            this.koMove = this.nullVertex;
        } else {
            this.numPasses = 0;
            this.koMove = updateBoard(vtx, color);
        }
        this.lastMove = vtx;
        this.toMove = getOppColor(this.toMove);
    }

    fun isSuicide(vtx: Int, color: Int) : Boolean {
        for (k in 0..3) {
            val avtx = vtx + this.directions[k];
            val libs = this.stringLiberties[this.stringParent[avtx]];
            val state = this.state[avtx];

            if (state == this.Empty) {
                return false;
            } else if (state == color && libs > 1) {
                return false;
            } else if (state == getOppColor(color) && libs <= 1) {
                return false;
            }
        }
        return true;
    }
    fun  isLegal(vtx: Int, color: Int) : Boolean {
        if (vtx == this.passMove || vtx == this.resignMove) {
            return true;
        }
        if (this.state[vtx] != this.Empty) {
            return false;
        }
        if (isSuicide(vtx, color)) {
            return false;
        }
        if (vtx == this.koMove) {
            return false;
        }
        return true;
    }

    override fun toString(): String {
        var out: String = "";
        val xmap = arrayOf<Char>('A','B','C','D','E','F','G','H','J','K','L','M','N','O','P','Q','R','S','T');
        for (reversed_y in 0..this.boardSize-1) {
            val y = this.boardSize - reversed_y - 1;
            if ((y+1) < 10) {
                out += (" " + (y+1).toString() + " ");
            } else {
                out += ((y+1).toString() + " ");
            }
            for (x in 0..this.boardSize-1) {
                val color = this.state[this.getVertex(x, y)];
                if (color == this.Black) {
                    out += " x ";
                } else if (color == this.White) {
                    out += " o ";
                } else {
                    out += " . ";
                }
            }
            out += "\n";
        }
        out += "   "
        for (x in 0..this.boardSize-1) {
            out += (" " + xmap[x].lowercase() + " ");
        }
        out += "\n"
        return out;
    }

    fun getVertex(x: Int, y :Int) : Int {
        return (x+1) + (y+1) * this.letterBoxSize;
    }
    fun getIndex(x: Int, y :Int) : Int {
        return x + y * this.boardSize;
    }

    fun getX (vtx: Int) : Int {
        return vtx % this.letterBoxSize - 1;
    }
    fun getY (vtx: Int) : Int {
        return vtx / this.letterBoxSize - 1;
    }

    fun getOppColor(color: Int) : Int {
        if (color == this.Black) {
            return this.White;
        } else if (color == this.White) {
            return this.Black;
        }
        return color;
    }
    fun computeHash() : Int {
        var str: String = "";
        val smap = arrayOf<Char>('x','o','.','-');
        for (vtx in 0..this.maxNumVertices-1) {
            str += smap[this.state[vtx]];
        }
        return str.hashCode();
    }
    fun deepCopy() : Board {
        val board = Board(this.boardSize, this.komi);
        board.koMove = this.koMove;
        board.toMove = this.toMove;
        board.lastMove = this.lastMove;
        board.numPasses = this.numPasses;

        for (vtx in 0..this.maxNumVertices) {
            if (vtx != this.maxNumVertices) {
                board.state[vtx] = this.state[vtx];
            }
            board.stringNext[vtx] = this.stringNext[vtx];
            board.stringParent[vtx] = this.stringParent[vtx];
            board.stringLiberties[vtx] = this.stringLiberties[vtx];
            board.stringStones[vtx] = this.stringStones[vtx];
        }
        return board;
    };
}