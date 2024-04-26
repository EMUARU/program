package com.example.honinbo.game

import android.icu.text.RelativeDateTimeFormatter.RelativeDateTimeUnit
import java.time.LocalDate
import java.time.LocalDateTime
import java.util.Vector
import kotlin.concurrent.thread

class GameState() {
    var gameHistory: Vector<Board> = Vector<Board>()
    var koHistory: Vector<Int> = Vector<Int>()
    var board: Board = Board()
    private var playersName: Array<String> = arrayOf("player1", "player2")
    private var moveNumber: Int = 0
    private var winner: Int = this.board.Invalid
    private var date: String = ""
    private var gameName : String = ""

    init {
        clearBoard()
    }

    fun clearBoard() {
        resetBoard(getBoardSize(), getKomi())
    }

    fun resetBoard(boardSize: Int, komi: Float) {
        this.board.reset(boardSize, komi)
        this.gameHistory.clear()
        this.gameHistory.add(this.board.deepCopy())
        this.koHistory.clear()
        this.koHistory.add(this.board.computeHash())
        this.moveNumber = 0
        this.date = ""
        this.winner = this.board.Invalid
        this.playersName[this.board.Black] = "player1"
        this.playersName[this.board.White] = "player2"
        this.gameName = ""
    }

    fun undoMove() {
        if (this.moveNumber <= 0) return

        while (this.gameHistory.size > this.moveNumber) {
            this.gameHistory.removeAt(this.gameHistory.size-1)
        }
        this.moveNumber -= 1
        this.board = this.gameHistory[this.moveNumber].deepCopy()
        this.winner = this.board.Invalid
    }

    fun superko() : Boolean {
        val hash = board.computeHash()
        for (i in 0..this.moveNumber-2) {
            if (hash == this.koHistory[i]) {
                return true
            }
        }
        return false
    }

    fun playMove(vtx: Int, color: Int) : Boolean {
        if (!board.isLegal(vtx, color)) {
            return false
        }
        if (vtx != this.board.resignMove) {
            this.board.playMoveAssumeLegal(vtx, color)
            this.moveNumber += 1
            this.gameHistory.add(this.board.deepCopy())
            this.koHistory.add(this.board.computeHash())
        } else {
            this.winner = this.board.getOppColor(color)
        }
        return true
    }

    fun isLegal(vtx: Int, color: Int) : Boolean {
        return this.board.isLegal(vtx, color)
    }

    override fun toString(): String {
        return this.board.toString()
    }

    fun getBoardSize() : Int {
        return this.board.boardSize
    }

    fun getKomi() : Float {
        return this.board.komi
    }

    fun getVertex(x: Int, y :Int) : Int {
        return this.board.getVertex(x,y)
    }

    fun getIndex(x: Int, y :Int) : Int {
        return this.board.getIndex(x,y)
    }

    fun setKomi(komi: Float) {
        this.board.komi = komi
    }

    fun setWinner(who: Int) {
        this.winner = who
    }

    fun setPlayerName(who: Int, name: String) {
        if (who == this.board.Black || who == this.board.White) {
            this.playersName[who] = name
        }
    }

    fun setGameName(name: String) {
        this.gameName = name
    }

    fun setDate(time: String) {
        this.date = time
    }

    fun getState(vtx: Int) : Int {
        return this.board.state[vtx]
    }

    fun getToMove() : Int {
        return this.board.toMove
    }

    fun getNumPasses() : Int {
        return this.board.numPasses
    }

    fun getMoveNumber() : Int {
        return this.moveNumber
    }

    fun getPlayerName(who : Int) : String {
        return this.playersName[who]
    }

    fun getDate() : String {
        return this.date
    }

    fun getGameName() : String {
        return this.gameName
    }

    fun getWinner()  : Int{
        return this.winner
    }

    fun vertexToText(vtx: Int) : String {
        if (vtx == this.board.passMove) {
            return "PASS"
        }
        if (vtx == this.board.resignMove) {
            return "resign"
        }
        var x = this.board.getX(vtx)
        var y = this.board.getY(vtx)
        if (x >= 8) {
            x += 1
        }
        y = getBoardSize() - y
        return ('A'.code + x).toChar().toString() + y.toString()
    }

