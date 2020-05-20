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
#define POSITION_KEY 1

int duty_cycle = 20;
static volatile int global_pos = 0;
static volatile double global_dist = 0;


PI_THREAD(line_detection) {
    while (1) {
        piLock(POSITION_KEY);
        global_pos = detect_line(black_line);
        piUnlock(POSITION_KEY);

        delay(1000);
    }
    return 0;
} 

PI_THREAD(set_distance) {
    while (1) {
        piLock(DISTANCE_KEY);
        global_dist = measure_distance();
        printf("set distance\n");
        piUnlock(DISTANCE_KEY);

        delay(1000);
    }
    return 0;
}

void create_sensor_threads() {
    int ultra_sensor_thread = piThreadCreate(set_distance);
    if(ultra_sensor_thread != 0) {
        printf("Failed to create the thread for the ultrasonic sensor");
    }

    int line_sensor_thread = piThreadCreate(line_detection);
    if(line_sensor_thread != 0) {
        printf("Failed to create the thread for the line sensors");
    }
}

// handles a signal interrupt
void sigint_handler(int sig_num) {
    printf("Keyboard Interrupt\n");
    keyboard_interrupt = 1;
}

double get_distance() {
    piLock(DISTANCE_KEY);
    double distance = global_dist;
    printf("get distance\n");
    piUnlock(DISTANCE_KEY);

    return distance;
}

int is_obstacle() {
    double distance = get_distance();

    if(distance < 50 && distance > 2) {
        printf("The distance from object is: %.2fcm\n", distance);
        return 1;
    }
    return 0;
}

int get_position() {
    piLock(POSITION_KEY);
    int position = global_pos;
    piUnlock(POSITION_KEY);

    printf("position: %d\n", position);
    return position;
}

void keep_on_track() {

    move_left(FL_MOTOR, arrows);
    // int position = get_position();
    
    // if(position == on_line) 
    //     move_straight(FR_MOTOR, FL_MOTOR, duty_cycle, arrows);
    // else if(position == shifted_left)
    //     move_right(FR_MOTOR, arrows);
    // else if(position == shifted_right)
    //     move_left(FL_MOTOR, arrows);
    // else
    //     printf("Can't detect the line!\n");
}


int main(void) {
    // sets the sigint_handler to handle a signal interrupt
    signal(SIGINT, sigint_handler);
    
    if (wiringPiSetup() == -1) {
        printf("WiringPi Setup failed!\n");
        return -1;
    } 

    Motor motors[] = {FR_MOTOR, FL_MOTOR, BR_MOTOR, BL_MOTOR};
    int num_motors = sizeof(motors) / sizeof(motors[0]);

    setup_motor(motors, num_motors, arrows);
    setup_ultra_sensor();

    create_sensor_threads();

    // to jump start the motor
    set_speed(motors, num_motors, 25);
    forward(motors, num_motors, arrows);
    delay(1000);

    set_speed(motors, num_motors, duty_cycle);
    while(1) {
        keep_on_track();

        // if (!is_obstacle()) {
        //     forward(motors, num_motors, arrows);
        //     keep_on_track();
        //     delay(1000);
        // } else {
        //     printf("detected obstacle\n");
        //     stop(motors, num_motors, arrows); delay(1000);
        //     backward(motors, num_motors, arrows); delay(1000);
        //     stop(motors, num_motors, arrows); delay(1000);
        //     forward(motors, num_motors, arrows);

        //     while (is_obstacle()) {
        //         move_right(FR_MOTOR, arrows);
        //     }
            
        //     while (get_position() == out_of_line) {
        //         move_left(FL_MOTOR, arrows);
        //     }
        // }
              
    }

    return 0;
}
