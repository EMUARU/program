package com.example.honinbo

import android.content.Intent
import android.os.Bundle
import android.util.Log
import android.view.View
import android.widget.ArrayAdapter
import android.widget.Button
import android.widget.EditText
import android.widget.FrameLayout
import android.widget.ImageView
import android.widget.LinearLayout
import android.widget.Spinner
import android.widget.TextView
import android.widget.Toast
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.material3.Button
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Surface
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.runtime.remember
import androidx.compose.ui.Modifier
import androidx.compose.ui.tooling.preview.Preview
import com.example.honinbo.game.Board
import com.example.honinbo.ui.theme.HoninboTheme
import com.example.honinbo.game.GameState
import com.google.firebase.database.DataSnapshot
import com.google.firebase.database.DatabaseError
import com.google.firebase.database.FirebaseDatabase
import com.google.firebase.database.ValueEventListener
import java.util.Stack
import java.util.Vector
import java.text.SimpleDateFormat
import java.util.Calendar
import java.util.Locale

class PlayGameActivity : ComponentActivity() {
    private val Black: Int = 0
    private val White: Int = 1
    private val Empty: Int = 2
    private val Invalid: Int = 3

    private val player1: Int = 0
    private val player2: Int = 1
    private val noOne: Int = -1
    private var currPlayer: Int = noOne

    private val boardSize = 19

    private val letters = "A B C D E F G H J K L M N O P Q R S T".split(" ")
    private val letterToIndexMap = letters.withIndex().associate { it.value to it.index }

    // 維護一個棋盤上所有棋子的引用的二維陣列
    private val stoneImageViews = Array(boardSize) { arrayOfNulls<ImageView>(boardSize) }
    // 記錄哪一步被跳過
    private val skipMoveHistory = ArrayDeque<Boolean>()

    // p2 (up) part elements
    private lateinit var buttonPlayerTwoSurrender: Button
    private lateinit var buttonPlayerTwoUndo: Button
    private lateinit var buttonPlayerTwoSkip: Button

    private lateinit var playerTwoCoordinateX: Spinner
    private lateinit var playerTwoCoordinateY: Spinner
    private lateinit var buttonPlayerTwoConfirm: Button

    private lateinit var imageViewHintPlayerTwo: ImageView
    private lateinit var imageViewHintGreyPlayerTwo: ImageView

    // p1 (down) part elements
    private lateinit var buttonPlayerOneSurrender: Button
    private lateinit var buttonPlayerOneUndo: Button
    private lateinit var buttonPlayerOneSkip: Button

    private lateinit var playerOneCoordinateX: Spinner
    private lateinit var playerOneCoordinateY: Spinner
    private lateinit var buttonPlayerOneConfirm: Button

    private lateinit var imageViewHintPlayerOne: ImageView
    private lateinit var imageViewHintGreyPlayerOne: ImageView

    private lateinit var topBackground: LinearLayout
    private lateinit var recordInputFrameLayout: FrameLayout
    private lateinit var recordInputHint: TextView
    private lateinit var recordInput: EditText
    private lateinit var sendRCNameButton: Button

    private val gameState = GameState()

    fun getCurrentDateTimeString(): String {
        val calendar = Calendar.getInstance()
        calendar.add(Calendar.HOUR_OF_DAY, 8)
        val dateFormat = SimpleDateFormat("yyyy-MM-dd HH:mm", Locale.getDefault())
        return dateFormat.format(calendar.time)
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.board)
        // Toast.makeText(this, "hello", Toast.LENGTH_LONG).show()

        topBackground = findViewById<LinearLayout>(R.id.topBackground)
        recordInputFrameLayout = findViewById<FrameLayout>(R.id.recordInputFrameLayout)
        recordInputHint = findViewById<TextView>(R.id.recordInputHint)
        recordInput = findViewById<EditText>(R.id.recordInput)
        sendRCNameButton = findViewById<Button>(R.id.sendRCNameButton)

        sendRCNameButton.setOnClickListener {
            finishPlayGameActivity()
        }

