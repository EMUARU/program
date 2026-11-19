# HugeInteger

> 任意位數的整數類別樣板 `HugeInteger<T>`，以容器存放各位數，底層容器可替換為自製的 `vector`、`list` 或 `deque`。

| 檔案 | 說明 |
|---|---|
| `HugeInteger.h` | 大整數樣板：加、減、乘、除、取餘數、比較與輸入輸出 |
| `Vector.h`、`List.h`、`Deque.h`、`XUtility.h` | 自製容器與迭代器 |
| `test_HugeInteger.cpp` | 讀取 `Test cases.txt`，以不同容器與整數型別執行四則運算並驗證結果 |
