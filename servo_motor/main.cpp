#include "mbed.h"

#define PERIOD 20

DigitalOut Dig(D4);
PwmOut P(D5);

int main() {
    P.period_ms(PERIOD);

    while (1) {
        P.pulsewidth_us(500);
        wait_us(500000);
        P.pulsewidth_us(1450);
        wait_us(500000);
    }
}
