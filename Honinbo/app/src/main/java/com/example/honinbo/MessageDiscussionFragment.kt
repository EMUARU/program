
package com.example.honinbo

import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import androidx.fragment.app.Fragment
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import com.google.firebase.database.ChildEventListener
import com.google.firebase.database.DataSnapshot
import com.google.firebase.database.DatabaseError
import com.google.firebase.database.FirebaseDatabase

class MessageDiscussionFragment : Fragment() {
    private var messageId: String? = null
    private var messageText: String? = null
    private var messageName: String? = null
    private var currentPageId: String? = null
    private var currentPageIndex: Int? = 0
    private var itemId: Int? = 0
    private val repliesList = mutableListOf<Reply>()
    private lateinit var repliesAdapter: ReplyAdapter
    fun setMessageText(text: String) {
        messageText = text
    }
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        messageId = arguments?.getString("messageId")
        messageText = arguments?.getString("messageText")
        messageName = arguments?.getString("messageName")
        currentPageId = arguments?.getString("currentPageId")
        currentPageIndex = arguments?.getInt("currentPageIndex")
        itemId = arguments?.getInt("itemId")
    }
    override fun onCreateView(inflater: LayoutInflater, container: ViewGroup?, savedInstanceState: Bundle?): View? {
        // Inflate the layout for this fragment
        val view = inflater.inflate(R.layout.fragment_message_discussion, container, false)
        view.findViewById<TextView>(R.id.messageTextViewName).text = messageName + " : "
        view.findViewById<TextView>(R.id.messageTextView).text = messageText

        val repliesRecyclerView = view.findViewById<RecyclerView>(R.id.repliesRecyclerView)
        repliesAdapter = ReplyAdapter(repliesList)
        repliesRecyclerView.layoutManager = LinearLayoutManager(context)
        repliesRecyclerView.adapter = repliesAdapter

        listenForReplies()

        return view
    }

    private fun listenForReplies() {
        // 您需要修改此方法以侦听 Firebase 数据库中的回复数据
        // 参考之前的步骤中 listenForReplies() 方法的实现
        messageId?.let { messageId ->
            val repliesRef = FirebaseDatabase.getInstance().getReference("messages/$itemId/$currentPageIndex/$messageId/replies")
            repliesRef.addChildEventListener(object : ChildEventListener {
                override fun onChildAdded(snapshot: DataSnapshot, previousChildName: String?) {
                    val reply = snapshot.getValue(Reply::class.java)
                    reply?.let {
                        repliesList.add(it)
                        repliesAdapter.notifyItemInserted(repliesList.size - 1)
                    }
                }

                override fun onChildChanged(snapshot: DataSnapshot, previousChildName: String?) {
                    TODO("Not yet implemented")
                }

                override fun onChildRemoved(snapshot: DataSnapshot) {
                    TODO("Not yet implemented")
                }

                override fun onChildMoved(snapshot: DataSnapshot, previousChildName: String?) {
                    TODO("Not yet implemented")
                }

                override fun onCancelled(error: DatabaseError) {
                    TODO("Not yet implemented")
                }
                // 实现其他 ChildEventListener 方法...
            })
        }
    }
}
