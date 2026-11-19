# STL-Containers：C++ 標準容器實作

> 仿照 Visual C++ 2019 STL 的內部結構與記憶體配置，以 C++ 實作 `vector`、`string`、`list`、`deque`、`unordered_set`，並用這些容器實作任意位數的大整數運算。

各容器的類別介面依照 MSVC STL 設計，下表列出實作的成員函式。

| 資料夾 | 容器 | 內部結構 | 實作重點 |
|---|---|---|---|
| [vector](vector/) | `vector<int>` | 連續陣列（first／last／end 三個指標） | fill／copy constructor、`assign`、`resize`，容量成長方式與 MSVC 一致 |
| [string](string/) | `string` | 短字串使用內建緩衝區（SSO），長字串配置於 heap | buffer／fill／copy constructor、`assign`、`resize` |
| [list](list/) | `list<T>` | 帶哨兵節點（head）的環狀雙向鏈結串列 | copy constructor、`operator=`、`push_front`／`push_back`、`pop_front`／`pop_back`、`clear` |
| [deque](deque/) | `deque<T>` | map（指標陣列）指向固定大小的區塊 | `push_front`、`push_back`，map 空間不足時加倍擴充（`doubleMapSize`） |
| [unordered_set](unordered_set/) | `unordered_set<T>` | 以 `list` 存放元素，`vector` 存放每個 bucket 的首尾迭代器 | `find`、`insert`、`erase`、`bucket_size`、bucket 擴充與 rehash |
| [HugeInteger](HugeInteger/) | `HugeInteger<T>` | 以上述容器逐位存放的大整數類別樣板 | 加、減、乘、除、取餘數與比較，底層容器可切換為 `vector`、`list`、`deque` |

## 測試方式

每個資料夾內的 `test_*.cpp` 會以相同操作分別執行標準 STL 容器與自製容器，**直接比對兩者的記憶體內容**（元素、容量、指標位置），輸出 `There are 0 errors` 表示完全一致。

由於比對的是 MSVC STL 的內部記憶體配置，需使用 **Visual Studio 2019、x86（Win32）** 組態編譯；在其他編譯器或 x64 下結果不具意義。

```text
Visual Studio → 建立「空白專案」→ 加入該資料夾的 .h 與 .cpp → 平台選 x86 → 執行
```

> 部分檔案含 Big5 編碼的中文註解，在 GitHub 網頁上可能顯示為亂碼，用 Visual Studio 開啟即可正常顯示。
