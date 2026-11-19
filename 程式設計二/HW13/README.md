# HW13：高鐵訂票系統（物件導向版）

> 以物件導向重新設計 HW12：將時刻表、車次與訂位資料庫拆成獨立類別，並以自製 `vector` 存放資料。

| 類別 | 職責 |
|---|---|
| `MakingReservation` | 訂票流程 |
| `ReservationHistory` | 查詢、減少張數與取消訂位 |
| `ReservationDatabase` | 讀寫 `Reservation details.dat` |
| `Reservation` | 單筆訂位資料 |
| `SouthboundTimetable`／`NorthboundTimetable` | 讀取南下／北上時刻表 |
| `Train` | 單一車次 |
| `vector`（`Vector.h`） | 自製容器 |

主程式為 `Assignment 13.cpp`，執行時 `*.dat` 需放在專案目錄。
