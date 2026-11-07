# HW9：記憶體映射與 POSIX IPC（TLPI 第 49、52、54 章）

| 資料夾 | 內容 |
|---|---|
| `49-1/` | 用 `mmap()` 實作 `cp`：把來源與目的檔都映射到記憶體後直接複製 |
| `52-3/` | 把 System V 訊息佇列的檔案伺服器改寫成 POSIX 訊息佇列版本（詳見資料夾內 README） |
| `54-1/` | 用 POSIX 共享記憶體與具名 semaphore 實作 writer／reader 傳遞資料 |

```bash
cd 49-1 && make && ./49-1 test.txt copy.txt
```
