package com.example.honinbo

import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView

class ReplyAdapter(private val replies: List<Reply>) : RecyclerView.Adapter<ReplyAdapter.ViewHolder>() {

    class ViewHolder(view: View) : RecyclerView.ViewHolder(view) {
        val replyTextViewName: TextView = view.findViewById(R.id.replyTextViewName)
        val replyTextView: TextView = view.findViewById(R.id.replyTextView)  // 假设您的item布局里有一个TextView的id为replyTextView
    }

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): ViewHolder {
        val view = LayoutInflater.from(parent.context).inflate(R.layout.item_reply, parent, false)
        return ViewHolder(view)
    }

    override fun onBindViewHolder(holder: ViewHolder, position: Int) {
        val reply = replies[position]
        holder.replyTextViewName.text = reply.name + " : "
        holder.replyTextView.text = reply.text
    }

    override fun getItemCount() = replies.size
}