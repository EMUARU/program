# 程式設計二（Computer Programming II）

> 大學二年級（2020 年春季）C++ 課程的 13 份作業與 2 次期中考。前半學期仿照 Visual C++ 2019 的 STL 自行實作 `vector`、`string`、`list`、`deque` 等容器，後半學期以物件導向設計 ATM 與高鐵訂票系統。

每個資料夾內有 `題目.docx`（若有保留）與程式碼。作業多為課程提供測試程式（`Assignment N.cpp`），學生實作指定的成員函式。

| 作業 | 主題 | 重點 |
|---|---|---|
| [HW1](HW1/) | `vector` | fill constructor、copy constructor、`assign`、`resize` 與容量成長 |
| [HW2](HW2/) | `string` | buffer／fill／copy constructor、`assign`、`resize` |
| [HW3](HW3/) | 大整數 `HugeInteger`（以 `vector` 實作） | 加減乘除、取餘數與比較運算 |
| [HW4](HW4/) | 大整數 `HugeInteger`（以 `string` 實作） | 同上，改用自製 `string` 存放位數 |
| [HW5](HW5/) | 類別樣板 | 將 `HugeInteger` 與 `vector` 改寫為 template |
| [HW6](HW6/) | `list` | copy constructor、`operator=`、`push_front`／`push_back`、`pop_front`／`pop_back`、`clear` |
| [HW7](HW7/) | 迭代器（`XUtility.h`） | `HugeInteger` 透過迭代器操作底層容器，可切換 `vector` 與 `list` |
| [HW8](HW8/) | `deque` | `push_front`、`push_back` 與 map 擴充 `doubleMapSize` |
| [HW9](HW9/) | 容器整合 | `HugeInteger` 分別以自製 `vector`、`list`、`deque` 為底層容器 |
| [HW10](HW10/) | ATM 系統 | 依需求文件設計 `ATM`、`Account` 類別：驗證帳號、查詢餘額、提款、存款 |
| [HW11](HW11/) | ATM 系統（拆分類別） | 將查詢、提款、存款拆成 `BalanceInquiry`、`Withdrawal`、`Deposit` 類別 |
| [HW12](HW12/) | 高鐵訂票系統 | 訂票、查詢與取消訂位；訂位資料以二進位檔儲存 |
| [HW13](HW13/) | 高鐵訂票系統（物件導向版） | 拆分為時刻表、車次、訂位資料庫等類別，並使用自製 `vector` |
| [期中考1](期中考1/) | 上機考 | `vector` 插入、`string`、`HugeInteger` 運算 |
| [期中考2](期中考2/) | 上機考 | `list`、`deque`、多項式乘法 |

## 環境

Visual Studio 2019（C++）。在 Visual Studio 建立主控台專案，加入該資料夾的 `.cpp` 與 `.h` 後編譯；需要輸入檔的作業（`Test cases.txt`、`*.dat`）請將檔案放在專案目錄。

> 部分原始碼為 Big5 編碼，在 GitHub 網頁上中文註解可能顯示為亂碼，用 Visual Studio 開啟即可正常顯示。
