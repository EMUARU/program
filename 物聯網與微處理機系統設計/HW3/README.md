# HW3：UART 指令控制蜂鳴器

> 電腦透過 UART（`/dev/ttyAMA1`，9600 baud）傳送指令給樹莓派，樹莓派依指令以 PWM 讓蜂鳴器發出 Do～Si 七個音。

- UART 序列埠通訊（pyserial）
- PWM 控制蜂鳴器頻率（262～493 Hz）
- pigpio 控制另一組 PWM 輸出

```bash
python hw3.py
```
