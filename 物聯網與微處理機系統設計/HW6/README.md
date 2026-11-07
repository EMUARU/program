# HW6：網頁攝影機串流

> 在樹莓派上架設 Flask 網頁伺服器，用瀏覽器連到網址即可看到攝影機即時畫面；每按一次實體按鈕，畫面就以 OpenCV 再旋轉 45 度，改變鏡頭方向。

| 檔案 | 說明 |
|---|---|
| `app-camera.py` | Flask 伺服器，以 MJPEG 串流輸出畫面 |
| `camera_pi.py` | 攝影機擷取與 OpenCV 旋轉處理 |

```bash
python app-camera.py   # 瀏覽 http://<樹莓派 IP>:8000
```
