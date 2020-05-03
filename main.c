#include <stdio.h>
#include <signal.h>
#include <wiringPi.h>
#include "Motor.h"

// handles a signal interrupt
void sigint_handler(int sig_num) {
    printf("Keyboard Interrupt\n");
    keyboard_interrupt = 1;
}



int main(void) {
    Motor motors[] = {m1, m2, m3, m4};
    int n = sizeof(motors) / sizeof(motors[0]);
    
    // sets the sigint_handler to handle a signal interrupt
    signal(SIGINT, sigint_handler);
    
    if (wiringPiSetup() == -1) {
        printf("WiringPi Setup failed!\n");
        return -1;
    } 

    setup(motors, n, arrows);
    int duty_cycle = 5;
    while(1) {
        forward(motors, n, duty_cycle, arrows);
        delay(5000);

    }

    stop(motors, n, arrows);

    return 0;
}
