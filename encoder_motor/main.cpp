#include "mbed.h"
#include "RotaryEncoder.h"

RawSerial pc(USBTX,USBRX);
RotaryEncoder R1(PB_6, PB_7);

DigitalOut motor(PA_7);
PwmOut motor_p(PA_8);

int step_count = 0;

double Target_distance = 0.0;
double Current_distance = 0.0;

void Move(void);
void Counter(void);

int main(void){
    motor_p.period_us(1275);
    while(1){
        //pc.printf("%d: %d, %.2lf\n\r", step_count, R1.Get_Count(), R1.Get_Circumference(10, 2048));
        Move();
        Counter();
        Current_distance = R1.Get_Circumference(10, 2048);
        ThisThread::sleep_for(10);
    }
}

void Move(void){
    if(Target_distance - 0.5 > Current_distance){
        motor = 0;
        motor_p = 0.5; 
    }
    else if(Target_distance + 0.5 < Current_distance){
        motor = 1;
        motor_p = 0.5;
    }
    else{
        motor_p = 0;
    }
}

void Counter(void){
    switch(step_count){
        case 100: Target_distance = 10; break;
        case 250: Target_distance = 0; break;
        case 500: Target_distance = -30; break;
        case 750: Target_distance = 0; break;
    }
    step_count++;
}