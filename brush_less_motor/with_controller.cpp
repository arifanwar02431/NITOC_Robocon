#include "mbed.h"
#include "esc.h"

#define PERIOD 10
#define MIN_DUTY 0.0
#define MAX_DUTY 0.5

ESC edf(PB_4, 20);      // 複数個のモータを使いたいときはここを増やす

RawSerial pc(USBTX,USBRX);
RawSerial cont(PA_9, PA_10, 2400);

int PS3[7];

void PS3Data() {
    // 割り込み受信時
    int SBDBT_Data = cont.getc();
    static int bits = 0;

    if(SBDBT_Data == 128) {
        bits = 0;
    }

    if(SBDBT_Data >= 0) {
        PS3[bits] = SBDBT_Data;

        if(bits == 7) {
            bits = 0;
        }
        else {
            bits++;
        }
    }
}

void init_SBDBT() {
    cont.attach(&PS3Data, SerialBase::RxIrq);

    pc.printf("Tilt both sticks down.\r\n");
    do {
        wait_us(1000);
    } while((PS3[4] != 0x7F) && (PS3[6] != 0x7F));  // スティック入力待ち
    ThisThread::sleep_for(1000);
}

void write_duty(double value) {
    edf.setThrottle(value);
    edf.pulse();
}

void init_esc() {
    edf.setThrottle(0.00);
    edf.pulse();
}

int main() {
    init_SBDBT();
    init_esc();
    pc.printf("Start!!!\r\n");
    while(1) {
        write_duty(fabs((double)(-PS3[4] + 64) / (double)64));
        pc.printf("%lf \r\n", fabs((double)(-PS3[4] + 64) / (double)64));
    }
}
