package com.example.honinbo

var globalName: String = ""
// var itemIndex: Int = 0
data class Message(val id: String = "", val text: String = "", val senderId: String = "", val name: String = "")
data class Reply(val id: String = "", val text: String = "", val senderId: String = "", val name: String = "")
data class Account(val name: String = "", val email: String = "", val password: String = "")
data class Page(val pageId: String = "", val pageTitle: String = "")
data class Item(val id: Int = 0, val item: String = "")
data class ItemModel(
    val id: Int,
    val name: String,
    val time: String,
    val moves: String,
    val winner: String,
    val sgfstr: String
)