package com.example.honinbo

import android.os.Bundle
import android.util.Log
import android.widget.Toast
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Surface
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.tooling.preview.Preview
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import com.example.honinbo.game.GameState
import com.example.honinbo.ui.theme.HoninboTheme
import com.google.firebase.database.ChildEventListener
import com.google.firebase.database.DataSnapshot
import com.google.firebase.database.DatabaseError
import com.google.firebase.database.FirebaseDatabase

class Analyze : ComponentActivity() {
    private lateinit var items: MutableList<ItemModel>

    private lateinit var recyclerView: RecyclerView
    private lateinit var adapter: MyAdapter

    private val databaseReference = FirebaseDatabase.getInstance().getReference("messages")

    private fun convertItemToItemModel(item: String, itemId: Int): ItemModel {
        val gameState = GameState()
        gameState.fromSgfString(item)

        val winner = gameState.getWinner()
        var winnerStr = ""
        when (winner)
        {
            0 -> winnerStr = "先手"
            1 -> winnerStr = "後手"
            3 -> winnerStr = "----"
        }

        return ItemModel(itemId, gameState.getGameName(), gameState.getDate(),
                         gameState.getMoveNumber().toString(), winnerStr, item)
    }

    private val parentEventListener = object : ChildEventListener {
        override fun onChildAdded(snapshot: DataSnapshot, previousChildName: String?) {
            for (childSnapshot in snapshot.children) {
                val itemString = childSnapshot.child("item").getValue(String::class.java)
                val itemId = childSnapshot.child("id").getValue(Int::class.java)

                if (itemString != null && itemId != null) {
                    Log.d("Analyze", "Item string: $itemString")
                    val itemModel = convertItemToItemModel(itemString, itemId)
                    items.add(itemModel)
                    adapter.notifyItemInserted(items.size - 1)
                    recyclerView.scrollToPosition(0)
                } else {
                    Log.d("Analyze", "Failed to get item or id from child snapshot")
                }
            }
        }
        override fun onChildChanged(snapshot: DataSnapshot, previousChildName: String?) {}
        override fun onChildRemoved(snapshot: DataSnapshot) {}
        override fun onChildMoved(snapshot: DataSnapshot, previousChildName: String?) {}
        override fun onCancelled(error: DatabaseError) {}
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.analyze)

        recyclerView = findViewById(R.id.listRecyclerView)
        recyclerView.layoutManager = LinearLayoutManager(this)

        items = mutableListOf()

        adapter = MyAdapter(items)
        recyclerView.adapter = adapter

        databaseReference.addChildEventListener(parentEventListener)
    }
}