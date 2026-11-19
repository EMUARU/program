# set（紅黑樹）

> 以紅黑樹為底層的 `set<T>`，結構仿照 MSVC STL 的 `xtree`：以 head 節點同時作為 nil 節點，`head->parent` 指向根節點。

## 實作內容

- **插入**：依二元搜尋樹插入後，以 `reBalance` 處理連續紅色節點，視叔叔節點顏色進行變色，或執行 LL、LR、RL、RR 旋轉
- **刪除**：有兩個子節點時，以右子樹最小節點取代後轉為刪除 degree ≤ 1 的節點（`eraseDegreeOne`），再以 `fixUp` 處理雙黑節點、恢復紅黑樹性質
- **走訪**：preorder、inorder

| 檔案 | 說明 |
|---|---|
| `xtree.h` | 紅黑樹本體：插入、刪除、旋轉與平衡 |
| `set.h` | 以紅黑樹包裝成 `set` 介面 |
| `xstddef.h` | 比較函式物件 |
| `test_set.cpp` | 隨機插入與刪除，與 `std::set` 比對樹的 preorder／inorder 結構與節點顏色 |
