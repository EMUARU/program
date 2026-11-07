# 物聯網與微處理機系統設計

> 以樹莓派（Raspberry Pi）實作的 9 份課堂作業與期末專題（團隊作品），從 GPIO 控制一路做到雲端平台、語音辨識與影像物件偵測。

| 作業 | 主題 | 使用技術 |
|---|---|---|
| [HW1](HW1/) | Python 基礎：依對照表把符號圖轉換成文字圖案 | Python、檔案讀寫、字典 |
| [HW2](HW2/) | 按鈕切換 LED 閃爍頻率 | GPIO、中斷事件 |
| [HW3](HW3/) | 從電腦經 UART 下指令，用 PWM 控制蜂鳴器音高 | UART、PWM |
| [HW4](HW4/) | 讀取加速度計，依板子傾斜幅度調整蜂鳴器音頻 | SPI、PWM |
| [HW5](HW5/) | 透過 Ubidots 雲端平台串接樹莓派與電腦，遠端控制 LED | REST API、Ubidots |
| [HW6](HW6/) | 用網址連到樹莓派觀看攝影機串流，並以按鈕旋轉鏡頭方向 | Flask、OpenCV、PiCamera |
| [HW7](HW7/) | 語音辨識控制 LED 燈開關 | SpeechRecognition、gTTS、APA102 LED |
| [HW8](HW8/) | 物件偵測：判斷物體是否位於畫面第四象限 | TensorFlow Object Detection API |
| [HW9](HW9/) | 以攝影機偵測物體位置，控制自走車前進 | TensorFlow、PWM 馬達控制 |
| [期末專題](期末專題/) | 以 Discord 機器人遠端控制樹莓派自走車 | Discord Bot、PostgreSQL、OpenCV、語音 |

> 雲端平台金鑰與資料庫連線資訊已從程式碼移除，改由環境變數 `UBIDOTS_TOKEN`、`DATABASE_URL` 提供。
