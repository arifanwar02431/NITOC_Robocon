#include "mbed.h"
#include "RotaryEncoder.h"
#include <DigitalInOut.h>

DigitalOut dig(D2);
PwmOut p(D3);
RawSerial pc(USBTX, USBRX);

RotaryEncoder re(D7, D8);        // ロリコンピン(A, B)

DigitalIn sw1(A5);       // スタートスイッチピン
DigitalIn sw2(A4);       // カウントスイッチピン

int cnt1 = 0;        // スタートスイッチ用カウント変数
int cnt2 = 0;        // カウントスイッチ用カウント変数

void init_pwm();
void init_sw();
void roll();
void time();

void init_pwm() {       // PWMの初期化
    p.period_us(100);
    p = 0;
    ThisThread::sleep_for(100);
}

void init_sw() {        // スイッチの初期設定
    sw1.mode(PullUp);       // スタートスイッチ
    sw2.mode(PullUp);       // カウントスイッチ(出口のところのスイッチ)
    ThisThread::sleep_for(100);
}

void roll() {       // テーブルを回転させる
    p = 0.3;

    double target_angle = 105.0;        // 目標回転角度
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
        time();
    }
    p = 0;
}

void time() {
    int i;
    for(i=1; i<=50; i++) {
        ThisThread::sleep_for(100);
        if(sw2.read() == 0) {
            break;
        }
    }
    if(i <= 49) {
        roll();
    }
}

int main() {
    init_pwm();
    init_sw();

    p.period_ms(5);
    while(true) {
        // pc.printf(" %d\r\n", sw1.read());
        if(sw1.read() == 0) {
            cnt1++;
            roll();
        }
        if(sw2.read() == 0) {
            cnt2++;
        }
        if(cnt1 > cnt2) {
            roll();
        } else if(cnt1 == cnt2) {
            p = 0;
        }
        re.Reset();
    }
    return 0;
}