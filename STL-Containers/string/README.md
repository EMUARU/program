# string

> 短字串存放在物件內建的緩衝區（Small String Optimization），超過容量時才配置 heap 記憶體。

| 檔案 | 說明 |
|---|---|
| `String.h` | 類別定義 |
| `String.cpp` | 成員函式實作：buffer／fill／copy constructor、`assign`、`resize` |
| `test_string.cpp` | 與 `std::string` 比對 |
