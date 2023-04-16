#include <mbed.h>

DigitalOut dig(D2);
PwmOut p(D3);

int main() {
    p.period_ms(5);
    while(true) {
        dig = 1;
        p = 0.3;
    }
    return 0;
}
