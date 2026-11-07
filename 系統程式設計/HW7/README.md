# HW7：Signal（TLPI 第 22 章）

| 檔案 | 內容 |
|---|---|
| `22-3.c` | 父子行程互送大量 signal，比較用 `sigsuspend()` 與 `sigwaitinfo()` 等待 signal 的速度 |
| `22-4.c` | 用 POSIX signal API 實作 System V 風格的 `sigset()`、`sighold()`、`sigrelse()`、`sigignore()`、`sigpause()` |

```bash
make && ./22-3 100000
```
