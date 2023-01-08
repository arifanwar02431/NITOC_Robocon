# robocon_memo
部内共有、備忘録的な何か  
後輩の参考にでもなれば  
フォルダ名・ファイル名・ディレクトリ構成　何もかも雑でごめんなさい

## ディレクトリ構成
```
.
├── brush_less_motor
|   ├── ESC ----------------------- ブラシレスモータに付いてる四角いやつを使うときはこれが必要
|   |   ├── esc.cpp
|   |   └── esc.h
|   ├── README.md
|   ├── stand_alone.cpp ----------- とりあえずブラシレスモータを動かしてみるプログラム(C++)
|   └── with_controller.cpp ------- ブラシレスモータをコントローラーで動かすためのプログラム(C++)
├── dc_motor
|   ├── main.cpp ------------------ DCモータの動作確認用プログラム(C++)
|   └── README.md
├── encoder_motor
|   ├── RotaryEncoder.cpp --------- エンコーダ付きのモータ回すためのプログラム(C++)
|   └── RotaryEncoder.h
├── self_position_estimation ------ 自己位置推定
|   ├── odometry.cpp -------------- オドメトリ手法(C++)
|   └── README.md
├── servo_motor
|   ├── main.cpp ------------------ サーボモータの動作確認用プログラム(C++)
|   └── README.md
├── ultra_sonic_sensor
|   ├── measure_distance.py ------- 超音波センサで距離を測るためのプログラム(Python)
|   └── README.md
└── README.md --------------------- このファイル
```

### 注意書きとか使ってるものの型番とかは、各フォルダ内のREADME.mdに書いてあります
