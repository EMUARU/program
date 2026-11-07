# HW1：檔案 I/O（TLPI 第 4 章）

| 資料夾 | 內容 |
|---|---|
| `4-1/` | 實作 `tee`：把標準輸入同時寫到標準輸出與多個檔案，支援 `-a` 附加模式；按 Ctrl+C 時關閉所有檔案再結束 |
| `4-2/` | 實作 `cpHole`：複製檔案時遇到連續的空位元組就用 `lseek` 跳過，讓目的檔保留原本的檔案空洞（hole） |

## 執行方式

```bash
cd 4-1 && make && ./tee [-a] file1 file2 ...
cd 4-2 && make && ./cpHole source dest
```
