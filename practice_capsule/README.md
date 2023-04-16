# practice_capsule
ガチャ制御教材  

## 概要
### step1
**PWM制御**  
モータをボールが詰まらない速度で回転させる.

### step2
**SW & Encoder制御**  
スイッチとエンコーダを使い, スイッチを1回押すとボールが1個出るようにする. (120°回転すると止まるようにする)

### step3
**SW & Encoder制御応用**  
スイッチを1回押すとボールが1個出るまで動くようにする.

## 解答
stepごとにディレクトリは分けて, プログラムファイル(step*.cpp)は`main.cpp`に記述することをオススメします.

### step1
**ディレクトリ構成**
```
.
├── mbed-os
|   └── .
├── .mbed
├── main.cpp
└── mbed-os.lib
```

### step2
**ディレクトリ構成**
```
.
├── mbed-os
|   └── .
├── .mbed
├── main.cpp
├── mbed-os.lib
├── RotaryEncoder.cpp
└── RotaryEncoder.h
```

### step3
**ディレクトリ構成**
```
.
├── mbed-os
|   └── .
├── .mbed
├── main.cpp
├── mbed-os.lib
├── RotaryEncoder.cpp
└── RotaryEncoder.h
```