    fun TextTovertex(text: String) : Int {
        if (text == "pass" || text == "PASS") {
            return this.board.passMove
        }
        if (text == "RESIGN" || text == "resign") {
            return this.board.resignMove
        }
        val xx : Int = text[0].code - 'A'.code
        val yy : Int = text.substring(1).toInt() - 1
        return this.getVertex(xx.toInt(), yy.toInt())
    }

    fun colorToText(color: Int) : String {
        val cmap = arrayOf("B", "W", "E", "I")
        return cmap[color]
    }
    fun vertexToSgf(vtx: Int) : String {
        if (vtx == this.board.resignMove) {
            return ""
        }
        if (vtx == this.board.passMove) {
            if (getBoardSize() <= 19) {
                return "tt"
            } else {
                return ""
            }
        }
        val x = this.board.getX(vtx)
        var y = this.board.getY(vtx)
        y = getBoardSize() - 1 - y
        return ('a'.code + x).toChar().toString() + ('a'.code + y).toChar().toString()
    }

    fun sgfToVertex(sgfpos: String) : Int {
        if (sgfpos == "" || sgfpos == "tt") {
            return board.passMove
        }
        val xx = sgfpos[0].code - 'a'.code
        var yy = sgfpos[1].code - 'a'.code
        yy = getBoardSize() - 1 - yy
        return getVertex(xx, yy)
    }

    fun toSgfString() : String {
        var sgf = "(;GM[1]FF[4]"
        sgf += "SZ[" + this.getBoardSize().toString() + "]"
        sgf += "KM[" + this.getKomi().toString() + "]"
        if (this.gameName.isNotEmpty()) {
            sgf += "GN[" + this.gameName + "]"
        }
        sgf += "RU[chinese]"
        sgf += "PB[" + getPlayerName(this.board.Black) + "]"
        sgf += "PW[" + getPlayerName(this.board.White) + "]"
        if (getDate().isNotEmpty()) {
            sgf += "DT[" + getDate() + "]"
        }
        if (this.winner == this.board.Black) {
            sgf += "RE[B+Resign]"
        } else if (this.winner == this.board.White) {
            sgf += "RE[W+Resign]"
        }
        for (i in 0..this.moveNumber) {
            val currBoard = this.gameHistory[i]
            val color = board.getOppColor(currBoard.toMove)
            val vtx = currBoard.lastMove
            if (vtx != board.nullVertex) {
                sgf += ";"
                sgf += colorToText(color)
                sgf += "["
                sgf += vertexToSgf(vtx)
                sgf += "]"
            }
        }
        sgf += ")"
        return sgf
    }

    fun fromSgfString(sgf: String) {
        clearBoard()
        var level: Int = 0
        var idx: Int = 0
        var node_cnt: Int = 0
        var key: String = ""
        val size = sgf.length
        while (idx < size) {
            val c = sgf[idx]
            idx += 1

            if (c == '(') {
                level += 1
            } else if (c == ')') {
                level -= 1
            }
            if (level != 1) {
                continue
            }
            var need_skip = false
            for (skip in arrayOf('(', ')', '\t', '\n', '\r')) {
                if (c == skip) {
                    need_skip = true
                }
            }
            if (need_skip) {
                continue
            }
            if (c == ';') {
                node_cnt += 1
            } else if (c == '[') {
                val end = sgf.indexOf(']', idx)
                val value = sgf.subSequence(idx, end).toString()
                if (key == "SZ") {
                    resetBoard(value.toInt(), getKomi())
                } else if (key == "KM") {
                    resetBoard(getBoardSize(), value.toFloat())
                } else if (key == "PB") {
                    setPlayerName(board.Black, value)
                } else if (key == "PW") {
                    setPlayerName(board.White, value)
                } else if (key == "DT") {
                    setDate(value)
                } else if (key == "RE") {
                    if (value.indexOf("B+") != -1) {
                        setWinner(board.Black)
                    } else if (value.indexOf("W+") != -1) {
                        setWinner(board.White)
                    }
                } else if (key == "GN") {
                    this.gameName = value
                } else if (key == "B") {
                    playMove(sgfToVertex(value), board.Black)
                } else if (key == "W") {
                    playMove(sgfToVertex(value), board.White)
                }
                idx = end + 1
                key = ""
            } else {
                key += c.toString()
            }
        }
    }
}