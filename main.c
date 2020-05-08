#include <stdio.h>
#include <signal.h>
#include <wiringPi.h>
#include "Motor.h"

#define IR_L 8
#define IR_C 9 
#define IR_R 7

int duty_cycle = 20;

// handles a signal interrupt
void sigint_handler(int sig_num) {
    printf("Keyboard Interrupt\n");
    keyboard_interrupt = 1;
}

PI_THREAD(detect_line) {
    move_right(front_right_motor, front_left_motor, duty_cycle, arrows);
    delay(5000);
    move_straight(front_right_motor, front_left_motor, duty_cycle, arrows);
    delay(5000);
    move_left(front_right_motor, front_left_motor, duty_cycle, arrows);
    delay(5000);
    return 0;
} 


int main(void) {
    Motor front_motors[] = {front_right_motor, front_left_motor};
    Motor back_motors[] = {back_right_motor, back_left_motor};
    int num_front_motors = sizeof(front_motors) / sizeof(front_motors[0]);
    int num_back_motors = sizeof(back_motors) / sizeof(back_motors[0]);
    
    // sets the sigint_handler to handle a signal interrupt
    signal(SIGINT, sigint_handler);
    
    if (wiringPiSetup() == -1) {
        printf("WiringPi Setup failed!\n");
        return -1;
    } 

    setup(front_motors, num_front_motors, arrows);
    setup(back_motors, num_back_motors, arrows);

    int line_sensor_thread = piThreadCreate(detect_line);
    if(line_sensor_thread != 0) {
        printf("Failed to create the thread for the line sensors");
    }

    int i = 0;
    while(i < 6) {
        forward(back_motors, num_back_motors, duty_cycle, arrows);
        delay(5000);

        duty_cycle += 5;
        i++;
    }

    stop(front_motors, num_front_motors, arrows);
    stop(back_motors, num_back_motors, arrows);

    return 0;
}
