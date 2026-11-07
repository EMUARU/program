# 44-6：防止 FIFO server 被 client 卡住

> 改良 TLPI 的 FIFO 序號伺服器：如果 client 送出請求後沒有打開自己的讀取 FIFO，server 也不會因此被阻塞。

## 執行方式

```bash
make
./server &                    # 先執行 server
./client 3                    # 模擬正常 client 的行為
./client_without_open_fifo    # 模擬沒有打開讀取端的 client
```
