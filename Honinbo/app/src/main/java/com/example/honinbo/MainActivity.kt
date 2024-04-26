package com.example.honinbo

import android.content.Intent
import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.material3.Button
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Surface
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.platform.LocalContext
import androidx.compose.ui.tooling.preview.Preview
import com.example.honinbo.ui.theme.HoninboTheme
import com.example.honinbo.game.Board
import com.example.honinbo.game.GameState



class MainActivity : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContent {
            HoninboTheme {
                // A surface container using the 'background' color from the theme
                Surface(
                    modifier = Modifier.fillMaxSize(),
                    color = MaterialTheme.colorScheme.background
                ) {
                    PlayGame("Android")
                }
            }
        }
    }
}





@Composable
fun PlayGame(name: String, modifier: Modifier = Modifier) {

    val context = LocalContext.current // 获取当前的Context

    Button(onClick = {
        // 创建Intent并启动新的Activity
        val intent = Intent(context, PlayGameActivity::class.java)
        context.startActivity(intent)
    }) {
        Text("Go to New Activity")
    }



}


