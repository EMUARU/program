# 敏捷開發專題：肥宅聊天室（Android App）

> 以敏捷開發流程，在短時間內完成的 Android 聊天軟體，結合 LINE 與 Messenger 的優點，並提供 ACG 資訊查詢。

## 簡介

團隊依敏捷開發的方式分工、迭代開發。App 使用 Firebase 儲存使用者、訊息與群組資料，除了一般聊天功能外，也整合了動畫新番、周邊商品等 ACG 資訊，滿足特定客群的需求。

## 功能

- **帳號**：註冊、登入、重設密碼、個人檔案與頭像（Firebase Authentication）
- **聊天**：一對一私訊、群組聊天、傳送圖片、查看大圖、訊息反應按鈕
- **推播通知**：新訊息透過 Firebase Cloud Messaging 通知
- **好友**：搜尋使用者、查看他人檔案
- **行事曆**：記錄與查看活動
- **分享**：把內容分享到聊天或群組
- **ACG 資訊**：新番列表、比價與周邊商店連結

## 技術

Java、Android、Firebase（Authentication、Realtime Database、Storage、Cloud Messaging）、Retrofit、Glide、Picasso

## 檔案

| 路徑 | 說明 |
|---|---|
| `src/java/com/example/chatroom/` | 主要原始碼：Activity、Adapter、Fragment、Model、Notifications |
| `src/res/` | 版面配置與圖片資源 |
| `src/AndroidManifest.xml` | App 設定 |
| `libraries/` | Android Studio 匯出的相依函式庫設定 |

## 開發方式

團隊專題，依功能分工並以短週期迭代完成。
