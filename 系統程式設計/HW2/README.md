# HW2：實作 tail（TLPI 第 13 章）

> 實作 `tail [-n num] file`，從檔案結尾以區塊為單位往回讀取，只讀需要的部分就輸出最後 n 行（預設 10 行），不必讀完整個檔案。

```bash
make && ./tail -n 20 file.txt
```
