# HW5：雲端平台串接樹莓派與電腦

> 透過 Ubidots IoT 雲端平台，讓電腦與樹莓派互相傳遞資料，達成遠端開關 LED。

| 檔案 | 說明 |
|---|---|
| `lec05.py` | 樹莓派偵測按鈕狀態並上傳到 Ubidots |
| `remote_switch.py` | 樹莓派從 Ubidots 讀取開關狀態並控制 LED |

## 執行方式

```bash
export UBIDOTS_TOKEN=你的金鑰
python lec05.py
python remote_switch.py
```
