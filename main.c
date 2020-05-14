#include <stdio.h>
#include <signal.h>
#include <wiringPi.h>
#include "Motor.h"

#define fr_motor m3
#define fl_motor m4
#define br_motor m2
#define bl_motor m1

int duty_cycle = 25;

// handles a signal interrupt
void sigint_handler(int sig_num) {
    printf("Keyboard Interrupt\n");
    keyboard_interrupt = 1;
}

PI_THREAD(detect_line) {
    move_straight(fr_motor, fl_motor, duty_cycle, arrows);
    delay(5000);
    move_right(fr_motor, arrows);
    delay(5000);
    move_straight(fr_motor, fl_motor, duty_cycle, arrows);
    delay(5000);
    move_left(fl_motor, arrows);
    delay(5000);
    move_straight(fr_motor, fl_motor, duty_cycle, arrows);
    delay(5000);
    return 0;
} 


int main(void) {
    Motor motors[] = {fr_motor, fl_motor, br_motor, bl_motor};
    int num_motors = sizeof(motors) / sizeof(motors[0]);
    
    // sets the sigint_handler to handle a signal interrupt
    signal(SIGINT, sigint_handler);
    
    if (wiringPiSetup() == -1) {
        printf("WiringPi Setup failed!\n");
        return -1;
    } 

    setup(motors, num_motors, arrows);

    int line_sensor_thread = piThreadCreate(detect_line);
    if(line_sensor_thread != 0) {
        printf("Failed to create the thread for the line sensors");
    }


    set_speed(motors, num_motors, duty_cycle);
    while(1) {
        forward(motors, num_motors, arrows);
    }

    stop(motors, num_motors, arrows);

    return 0;
}
