# YueDiscordBot：自走車控制機器人

> 期末專題的 Discord 機器人（機器人名稱：Kay0211），使用 discord.py 的 Cog 架構撰寫，資料庫使用 Heroku PostgreSQL。

## 功能模組

| 檔案 | 功能 |
|---|---|
| `commands/raspberry.py` | 自走車控制指令（`#f`、`#b`、`#l`、`#r`、`#stop`、`#sound`），透過 Ubidots 傳給樹莓派 |
| `commands/main.py` | 一般指令：清除訊息、查詢身分、產生與確認驗證碼 |
| `commands/event.py` | 成員加入／離開通知、訊息事件、以表情反應領取身分組 |
| `commands/music.py` | 播放 YouTube 音樂、查看佇列、跳過 |
| `core/classes.py` | 共用的 Cog 基底類別與資料庫連線 |
| `bot.py` | 機器人進入點，載入所有指令模組 |

## 執行方式

1. 建立 `setting.json`（已列入 `.gitignore`），內容包含 `{"Token": "你的 Discord Bot Token"}`。
2. 設定環境變數 `UBIDOTS_TOKEN` 與 `DATABASE_URL`。
3. 安裝套件並啟動：

   ```bash
   pip install -r requirements.txt
   python bot.py
   ```

可依 `Procfile` 部署到 Heroku。
