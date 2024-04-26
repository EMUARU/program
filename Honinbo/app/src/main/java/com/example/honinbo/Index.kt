package com.example.honinbo

import android.content.Intent
import android.os.Bundle
import android.widget.Button
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Surface
import androidx.compose.material3.Text
import androidx.compose.runtime.Composable
import androidx.compose.ui.Modifier
import androidx.compose.ui.tooling.preview.Preview
import com.example.honinbo.ui.theme.HoninboTheme

class Index : ComponentActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.index)

        val playButton: Button = findViewById(R.id.btnPlay)
        val analyzeButton: Button = findViewById(R.id.btnAnalyze)

        playButton.setOnClickListener {
            val intent = Intent(this, PlayGameActivity::class.java)
            startActivity(intent)
        }

        analyzeButton.setOnClickListener {
            val intent = Intent(this, Analyze::class.java)
            startActivity(intent)
        }
    }
}
