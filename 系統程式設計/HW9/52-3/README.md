# 52-3：POSIX 訊息佇列檔案伺服器

> client 傳送檔案路徑給 server，server 讀取檔案後透過 POSIX 訊息佇列把內容傳回 client。

## 執行方式

```bash
make
./server &               # 先執行 server
./client test.txt        # client 要帶一個檔案路徑當參數
```

資料夾內附有 `empty.txt` 與 `test.txt` 可供測試。
