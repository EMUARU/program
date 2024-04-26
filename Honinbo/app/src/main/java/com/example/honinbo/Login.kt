package com.example.honinbo

import android.content.Intent
import android.os.Bundle
import android.widget.Button
import android.widget.EditText
import android.widget.Toast
import androidx.activity.ComponentActivity
import com.google.firebase.database.DataSnapshot
import com.google.firebase.database.DatabaseError
import com.google.firebase.database.DatabaseReference
import com.google.firebase.database.FirebaseDatabase
import com.google.firebase.database.ValueEventListener

class Login : ComponentActivity() {
    private lateinit var database: DatabaseReference
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.login)

        val btnLogin = findViewById<Button>(R.id.btnLogin)
        val btnRegister = findViewById<Button>(R.id.btnRegister)

        val email = findViewById<EditText>(R.id.lgEmail)
        val password = findViewById<EditText>(R.id.lgPassword)

        database = FirebaseDatabase.getInstance().getReference("accounts")

        btnLogin.setOnClickListener {
            val emailText = email.text.toString()
            val passwordText = password.text.toString()
            if (emailText.isNotBlank() && passwordText.isNotBlank()) {
                validateAccount(emailText, passwordText) { accountExists ->
                    if (accountExists) {
                        val intent = Intent(this, Index::class.java)
                        startActivity(intent)
                    }
                }
            }
        }

        btnRegister.setOnClickListener {
            // 跳轉到註冊頁面
            val intent = Intent(this, Register::class.java)
            startActivity(intent)
        }
    }

    private fun validateAccount(account: String, password: String, callback: (Boolean) -> Unit) {
        database.addListenerForSingleValueEvent(object : ValueEventListener {
            override fun onDataChange(dataSnapshot: DataSnapshot) {
                var accountExists = false

                for (accountSnapshot in dataSnapshot.children) {
                    val email = accountSnapshot.child("email").getValue(String::class.java)
                    val password1 = accountSnapshot.child("password").getValue(String::class.java)
                    var nickName = accountSnapshot.child("name").getValue(String::class.java)

                    if (email.equals(account, ignoreCase = true) && password1.equals(password)) {
                        Toast.makeText(this@Login, "Login successful", Toast.LENGTH_SHORT).show()
                        globalName = nickName.toString();
                        accountExists = true
                        break
                    }
                }
                if (accountExists)
                    callback(accountExists)

                if (!accountExists) {
                    Toast.makeText(this@Login, "Account does not exist or invalid password", Toast.LENGTH_SHORT).show()
                    callback(false)
                }
            }

            override fun onCancelled(databaseError: DatabaseError) {
                Toast.makeText(this@Login, "Error: ${databaseError.message}", Toast.LENGTH_SHORT).show()
                callback(false)
            }
        })
    }
}