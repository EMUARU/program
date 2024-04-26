package com.example.honinbo

import android.content.Intent
import android.os.Bundle
import android.widget.Button
import android.widget.EditText
import android.widget.Toast
import androidx.activity.ComponentActivity
import com.google.firebase.database.DataSnapshot
import com.google.firebase.database.DatabaseError
import com.google.firebase.database.FirebaseDatabase
import com.google.firebase.database.ValueEventListener


class Register : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.register)

        val btnRegister = findViewById<Button>(R.id.btnRegister)
        val nickName = findViewById<EditText>(R.id.etNickname)
        val email = findViewById<EditText>(R.id.etEmail)
        val password = findViewById<EditText>(R.id.etPasswordRegister)
        val confirmPassword = findViewById<EditText>(R.id.etConfirmPassword)

        btnRegister.setOnClickListener {
            val nickNameText = nickName.text.toString()
            val emailText = email.text.toString()
            val passwordText = password.text.toString()
            val confirmPasswordText = confirmPassword.text.toString()
            if (nickNameText.isNotBlank() && emailText.isNotBlank() && passwordText.isNotBlank() && confirmPasswordText.isNotBlank()) {
                checkAccount(emailText) { accountExists ->
                    if (!accountExists) {
                        handleBtnRegister(nickNameText, emailText, passwordText, confirmPasswordText)
                    } else {
                        Toast.makeText(this, "帳號已存在", Toast.LENGTH_SHORT).show()
                    }
                }
            }
        }
    }

    private fun handleBtnRegister(nickNameText: String, emailText: String, passwordText: String, confirmPasswordText: String) {
        if (passwordText != confirmPasswordText) {
            Toast.makeText(this, "密碼不相符", Toast.LENGTH_SHORT).show();
            return
        }

        val databaseReference = FirebaseDatabase.getInstance().getReference("accounts")
        databaseReference.push().setValue(Account(nickNameText, emailText, passwordText))

        Toast.makeText(this, "註冊成功", Toast.LENGTH_SHORT).show()

        val intent = Intent(this, Login::class.java)
        startActivity(intent)
    }

    private fun checkAccount(account: String, callback: (Boolean) -> Unit) {
        val database = FirebaseDatabase.getInstance().getReference("accounts")
        database.addListenerForSingleValueEvent(object : ValueEventListener {
            override fun onDataChange(dataSnapshot: DataSnapshot) {
                var accountExists = false
                for (accountSnapshot in dataSnapshot.children) {
                    val email = accountSnapshot.child("email").getValue(String::class.java)

                    if (email == account) {
                        accountExists = true
                        break
                    }
                }
                callback(accountExists)
            }

            override fun onCancelled(databaseError: DatabaseError) {
                Toast.makeText(this@Register, "Error: ${databaseError.message}", Toast.LENGTH_SHORT).show()
                callback(false)
            }
        })
    }
}