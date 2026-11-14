# gemeS：終端機小遊戲合集

> 自學 Python 時寫的練習專案：在 Windows 命令提示字元中，用方向鍵選單遊玩「屏風式四子棋」與「猜顏色」，並用 PyInstaller 打包成單一執行檔。

## 遊戲內容

### 屏風式四子棋（Connect Four）

- 雙人輪流用 `←`／`→` 選擇欄位、`Space` 投下棋子，棋子會落到最底部
- 縱、橫、斜任一方向連成四子獲勝；棋盤下滿仍無人連線則平手
- 目前只有雙人對戰（PVP）模式

### 猜顏色（類似 Mastermind）

- 電腦隨機出 4 格顏色（共 6 種顏色），玩家要在 8 次以內猜中
- 每次猜完會提示「位置和顏色都對」與「顏色對但位置不對」的數量
- 可選擇單人或雙人輪流猜，以及答案中顏色是否可以重複

### 點格棋（Dots and Boxes）

- 已建立類別架構，尚未完成，選單中暫時隱藏

## 設計重點

- **抽象類別**：`Game` 繼承 `ABC`，定義所有遊戲共用的流程（說明 → 選單 → 開始遊戲）與抽象方法 `play_game()`、`init_draw()`、`check_game_finish()`、`finish_game()`，各遊戲再分別實作
- **封裝**：玩家與遊戲狀態用私有屬性搭配 `@property` 存取；各遊戲的玩家類別（`CF_Player`、`GTC_Player`）繼承共用的 `Player`
- **自訂例外**：`Interrupt` 處理中途離開與找不到地圖檔的情況
- **終端機繪圖**：以 `ctypes` 呼叫 Windows API 移動游標（`move.py`）和設定文字顏色（`color.py`），用 `pynput` 監聽鍵盤，`cursor` 隱藏游標
- **地圖檔**：棋盤外框從 `map *.txt` 讀入，畫面與程式邏輯分離

## 檔案

| 檔案 | 說明 |
|---|---|
| `gemeS.py` | 程式進入點與遊戲選單 |
| `Game.py` | 遊戲抽象類別與共用選單 |
| `Player.py` | 玩家基底類別 |
| `Connect_Four.py` | 四子棋 |
| `Guess_The_Color.py` | 猜顏色 |
| `Dots_And_Boxes.py` | 點格棋（未完成） |
| `color.py`、`move.py` | 終端機文字顏色與游標位置控制 |
| `Interrupt.py` | 遊戲中斷例外 |
| `map Connect_Four.txt`、`map Guess_The_Color.txt` | 棋盤畫面 |
| `gemeS.spec` | PyInstaller 打包設定 |

## 執行方式

僅支援 Windows（使用 Windows 主控台 API）。

```bash
pip install -r requirements.txt
python gemeS.py
```

打包成執行檔（`map *.txt` 需與 exe 放在同一個資料夾）：

```bash
pip install pyinstaller
pyinstaller gemeS.spec
```
