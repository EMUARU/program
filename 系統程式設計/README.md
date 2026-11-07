# 系統程式設計（Network System Programming）

> 2023 年網路系統程式設計課程的 12 份作業，以 C 語言在 Linux 上實作檔案 I/O、行程、signal、IPC、socket 等系統程式。題目多出自 *The Linux Programming Interface*（TLPI）的習題。

每個作業資料夾內有 `題目`、程式碼與 `makefile`，大多可直接 `make` 編譯。

| 作業 | 主題 | 重點 |
|---|---|---|
| [HW1](HW1/) | 檔案 I/O | 實作 `tee`、能保留檔案空洞（hole）的 `cp` |
| [HW2](HW2/) | I/O 緩衝 | 實作 `tail -n`，從檔尾往回讀取 |
| [HW3](HW3/) | 簡易 shell | 指令解析、內建指令、背景執行 |
| [HW4](HW4/) | `/proc` 檔案系統 | 列出使用者的行程、行程樹、找出開啟某檔案的行程 |
| [HW5](HW5/) | 系統指令與 shell 進階 | `cat`／`date`／`ls` 等指令、shell 的 pipe 與 I/O 重導、字典查詢程式 |
| [HW6](HW6/) | Pipe | 雙向 pipe 的父子行程溝通、自製 `popen`／`pclose` |
| [HW7](HW7/) | Signal | `sigsuspend` 與 `sigwaitinfo` 效能比較、自製 System V signal API |
| [HW8](HW8/) | FIFO 與 System V 訊息佇列 | 防止惡意 client 卡住 FIFO server、非阻塞 FIFO、訊息佇列版序號伺服器 |
| [HW9](HW9/) | 記憶體映射與 POSIX IPC | 用 `mmap` 實作 `cp`、POSIX 訊息佇列檔案伺服器、POSIX 共享記憶體 |
| [HW10](HW10/) | 共享記憶體＋semaphore | 一對多的生產者／消費者，實驗不同參數下的封包遺失，附報告 |
| [HW11](HW11/) | Socket | 字典查詢伺服器：UNIX domain socket、TCP、UDP 三種版本 |
| [HW12](HW12/) | inotify | 遞迴監控目錄的新增、刪除與搬移 |

## 環境

Linux、gcc、make

> HW8、HW9 中的 `tlpi_hdr.h`、`error_functions.*`、`get_num.*`、`ename.c.inc` 為 TLPI 書附的輔助程式。
