# HW9：HugeInteger 與自製容器整合

> 將前面實作的容器整合進 `HugeInteger` 樣板，比較以不同容器作為底層時的運算結果。

| 檔案／資料夾 | 內容 |
|---|---|
| `Assignment 9-1.cpp` | 以 `deque` 為底層，測試 `int`／`unsigned int`／`short int`／`unsigned short int` |
| `Assignment 9-2/` | `HugeInteger` 可切換 `vector`、`list`、`deque` |
| `Assignment 9-3/` | 以 `deque`、`list` 為底層的版本 |
| `Vector.h`、`List.h`、`Deque.h`、`XUtility.h` | 自製容器與迭代器 |
| `Test cases.txt`、`Result.txt` | 測試資料與執行結果 |
