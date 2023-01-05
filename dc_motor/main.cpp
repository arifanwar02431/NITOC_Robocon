#include "mbed.h"

DigitalOut Dig(D5);
PwmOut P(D6);
RawSerial PC(USBTX, USBRX);

int main() {
    P.period_ms(5);
    while(1) {
        Dig = 0;
        P = 0.5;
    }
    return 0;
}
