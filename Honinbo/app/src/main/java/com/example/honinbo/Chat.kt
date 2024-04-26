
package com.example.honinbo

import android.annotation.SuppressLint
import android.os.Bundle
import android.service.autofill.FillEventHistory
import android.view.View
import android.widget.Button
import android.widget.EditText
import android.widget.FrameLayout
import android.widget.ImageButton
import android.widget.ImageView
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import androidx.core.content.ContextCompat
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import com.example.honinbo.game.GameState
import com.example.honinbo.game.Network
import com.google.firebase.database.ChildEventListener
import com.google.firebase.database.DataSnapshot
import com.google.firebase.database.DatabaseError
import com.google.firebase.database.FirebaseDatabase
import java.util.UUID

class Chat : AppCompatActivity() {
    private lateinit var adapter: MessageAdapter
    private lateinit var messageList: MutableList<Message>
    private lateinit var recyclerView: RecyclerView
    private lateinit var messageInput: EditText
    private lateinit var sendButton: Button
    private var currentMessageId: String? = null
    private var currentPageId: String = "page1"
    //private val pageIds = mutableListOf("page1", "page2", "page3")
    private var pageSize = 0
    private var currentPageIndex = 0
    private var itemId = 0
    private var sgfstr: String? = null
    private var network = Network()

    private val gameState = GameState()
    private var gameHistoryStep = 0
    private val optPrevious = "previous"
    private val optNext = "next"
    private val optInit = "init"

    private lateinit var previousPageButton: ImageButton
    private lateinit var nextPageButton: ImageButton
    private lateinit var curr_player_info: TextView
    private lateinit var step_cnt: TextView
    private lateinit var step: TextView
    private lateinit var win_rate_info: TextView

    private val boardSize = 19
    private val Black: Int = 0
    private val White: Int = 1
    private val Empty: Int = 2
    private val Invalid: Int = 3
    // 維護一個棋盤上所有棋子的引用的二維陣列
    private val stoneImageViews = Array(boardSize) { arrayOfNulls<ImageView>(boardSize) }
    private val winRateHistory = arrayOfNulls<Int>(999)

    val senderId = UUID.randomUUID().toString()

    private val childEventListener = object : ChildEventListener {
        override fun onChildAdded(snapshot: DataSnapshot, previousChildName: String?) {
            val message = snapshot.getValue(Message::class.java)?.copy(id = snapshot.key!!)
            message?.let {
                messageList.add(it)
                adapter.notifyItemInserted(messageList.size - 1)
                recyclerView.scrollToPosition(messageList.size - 1)
            }
        }

        override fun onChildChanged(snapshot: DataSnapshot, previousChildName: String?) {}
        override fun onChildRemoved(snapshot: DataSnapshot) {}
        override fun onChildMoved(snapshot: DataSnapshot, previousChildName: String?) {}
        override fun onCancelled(error: DatabaseError) {}
    }

    @SuppressLint("MissingInflatedId")
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.chat)

        itemId = intent.getIntExtra("ID", 0)
        sgfstr = intent.getStringExtra("sgfstr")
        sgfstr?.let { gameState.fromSgfString(it) }

        pageSize = gameState.getMoveNumber() + 1
        messageList = mutableListOf()
        adapter = MessageAdapter(currentPageId, messageList) { message ->
            showMessageDiscussion(message)
        }
        recyclerView = findViewById(R.id.recyclerView)
        messageInput = findViewById(R.id.messageInput)
        sendButton = findViewById(R.id.sendButton)

        recyclerView.layoutManager = LinearLayoutManager(this)
        recyclerView.adapter = adapter

        sendButton.setOnClickListener {
            val messageText = messageInput.text.toString()
            if (messageText.isNotBlank()) {
                if (currentMessageId != null) {
                    sendReplyToFirebase(messageText, currentMessageId!!)
                } else {
                    sendMessageToFirebase(Message("", messageText, senderId, globalName))
                }
                messageInput.setText("")
            }
        }

        previousPageButton = findViewById(R.id.previousPageButton)
        nextPageButton = findViewById(R.id.nextPageButton)
        curr_player_info = findViewById(R.id.curr_player_info)
        step_cnt = findViewById(R.id.step_cnt)
        step = findViewById(R.id.step)
        win_rate_info = findViewById(R.id.win_rate_info)

        previousPageButton.setOnClickListener {
            if (gameHistoryStep > 0) {
                getPreviousPageId()
                switchPage(opt = optPrevious)
            }
        }

        nextPageButton.setOnClickListener {
            if (gameHistoryStep < gameState.getMoveNumber()) {
                getNextPageId()
                switchPage(opt = optNext)
            }
        }

        winRateHistory[0] = 0

        //listenForMessages(currentPageId)
        switchPage(opt=optInit)
        network.loadWeights(applicationContext)
    }
    private fun getImageResourceId(pageId: String): Int {
        val resourceName = "$pageId"
        return resources.getIdentifier(resourceName, "drawable", packageName)
    }
