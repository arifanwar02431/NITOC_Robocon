#include "mbed.h"
#include "RotaryEncoder.h"
#include <DigitalInOut.h>

DigitalOut dig(D2);
PwmOut p(D3);
RawSerial pc(USBTX, USBRX);

RotaryEncoder re(D7, D8);        // ロリコンピン(A, B)定義

DigitalIn sw(A5);       // スイッチピン定義

void init_pwm() {
    p.period_us(100);
    p = 0;
    ThisThread::sleep_for(100);
}

void init_sw() {
    sw.mode(PullUp);
    ThisThread::sleep_for(100);
}

void roll() {
    p = 0.3;

    double target_angle = 120.0;
    double current_angle = 0.0;

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
        re.Reset();
    }
    return 0;
}