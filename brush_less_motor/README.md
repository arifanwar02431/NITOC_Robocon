# ブラシレスモータの制御
stand_alone.cpp: リポとESCを接続して回すだけ

with_controller.cpp: リポとESCに加え、SBDBT（usbドングル）とコントローラを使用

## 使用機器詳細
- ESC: Flycolor 40A OPTO brushless ESC 2-6S
- SBDBT: SBDBT 3v3 (usbドングル)
- コントローラー: PS3コントローラー (dualshock)

## その他
[ESCを使うときはここからインポートしましょう](https://os.mbed.com/teams/Line-Following-Robot/code/ESC/)
### 補足
- ESCは「Electronic Speed Controller」と言って、モーターの磁界を制御して回転数をコントロールしてくれます
- 電気信号が発生しないのでノイズの心配もない
- 2023.01現在、部室には以下のESCがあります
  - Flycolor 40A OPTO brushless ESC 2-6S
  - HOBBYWING SKYWALKER 50A ブラシレスESC /24A6A
