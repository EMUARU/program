# 期末專題：Discord 遠端控制樹莓派自走車

> 使用者在 Discord 群組輸入指令，就能遠端操控樹莓派自走車；登入時以圖片比對驗證身分，並支援語音輸入。

## 簡介

團隊期末專題。系統分成兩部分：

1. **樹莓派端（`project.py`）**：負責帳號登入、讀取 Ubidots 上的指令並驅動馬達與蜂鳴器。
2. **Discord 機器人（`YueDiscordBot/`）**：接收群組中的指令，透過 Ubidots 轉送給自走車；也包含入群驗證、身分組管理與音樂播放功能。

## 使用流程

1. 操控自走車前，必須先建立帳號並加入 Discord 群組。
2. 登入自走車操控系統時，要上傳建立帳號時使用的圖片，系統以色彩直方圖比對驗證身分。
3. 在 Discord 群組的聊天欄位輸入指令操控自走車。

## Discord 指令

| 指令 | 功能 |
|---|---|
| `#f <秒數>`／`#b <秒數>` | 前進／後退 |
| `#l <秒數>`／`#r <秒數>` | 左轉／右轉 |
| `#stop` | 停止 |
| `#sound` | 讓車上的蜂鳴器發出聲音 |

## 技術

Python、Raspberry Pi（GPIO、馬達）、discord.py、Ubidots、PostgreSQL（Heroku）、OpenCV、SpeechRecognition、gTTS

## 檔案

| 路徑 | 說明 |
|---|---|
| `project.py` | 樹莓派端主程式 |
| `YueDiscordBot/` | Discord 機器人 |
| `*.png` | 帳號登入用的範例圖片 |
| `期末專題報告.docx` | 期末報告 |

## 執行方式

```bash
export UBIDOTS_TOKEN=你的金鑰
export DATABASE_URL=postgres://...
python project.py
```
