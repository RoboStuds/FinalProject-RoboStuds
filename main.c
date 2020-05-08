#include <stdio.h>
#include <signal.h>
#include <wiringPi.h>
#include "Motor.h"

#define IR_L 8
#define IR_C 9 
#define IR_R 7

// handles a signal interrupt
void sigint_handler(int sig_num) {
    printf("Keyboard Interrupt\n");
    keyboard_interrupt = 1;
}



int main(void) {
    Motor motors[] = {back_left_motor, back_right_motor, front_right_motor, front_left_motor};
    int n = sizeof(motors) / sizeof(motors[0]);
    
    // sets the sigint_handler to handle a signal interrupt
    signal(SIGINT, sigint_handler);
    
    if (wiringPiSetup() == -1) {
        printf("WiringPi Setup failed!\n");
        return -1;
    } 

    setup(motors, n, arrows);
    pinMode(IR_L, INPUT);
    pinMode(IR_C, INPUT);
    pinMode(IR_R, INPUT);

    int duty_cycle = 20;
    while(1) {
        //forward(motors, n, duty_cycle, arrows);
        //delay(5000);

        
        if((digitalRead(IR_L) == 0))
            printf("left detected white");
        else 
            printf("left detected black");
        
        /*
        if((digitalRead(IR_C) == 0))
            printf("center detected white");
        else 
            printf("center detected black");
        
        if((digitalRead(IR_R) == 0))
            printf("right detected white");
        else 
            printf("right detected black");
        */
    }

    //stop(motors, n, arrows);

    return 0;
}
