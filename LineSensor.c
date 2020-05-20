#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "Motor.h"
#include "LineSensor.h"

//BCM: 22, 14, 10
#define IR_L 29 // P40
#define IR_C 28 // P30
#define IR_R 7 // P7 

int white_line = 0, black_line = 1;
int out_of_line = 0, on_line = 1, shifted_left = 2, shifted_right = 3;

void sensor_setup() {
    pinMode(IR_L, INPUT);
    pinMode(IR_C, INPUT);
    pinMode(IR_R, INPUT);
}

int detect_line(int color) {
    int center_read = digitalRead(IR_C);
    int left_read = digitalRead(IR_L);
    int right_read = digitalRead(IR_R);

    printf("center: %d\n", center_read);
    
    if(color == black_line) {
        // left on white, center on black, right on white 
        if(left_read == 0 && center_read == 1 && right_read == 0)
            return on_line;

        // left on white, center on white, right on black 
        // or left on white, center on black, right on black
        else if((left_read == 0 && center_read == 0 && right_read == 1) ||
                (left_read == 0 && center_read == 1 && right_read == 1))
            return shifted_left;

        // left on black, center on white, right on white 
        // or left on black, center on black, right on white
        else if((left_read == 1 && center_read == 0 && right_read == 0) ||
                (left_read == 1 && center_read == 1 && right_read == 0)) 
            return shifted_right;

        else
            return out_of_line;
    } else {
        // left on black, center on white, right on black 
        if(left_read == 1 && center_read == 0 && right_read == 1)
            return on_line;

        // left on black, center on black, right on white
        // or left on black, center on white, right on white
        else if((left_read == 1 && center_read == 1 && right_read == 0) ||
                (left_read == 1 && center_read == 0 && right_read == 0))
            return shifted_left;

        // left on white, center on black, right on black
        // or left on white, center on white, right on black
        else if((left_read == 0 && center_read == 1 && right_read == 1) ||
                (left_read == 0 && center_read == 0 && right_read == 1)) 
            return shifted_right;

        else
            return out_of_line;
    }
}
