#include <mbed.h>

DigitalOut dig(D2);
PwmOut p(D3);

int main() {
    p.period_ms(5);
    while(true) {
        dig = 1;        // モータの回転方向(0 or 1)
        p = 0.3;        // モータの回転速度(max: 1.0)
    }
    return 0;
}