//    fun addNewPage(pageId: String) {
//        pageIds.add(pageId)
//    }
    private fun getPreviousPageId() {
        currentPageIndex = if (currentPageIndex > 0) currentPageIndex - 1 else pageSize - 1
        //return pageIds[currentPageIndex]
        return
    }

    private fun getNextPageId() {
        currentPageIndex = (currentPageIndex + 1) % pageSize
        //return pageIds[currentPageIndex]
        return
    }

    private fun drawBoard() {
        val frameLayout = findViewById<FrameLayout>(R.id.imageViewBoardLayout_border_play_rec)
        val board = gameState.gameHistory[gameHistoryStep]

        frameLayout.post {
            for (i in 0 until 19) {
                for (j in 0 until 19) {
                    // 檢查並移除舊的棋子
                    stoneImageViews[i][j]?.let {
                        frameLayout.removeView(it)
                        stoneImageViews[i][j] = null
                    }

                    // 根據 gameState 添加新的棋子
                    if (board.state[gameState.getVertex(i, j)] != Empty) {
                        val stone = ImageView(this).apply {
                            val stoneSize = frameLayout.width / 19
                            layoutParams = FrameLayout.LayoutParams(stoneSize, stoneSize)
                            x = i * stoneSize.toFloat()
                            y = j * stoneSize.toFloat()

                            when (board.state[gameState.getVertex(i, j)]) {
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

    @SuppressLint("SetTextI18n")
    private fun switchPage(opt: String) {
        //currentPageId = pageId
        /*val imageView: ImageView = findViewById(R.id.imageView)
        val imageResId = getImageResourceId(pageId)
        if (imageResId != 0) {
            imageView.setImageResource(imageResId)
        } else {
            imageView.setImageResource(R.drawable.page1)  // 找不到用默認圖片
        }*/

        if (opt != optInit)
        {
            if (opt == optPrevious)
            {
                gameHistoryStep -= 1
            }
            else if (opt == optNext)
            {
                gameHistoryStep += 1
            }
        }

        val board = gameState.gameHistory[gameHistoryStep]

        if (gameHistoryStep % 2 == 1)
        {
            curr_player_info.text = "白"
            curr_player_info.setTextColor(ContextCompat.getColor(this, R.color.white))
        } else
        {
            curr_player_info.text = "黑"
            curr_player_info.setTextColor(ContextCompat.getColor(this, R.color.black))
        }

        step_cnt.text = "$gameHistoryStep."

        step.text = gameState.vertexToText(board.lastMove); // board.getX(board.lastMove).toString() + "/" + board.getY(board.lastMove).toString()

        val currGameState = GameState()
        currGameState.resetBoard(gameState.getBoardSize(), gameState.getKomi())
        for (i in 1 until gameHistoryStep + 1) {
            currGameState.playMove(gameState.gameHistory[i].lastMove, currGameState.getToMove())
        }

        var winRate: Int

        if (winRateHistory[gameHistoryStep] == null)
        {
            winRate = (100.0f * network.analyze(currGameState)).toInt()
            winRateHistory[gameHistoryStep] = winRate
        }
        else
        {
            winRate = winRateHistory[gameHistoryStep]!!
        }
        win_rate_info.text = "$winRate%"

        if(gameHistoryStep == 0)
        {
            curr_player_info.text = "黑"
            curr_player_info.setTextColor(ContextCompat.getColor(this, R.color.black))
            step.text = "---"
            win_rate_info.text = "44%"

            val frameLayout = findViewById<FrameLayout>(R.id.imageViewBoardLayout_border_play_rec)

            frameLayout.post {
                for (i in 0 until 19)
                    for (j in 0 until 19)
                        stoneImageViews[i][j]?.let {
                            frameLayout.removeView(it)
                            stoneImageViews[i][j] = null
                        }
            }
        }

        drawBoard()

        // 清除現有的監聽器
        //val databaseReference = FirebaseDatabase.getInstance().getReference("pages/$currentPageId")
        val databaseReference = FirebaseDatabase.getInstance().getReference("messages/$itemId/$currentPageIndex")
        databaseReference.removeEventListener(childEventListener)

        messageList.clear() // 清除就頁面的 message
        adapter.notifyDataSetChanged() // 通知 adapter
        listenForMessages() // 監聽新頁面
    }

    override fun onBackPressed() {
        // 檢查當前是否有 fragment 顯示
        if (supportFragmentManager.backStackEntryCount > 0) {
            currentMessageId = null
            super.onBackPressed() // 讓系統處理 fragment 的返回操作
            recyclerView.visibility = View.VISIBLE // 顯示 RecyclerView
            findViewById<FrameLayout>(R.id.fragment_container).visibility = View.GONE // 隱藏 fragment

            previousPageButton.isEnabled = true
            nextPageButton.isEnabled = true
        } else {
            finish()
        }
    }

    private fun showMessageDiscussion(message: Message) {
        currentMessageId = message.id
        val fragment = MessageDiscussionFragment().apply {
            arguments = Bundle().apply {
                putString("messageId", message.id)
                putString("messageText", message.text)
                putString("messageName", message.name)
                putString("currentPageId", currentPageId)
                putInt("currentPageIndex", currentPageIndex)
                putInt("itemId", itemId)
            }
        }

        previousPageButton.isEnabled = false
        nextPageButton.isEnabled = false

        supportFragmentManager.beginTransaction()
            .replace(R.id.fragment_container, fragment)
            .addToBackStack(null)
            .commit()

        recyclerView.visibility = View.GONE // 隐藏 RecyclerView
        findViewById<FrameLayout>(R.id.fragment_container).visibility = View.VISIBLE // 显示 Fragment 容器
    }
    private fun sendReplyToFirebase(replyText: String, messageId: String) {
        val replyId = UUID.randomUUID().toString()
        val reply = mapOf(
            "text" to replyText,
            "senderId" to senderId,
            "name" to globalName
        )

        val databaseReference = FirebaseDatabase.getInstance()
            .getReference("messages/$itemId/$currentPageIndex/$messageId/replies/$replyId")

        databaseReference.setValue(reply)
    }
    private fun sendMessageToFirebase(message: Message) {
        val databaseReference = FirebaseDatabase.getInstance().getReference("messages/$itemId/$currentPageIndex")
        databaseReference.push().setValue(message)
    }

    private fun listenForMessages() {
        val databaseReference = FirebaseDatabase.getInstance().getReference("messages/$itemId/$currentPageIndex")
        databaseReference.addChildEventListener(childEventListener)
    }
}
