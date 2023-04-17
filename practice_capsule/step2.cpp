#include "mbed.h"
#include "RotaryEncoder.h"      // エンコーダ制御ではこれを使う
#include <DigitalInOut.h>

DigitalOut dig(D2);
PwmOut p(D3);
RawSerial pc(USBTX, USBRX);

RotaryEncoder re(D7, D8);        // ロリコンピン(A, B)定義

DigitalIn sw(A5);       // スイッチピン定義

void init_pwm();
void init_sw();
void roll();

// PWM信号の初期化
void init_pwm() {
    p.period_us(100);
    p = 0;
    ThisThread::sleep_for(100);
}

// スイッチの初期設定
void init_sw() {
    sw.mode(PullUp);
    ThisThread::sleep_for(100);
}

// テーブルを回転させるための動作をまとめた関数
void roll() {
    p = 0.3;

    double target_angle = 120.0;        // 目標回転角度
    double current_angle = 0.0;         // 現在の角度(初期値0.0)

    while(true) {
        current_angle = re.Get_Count() * 0.17578125;

        if(target_angle < current_angle) {
            dig = 0;
        } else if(target_angle > current_angle) {
            dig = 1;
        } else {
            p = 0;
        }

        if(current_angle >= target_angle) {
            break;
        }
    }
    p = 0;
}

int main() {
    init_pwm();
    init_sw();

    p.period_ms(5);
    while(true) {
        // pc.printf(" %d\r\n", sw.read());
        if(sw.read() == 0) {
            roll();
        } else {
            p = 0;
        }
        re.Reset();     // ロリコンリセット
    }
    return 0;
}