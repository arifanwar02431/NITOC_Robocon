#include "mbed.h"

#define PERIOD 10
#define MIN_DUTY 0.0
#define MAX_DUTY 0.5

DigitalOut Dig(D4);
PwmOut P(D5);

void write_duty(float value) {
    if(value > MAX_DUTY) {
        value = MAX_DUTY;
        }
    if(value < MIN_DUTY) {
        value = MIN_DUTY;
        }
    P.write(value);
}

void init_esc() {
    P.period_ms(PERIOD);
    write_duty(0.1);
    wait_us(1000000);
}

int main() {
    init_esc();
    while(1) {
        write_duty(0.2);
        Dig = !Dig;
    }
}
