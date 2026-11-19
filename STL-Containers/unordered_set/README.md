# unordered_set

> 雜湊表：所有元素存放在一條 `list` 中，另以 `vector` 記錄每個 bucket 在 list 中的首尾迭代器，查詢時可直接跳到對應區段。

| 檔案 | 說明 |
|---|---|
| `xhash.h` | 雜湊表本體：`find`、`insert`、`erase`、`bucket_size`、bucket 陣列擴充（`assignGrow`）與元素重新分配（`putIn`） |
| `unordered_set.h` | 包裝成 `unordered_set` 介面 |
| `type_traits.h` | 雜湊函式與比較設定 |
| `test_unordered_set.cpp` | 與 `std::unordered_set` 比對 bucket 數量與每個 bucket 的內容 |
