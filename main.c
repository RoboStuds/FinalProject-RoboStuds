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

int reg_speed = 24;
int rev_speed = 15;
int gentle_fturn_speed = 27;
int gentle_bturn_speed = 32;
int sharp_turn_speed = 42;

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
        linked_left(gentle_fturn_speed, gentle_bturn_speed);
    } else if(position == shifted_left) {
        linked_right(gentle_fturn_speed, gentle_bturn_speed);
    } else if(position == right_edge) {
        linked_stop(); delay(1000);
        linked_backward(rev_speed); delay(500);
        linked_right(reg_speed, sharp_turn_speed);
    } else if(position == left_edge) {
        linked_stop(); delay(1000);
        linked_backward(rev_speed); delay(500);
        linked_left(reg_speed, sharp_turn_speed);
    } else {
        //linked_backward(reg_speed);
        linked_right(gentle_fturn_speed, gentle_bturn_speed);
        linked_left(gentle_fturn_speed, gentle_bturn_speed);
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
            linked_forward(reg_speed);
            keep_on_track();
            delay(300);
            linked_stop();
            delay(500);

        } 

        printf("detected obstacle\n");
        linked_stop();
        delay(2000);

        while (is_obstacle()) {
            linked_right(gentle_fturn_speed, gentle_bturn_speed);
        }
        
        while (get_position() == out_of_line) {
            linked_left(gentle_fturn_speed, gentle_bturn_speed);
        }
            
        
              
    }

    cleanup_arrows();
    cleanup_motor(FR_MOTOR); cleanup_motor(FL_MOTOR);
    cleanup_motor(BR_MOTOR); cleanup_motor(BL_MOTOR);

    return 0;
}
