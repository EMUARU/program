# HW11：Socket 字典查詢伺服器

> 把 HW5 的字典查詢改成 client／server 架構，分別用三種 socket 實作。

| 資料夾 | 傳輸方式 | client | server |
|---|---|---|---|
| `part1/` | UNIX domain socket（TCP） | `lookup7.c` | `usock_server.c` |
| `part2/` | Internet TCP socket | `lookup8.c` | `isock_server.c` |
| `part3/` | Internet UDP socket | `lookup9.c` | `udp_server.c` |

每個資料夾內 `fixrec` 為字典資料檔，`lookup5.c` 為 server 端的本機查詢函式。

```bash
cd part2 && make
```
