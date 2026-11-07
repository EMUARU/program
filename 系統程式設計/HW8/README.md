# HW8：FIFO 與 System V 訊息佇列（TLPI 第 44、46 章）

| 資料夾 | 內容 |
|---|---|
| `44-6/` | 改良 FIFO 序號伺服器，避免 client 沒打開讀取端時讓 server 卡住（詳見資料夾內 README） |
| `44-7/` | 示範以 `O_NONBLOCK` 開啟 FIFO：client 尚未開啟時 server 端的 `open()` 行為 |
| `46-2/` | 把序號伺服器改寫成使用 System V 訊息佇列（`make` 後產生 `server`、`client`） |

```bash
cd 44-6 && make
./server &
./client 3
```
