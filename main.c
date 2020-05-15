#include <stdio.h>
#include <signal.h>
#include <wiringPi.h>
#include "Motor.h"
#include "UltraSensor.h"
#include "LineSensor.h"

#define FR_MOTOR m3
#define FL_MOTOR m4
#define BR_MOTOR m2
#define BL_MOTOR m1

#define DISTANCE_KEY 0

int duty_cycle = 25;
static volatile double global_dist = 0;

// handles a signal interrupt
void sigint_handler(int sig_num) {
    printf("Keyboard Interrupt\n");
    keyboard_interrupt = 1;
}

PI_THREAD(line_detection) {
    while (1) {
        detect_line();
        if right
            move_right(FR_MOTOR, arrows);
        else if left
            move_left(FL_MOTOR, arrows);
        else 
            move_straight(FR_MOTOR, FL_MOTOR, duty_cycle, arrows);
        // move_straight(FR_MOTOR, FL_MOTOR, duty_cycle, arrows);
        // delay(5000);
        // move_right(FR_MOTOR, arrows);
        // delay(5000);
        // move_straight(FR_MOTOR, FL_MOTOR, duty_cycle, arrows);
        // delay(5000);
        // move_left(FL_MOTOR, arrows);
        // delay(5000);
        // move_straight(FR_MOTOR, FL_MOTOR, duty_cycle, arrows);
        // delay(5000);
    }
    return 0;
} 

PI_THREAD(get_distance) {
    while (1) {
        piLock(DISTANCE_KEY);
        global_dist = measure_distance();
        piUnlock(DISTANCE_KEY);
    }

    return 0;
}


int main(void) {
    Motor motors[] = {FR_MOTOR, FL_MOTOR, BR_MOTOR, BL_MOTOR};
    int num_motors = sizeof(motors) / sizeof(motors[0]);
    
    // sets the sigint_handler to handle a signal interrupt
    signal(SIGINT, sigint_handler);
    
    if (wiringPiSetup() == -1) {
        printf("WiringPi Setup failed!\n");
        return -1;
    } 

    setup_motor(motors, num_motors, arrows);
    setup_ultra_sensor();

    int ultra_sensor_thread = piThreadCreate(get_distance);
    if(ultra_sensor_thread != 0) {
        printf("Failed to create the thread for the ultrasonic sensor");
    }

    int line_sensor_thread = piThreadCreate(line_detection);
    if(line_sensor_thread != 0) {
        printf("Failed to create the thread for the line sensors");
    }

    double distance = 0;
    set_speed(motors, num_motors, duty_cycle);
    while(1) {
        piLock(DISTANCE_KEY);
        distance = global_dist;
        piUnlock(DISTANCE_KEY);
        if(distance < 70 && distance > 2)
            stop(motors, num_motors, arrows);
        else {
            forward(motors, num_motors, arrows);
        }
        delay(1000);
        
    }

    stop(motors, num_motors, arrows);

    return 0;
}
