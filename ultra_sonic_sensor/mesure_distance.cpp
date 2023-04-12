#include "mbed.h"

int flag = 0;
int captime = 0;

double dist = 0.0;

void flip_rise();
void flip_fall();

Timer counter;

RawSerial PC(USBTX, USBRX, 9600);
DigitalOut trigger(D7);
InterruptIn data(D8);

// main() runs in its own thread in the OS
int main() {
    data.rise(&flip_rise);
    data.fall(&flip_fall);

    while (true) {
        trigger = 1;
        wait_us(10);
        trigger = 0;
        ThisThread::sleep_for(60);

        dist = captime * 0.034 / 2.0;
        if(dist > 400.0) {
            PC.printf("distance: error!!!\r\n");
        }
        else {
            PC.printf("distance: %3.2lfcm\r\n", dist);
        }
    }
}

void flip_rise() {
    counter.start();
    flag = 0;
}

void flip_fall() {
    counter.stop();
    captime = counter.read_us();
    counter.reset();
    flag = 1;
}
