package com.example.honinbo

import android.content.Intent
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import androidx.core.content.ContextCompat
import androidx.recyclerview.widget.RecyclerView

class MyAdapter(private val dataList: List<ItemModel>) : RecyclerView.Adapter<MyAdapter.MyViewHolder>() {

    class MyViewHolder(view: View) : RecyclerView.ViewHolder(view) {
        var textView1: TextView = view.findViewById(R.id.textView1)
        var textView2: TextView = view.findViewById(R.id.textView2)
        var textView3: TextView = view.findViewById(R.id.textView3)
        var textView4: TextView = view.findViewById(R.id.textView4)

        fun bind(item: ItemModel) {
            textView1.text = "棋譜: ${item.name}"
            textView2.text = "時間: ${item.time}"
            textView3.text = "手數: ${item.moves}"
            textView4.text = "勝者: ${item.winner}"

            itemView.setOnClickListener {
                val intent = Intent(itemView.context, Chat::class.java)
                intent.putExtra("ID", item.id)
                intent.putExtra("sgfstr", item.sgfstr)
                itemView.context.startActivity(intent)
            }
        }
    }

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): MyViewHolder {
        val itemView = LayoutInflater.from(parent.context).inflate(R.layout.item_layout, parent, false)
        return MyViewHolder(itemView)
    }

    override fun onBindViewHolder(holder: MyViewHolder, position: Int) {
        val item = dataList[dataList.size - 1 - position]
        holder.bind(item)

        if (position % 2 == 0) {
            holder.itemView.setBackgroundColor(ContextCompat.getColor(holder.itemView.context, R.color.colorEven))
        } else {
            holder.itemView.setBackgroundColor(ContextCompat.getColor(holder.itemView.context, R.color.colorOdd))
        }
    }

    override fun getItemCount() = dataList.size
}
