# Honinbo：圍棋棋譜勝率分析 App

> 可以下棋、分析棋譜每一步勝率的 Android App，神經網路直接在手機上推論，並附有討論聊天室。

## 簡介

Honinbo（本因坊）是 3 人團隊的專題作品。使用者可以在 App 中下棋或載入棋局，App 會用內建的圍棋神經網路計算目前局面的勝率與建議落點；也可以把棋局分享到聊天室與其他人討論。

## 功能

- **對弈與棋盤**：自繪 19 路棋盤，處理落子、提子與棋局狀態（`Board.kt`、`GameState.kt`、`PlayGameActivity.kt`）
- **勝率分析**：讀取 ResNet 架構的權重檔（policy head＋value head），以 Kotlin 自行實作卷積、批次正規化、im2col、矩陣乘法與 softmax，**在手機端完成推論**，不需要連線到伺服器（`Network.kt`、`Analyze.kt`）
- **帳號系統**：註冊、登入（`Register.kt`、`Login.kt`）
- **聊天室**：即時訊息與回覆討論，資料存放在 Firebase Realtime Database（`Chat.kt`、`MessageDiscussionFragment.kt`）

## 我的角色

- 前端畫面元件的繪製
- 前端與後端（Firebase）的串接
- 團隊另外兩位成員分別負責 AI 推論與聊天室功能

## 技術

Kotlin、Android（Jetpack Compose、RecyclerView）、Firebase Realtime Database

## 檔案

| 路徑 | 說明 |
|---|---|
| `app/src/main/java/com/example/honinbo/` | 主要原始碼 |
| `Honinbo_last(23-12-28).zip` | 完整的 Android Studio 專案（含 Gradle 設定與資源檔） |

## 執行方式

解壓縮 `Honinbo_last(23-12-28).zip`，用 Android Studio 開啟 `AOS_APP` 資料夾後建置執行。權重檔 `weights.txt` 需放在 `assets/` 中。