        // p2 (up) part elements
        buttonPlayerTwoSurrender = findViewById<Button>(R.id.buttonPlayerTwoSurrender)
        buttonPlayerTwoUndo = findViewById<Button>(R.id.buttonPlayerTwoUndo)
        buttonPlayerTwoSkip = findViewById<Button>(R.id.buttonPlayerTwoSkip)

        playerTwoCoordinateX = findViewById<Spinner>(R.id.PlayerTwoCoordinateX)
        playerTwoCoordinateY = findViewById<Spinner>(R.id.PlayerTwoCoordinateY)
        buttonPlayerTwoConfirm = findViewById<Button>(R.id.buttonPlayerTwoConfirm)

        imageViewHintPlayerTwo = findViewById<ImageView>(R.id.imageViewHintPlayerTwo)
        imageViewHintGreyPlayerTwo = findViewById<ImageView>(R.id.imageViewHintGreyPlayerTwo)

        // p1 (down) part elements
        buttonPlayerOneSurrender = findViewById<Button>(R.id.buttonPlayerOneSurrender)
        buttonPlayerOneUndo = findViewById<Button>(R.id.buttonPlayerOneUndo)
        buttonPlayerOneSkip = findViewById<Button>(R.id.buttonPlayerOneSkip)

        playerOneCoordinateX = findViewById<Spinner>(R.id.PlayerOneCoordinateX)
        playerOneCoordinateY = findViewById<Spinner>(R.id.PlayerOneCoordinateY)
        buttonPlayerOneConfirm = findViewById<Button>(R.id.buttonPlayerOneConfirm)

        imageViewHintPlayerOne = findViewById<ImageView>(R.id.imageViewHintPlayerOne)
        imageViewHintGreyPlayerOne = findViewById<ImageView>(R.id.imageViewHintGreyPlayerOne)

        // 獲取座標數據
        val xCoordinates_p1 = resources.getStringArray(R.array.x_coordinates)
        val yCoordinates_p1 = resources.getStringArray(R.array.y_coordinates)
        val xCoordinates_p2 = resources.getStringArray(R.array.x_coordinates)
        val yCoordinates_p2 = resources.getStringArray(R.array.y_coordinates)

        // 為 Spinner 創建 ArrayAdapter
        val adapterX_p1 = ArrayAdapter(this, android.R.layout.simple_spinner_item, xCoordinates_p1)
        val adapterY_p1 = ArrayAdapter(this, android.R.layout.simple_spinner_item, yCoordinates_p1)
        val adapterX_p2 = ArrayAdapter(this, android.R.layout.simple_spinner_item, xCoordinates_p2)
        val adapterY_p2 = ArrayAdapter(this, android.R.layout.simple_spinner_item, yCoordinates_p2)

