# HW3：簡易 shell

> 以 C 語言實作的命令列 shell。

## 功能

- 讀取並解析指令列（`parse.c`）
- 內建指令：`echo`（支援 `-n`）、`quit`／`exit`／`logout`／`bye`（`builtin.c`）
- 以 `fork` + `exec` 執行外部程式（`run_command.c`）
- 指令結尾加 `&` 可在背景執行（`is_background.c`）

## 執行方式

```bash
make && ./shell
```

HW5 的 `part2` 在此基礎上加入 pipe 與 I/O 重導。
