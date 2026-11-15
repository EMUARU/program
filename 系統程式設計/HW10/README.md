# HW10：共享記憶體生產者／消費者

> 一個 producer 以固定速率產生訊息，放進 POSIX 共享記憶體中只有 B 格的緩衝區（滿了就淘汰最舊的一筆），再以 `sigqueue` 送出 SIGUSR1、附帶訊息序號，通知多個 consumer 行程讀取，並統計在不同參數下的封包遺失情形（依作業要求採用 Shared Memory + signal）。

## 參數

```bash
make
./hw10 <資料數量 M> <傳送速率 R> <consumer 數量 N> <buffer size B>
```

## 實驗

- 實驗一：固定 buffer，改變傳送速率與 consumer 數量
- 實驗二：固定傳送速率，改變 buffer size 與 consumer 數量
- 使用的參數組合見 `指令.txt`；結果記錄在 `1.csv`、`2.csv`，以 `plot.py` 畫成 `1.png`、`2.png`
- 完整分析見 `SP_HW10報告.pdf`

| 檔案 | 說明 |
|---|---|
| `hw10.c` | 主程式 |
| `plot.py` | 繪製結果圖（pandas、matplotlib） |
