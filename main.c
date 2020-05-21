#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <wiringPi.h>
#include "Motor.h"
#include "Arrow.h"
#include "UltraSensor.h"
#include "LineSensor.h"

#define FR_MOTOR m3
#define FL_MOTOR m4
#define BR_MOTOR m2
#define BL_MOTOR m1

#define DISTANCE_KEY 0
#define POSITION_KEY 1

int reg_speed = 15;
int gentle_turn_speed = 25;
int sharp_turn_speed = 45;

static volatile int global_pos = 0;
static volatile double global_dist = 0;


PI_THREAD(line_detection) {
    while (1) {
        piLock(POSITION_KEY);
        global_pos = detect_line(black_line);
        piUnlock(POSITION_KEY);

        delay(500);
    }
    return 0;
} 

PI_THREAD(set_distance) {
    while (1) {
        piLock(DISTANCE_KEY);
        global_dist = measure_distance();
        // printf("set distance\n");
        piUnlock(DISTANCE_KEY);

        delay(500);
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
    // printf("get distance\n");
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

    return position;
}

void linked_forward(int speed) {
    move_forward(FR_MOTOR, FL_MOTOR, speed);
    move_forward(BR_MOTOR, BL_MOTOR, speed);
    turn_on(arrows.af);
    turn_off(arrows.ab);
    turn_off(arrows.ar);
    turn_off(arrows.al);
}

void linked_backward(int speed) {
    move_backward(FR_MOTOR, FL_MOTOR, speed);
    move_backward(BR_MOTOR, BL_MOTOR, speed);
    turn_off(arrows.af);
    turn_on(arrows.ab);
    turn_off(arrows.ar);
    turn_off(arrows.al);
}

void linked_right(int f_speed, int b_speed) {
    move_right(FR_MOTOR, FL_MOTOR, f_speed);
    move_forward(BR_MOTOR, BL_MOTOR, b_speed);
    turn_on(arrows.af);
    turn_off(arrows.ab);
    turn_on(arrows.ar);
    turn_off(arrows.al);
}

void linked_left(int f_speed, int b_speed) {
    move_left(FR_MOTOR, FL_MOTOR, f_speed);
    move_forward(BR_MOTOR, BL_MOTOR, b_speed);
    turn_on(arrows.af);
    turn_off(arrows.ab);
    turn_off(arrows.ar);
    turn_on(arrows.al);
}

void linked_stop() {
    stop_motors(FR_MOTOR, FL_MOTOR);
    stop_motors(BR_MOTOR, BL_MOTOR);
    turn_off(arrows.af);
    turn_off(arrows.ab);
    turn_off(arrows.ar);
    turn_off(arrows.al);
}

void keep_on_track() {
    int position = get_position();
    
    if(position == on_line) {
        linked_forward(reg_speed);
    } else if(position == shifted_right) {
        linked_left(gentle_turn_speed, gentle_turn_speed);
    } else if(position == shifted_left) {
        linked_right(gentle_turn_speed, gentle_turn_speed);
    } else if(position == right_edge) {
        linked_right(reg_speed, sharp_turn_speed);
    } else if(position == left_edge) {
        linked_left(reg_speed, sharp_turn_speed);
    } else {
        printf("Can't detect the line!\n");
    }
}


int main(void) {
    // sets the sigint_handler to handle a signal interrupt
    signal(SIGINT, sigint_handler);
    
    if (wiringPiSetup() == -1) {
        printf("WiringPi Setup failed!\n");
        return -1;
    } 

    // setup the motor and sensors
    setup_motors(FR_MOTOR, FL_MOTOR);
    setup_motors(BR_MOTOR, BL_MOTOR);
    setup_arrows();
    setup_ultra_sensor();
    setup_line_sensor();

    create_sensor_threads();

    while(!keyboard_interrupt) {
        while (!is_obstacle()) {
            keep_on_track();
            delay(500);
            linked_stop(500);
            delay(500);

        } 

        printf("detected obstacle\n");
        linked_stop();
        delay(2000);

        while (is_obstacle()) {
            linked_right(gentle_turn_speed, gentle_turn_speed);
        }
        
        while (get_position() == out_of_line) {
            linked_left(gentle_turn_speed, gentle_turn_speed);
        }
            
        
              
    }

    cleanup_arrows();
    cleanup_motor(FR_MOTOR); cleanup_motor(FL_MOTOR);
    cleanup_motor(BR_MOTOR); cleanup_motor(BL_MOTOR);

    return 0;
}