        // 指定下拉列表的樣式
        adapterX_p1.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item)
        adapterY_p1.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item)
        adapterX_p2.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item)
        adapterY_p2.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item)

        // 將 ArrayAdapter 添加到 Spinner
        playerOneCoordinateX.adapter = adapterX_p1
        playerOneCoordinateY.adapter = adapterY_p1
        playerTwoCoordinateX.adapter = adapterX_p2
        playerTwoCoordinateY.adapter = adapterY_p2
        // p1
        buttonPlayerOneSurrender.setOnClickListener {
            gameEnd(surrender = player1)
        }
        buttonPlayerOneUndo.setOnClickListener {
            undo()
        }
        buttonPlayerOneSkip.setOnClickListener {
            skip(player = player1)
        }
        buttonPlayerOneConfirm.setOnClickListener {
            tryPlayMove(player = player1)
        }
        // p2
        buttonPlayerTwoSurrender.setOnClickListener {
            gameEnd(surrender = player2)
        }
        buttonPlayerTwoUndo.setOnClickListener {
            undo()
        }
        buttonPlayerTwoSkip.setOnClickListener {
            skip(player = player2)
        }
        buttonPlayerTwoConfirm.setOnClickListener {
            tryPlayMove(player = player2)
        }

        playGame()
    }

    private fun tryPlayMove(player: Int = noOne)
    {
        var X = 0
        var Y = 0
        if (player == player1)
        {
            X = letterToIndexMap[playerOneCoordinateX.selectedItem.toString()]!!
            Y = boardSize - playerOneCoordinateY.selectedItem.toString().toInt()
        }
        else if (player == player2)
        {
            X = letterToIndexMap[playerTwoCoordinateX.selectedItem.toString()]!!
            Y = boardSize - playerTwoCoordinateY.selectedItem.toString().toInt()
        }

        if (!gameState.playMove(gameState.getVertex(X,Y), player))
            Toast.makeText(this, "Invalid Move!", Toast.LENGTH_SHORT).show()
        else
        {
            // winrate = nn.analyze(gameState)

            drawBoard()
            skipMoveHistory.addLast(false)
            newTurn()
        }
    }

    private fun playGame() {
        /*gameState.playMove(gameState.getVertex(9,9), 0);
        gameState.playMove(gameState.getVertex(16,3), 1);
        gameState.playMove(gameState.getVertex(3,16), 0);
        gameState.playMove(gameState.getVertex(0,0), 0);
        gameState.playMove(gameState.getVertex(0,18), 1);
        gameState.playMove(gameState.getVertex(18,0), 1);
        gameState.playMove(gameState.getVertex(18,18), 0);
        drawBoard()*/
        /*gameState.playMove(gameState.getVertex(0,18), 0);
        gameState.playMove(gameState.getVertex(1,18), 1);
        gameState.playMove(gameState.getVertex(1,17), 1);
        gameState.playMove(gameState.getVertex(0,17), 1);
        gameState.playMove(gameState.getVertex(0,16), 1);
        drawBoard()*/

        topBackground.visibility = View.GONE
        recordInputFrameLayout.visibility = View.GONE
        recordInputHint.visibility = View.GONE
        recordInput.visibility = View.GONE
        sendRCNameButton.visibility = View.GONE

        currPlayer = player2
        newTurn()
    }

    private fun newTurn()
    {
        currPlayer = (currPlayer + 1) % 2
        updateElementsState()
    }

    private fun drawBoard() {
        val frameLayout = findViewById<FrameLayout>(R.id.imageViewBoardLayout_border)

        frameLayout.post {
            for (i in 0 until 19) {
                for (j in 0 until 19) {
                    // 檢查並移除舊的棋子
                    stoneImageViews[i][j]?.let {
                        frameLayout.removeView(it)
                        stoneImageViews[i][j] = null
                    }

                    // 根據 gameState 添加新的棋子
                    if (gameState.board.state[gameState.getVertex(i, j)] != Empty) {
                        val stone = ImageView(this).apply {
                            val stoneSize = frameLayout.width / 19
                            layoutParams = FrameLayout.LayoutParams(stoneSize, stoneSize)
                            x = i * stoneSize.toFloat()
                            y = j * stoneSize.toFloat()

                            when (gameState.board.state[gameState.getVertex(i, j)]) {
                                Black -> setImageResource(R.drawable.goishi_black)
                                White -> setImageResource(R.drawable.goishi_white)
                            }
                        }
                        frameLayout.addView(stone)
                        stoneImageViews[i][j] = stone
                    }
                }
            }
        }
    }

    // update elements state
    private fun updateElementsState()
    {
        if (currPlayer == player1)
        {
            buttonPlayerOneSkip.isEnabled = true
            buttonPlayerOneConfirm.isEnabled = true
            imageViewHintGreyPlayerOne.visibility = View.GONE
            imageViewHintPlayerOne.visibility = View.VISIBLE

            buttonPlayerTwoSkip.isEnabled = false
            buttonPlayerTwoConfirm.isEnabled = false
            imageViewHintPlayerTwo.visibility = View.GONE
            imageViewHintGreyPlayerTwo.visibility = View.VISIBLE
        }
        else if ((currPlayer == player2))
        {
            buttonPlayerTwoSkip.isEnabled = true
            buttonPlayerTwoConfirm.isEnabled = true
            imageViewHintGreyPlayerTwo.visibility = View.GONE
            imageViewHintPlayerTwo.visibility = View.VISIBLE

            buttonPlayerOneSkip.isEnabled = false
            buttonPlayerOneConfirm.isEnabled = false
            imageViewHintPlayerOne.visibility = View.GONE
            imageViewHintGreyPlayerOne.visibility = View.VISIBLE
        }
    }

    private fun gameEnd(surrender: Int = noOne)
    {
        val frameLayout = findViewById<FrameLayout>(R.id.imageViewBoardLayout_border)

        frameLayout.post {
            for (i in 1 until 18)
                for (j in 6 until 13)
                    stoneImageViews[i][j]?.let {
                        frameLayout.removeView(it)
                        stoneImageViews[i][j] = null
                    }
        }

        when (surrender) {
            player1 -> Toast.makeText(this, "player1 surrender", Toast.LENGTH_SHORT).show()
            player2 -> Toast.makeText(this, "player2 surrender", Toast.LENGTH_SHORT).show()
            else -> Toast.makeText(this, "Game End", Toast.LENGTH_SHORT).show()
        }

        topBackground.elevation = 99F
        topBackground.isFocusable = true
        topBackground.isClickable = true

        // 在游戏结束时调用
        topBackground.apply {
            visibility = View.VISIBLE  // 设置为可见
            bringToFront()  // 将视图带到前面
            requestFocus()  // 请求焦点以阻止点击事件传递
            requestLayout()
        }

        topBackground.visibility = View.VISIBLE
        recordInputFrameLayout.visibility = View.VISIBLE
        recordInputHint.visibility = View.VISIBLE
        recordInput.visibility = View.VISIBLE
        sendRCNameButton.visibility = View.VISIBLE

        // if no surrender : 判斷贏家
        // else 輸家 = surrender
        if (surrender == player1 || surrender == player2)
            gameState.setWinner(1 - surrender)
        else
            gameState.setWinner(Invalid);

        val currentDateTimeString = getCurrentDateTimeString()
        gameState.setDate(currentDateTimeString)
        Toast.makeText(this, "currentDateTimeString: $currentDateTimeString", Toast.LENGTH_SHORT).show()
    }

    private fun undo()
    {
        // Toast.makeText(this, "undo", Toast.LENGTH_SHORT).show()
        val lastMoveSkipped =
            (if (skipMoveHistory.isNotEmpty()) skipMoveHistory.removeLast() else null)
                ?: return

        gameState.undoMove()
        drawBoard()
        newTurn()
    }

    private fun skip(player: Int)
    {
        val lastMoveSkipped = skipMoveHistory.lastOrNull()
        if (lastMoveSkipped == true)
            gameEnd()
        else
        {
            gameState.playMove(gameState.board.passMove, player)
            skipMoveHistory.addLast(true)
            newTurn()
        }
    }

    private fun finishPlayGameActivity()
    {
        val recordInputValue = recordInput.text.toString()
        //Toast.makeText(this, "RecordName: $recordInputValue", Toast.LENGTH_SHORT).show()
        gameState.setGameName(recordInputValue)

        // 將gameState資訊寫回資料庫
        val myRef = FirebaseDatabase.getInstance().getReference("itemIndex")

        val sgfStr = gameState.toSgfString()
        myRef.addListenerForSingleValueEvent(object : ValueEventListener {
            override fun onDataChange(dataSnapshot: DataSnapshot) {
                val itemIndex = dataSnapshot.getValue(Int::class.java) ?: 0

                val newItemRef = FirebaseDatabase.getInstance().getReference("messages/$itemIndex").push()
                newItemRef.setValue(Item(itemIndex, sgfStr)).addOnSuccessListener {
                    myRef.setValue(itemIndex + 1)
                }.addOnFailureListener {
                    it.printStackTrace()
                }
            }

            override fun onCancelled(databaseError: DatabaseError) {
                Log.w("TAG", "Failed to read value.", databaseError.toException())
            }
        })

        // 跳轉到其他活動
        val intent = Intent(this, Index::class.java)
        startActivity(intent)
        finish() // 結束當前活動
    }
}
