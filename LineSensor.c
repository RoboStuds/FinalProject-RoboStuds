#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "Motor.h"
#include "LineSensor.h"

#define IR_L 29 // P40
#define IR_C 28 // P30
#define IR_R 8 // P3 

int white_line = 0, black_line = 1;
int out_of_line = 0, on_line = 1;
int shifted_right = 2, shifted_left = 3;
int right_edge = 4, left_edge = 5;

void setup_line_sensor() {
    pinMode(IR_R, INPUT);
    pinMode(IR_C, INPUT);
    pinMode(IR_L, INPUT);
}

int detect_line(int color) {
    int right_read = digitalRead(IR_R);
    int center_read = digitalRead(IR_C);
    int left_read = digitalRead(IR_L);
    
    if(color == black_line) {
        // left on white, center on black, right on white 
        if(left_read == 0 && center_read == 1 && right_read == 0)
            return on_line;

        // left on black, center on white, right on white 
        else if(left_read == 1 && center_read == 0 && right_read == 0)
            return shifted_right;

        // left on white, center on white, right on black 
        else if(left_read == 0 && center_read == 0 && right_read == 1)
            return shifted_left;

        // left on white, center on black, right on black
        else if(left_read == 0 && center_read == 1 && right_read == 1)
            return right_edge;

        // left on black, center on black, right on white
        else if(left_read == 1 && center_read == 1 && right_read == 0)
            return left_edge;

        else
            return out_of_line;
    } else {
        // left on black, center on white, right on black 
        if(left_read == 1 && center_read == 0 && right_read == 1)
            return on_line;

        // left on white, center on black, right on black
        else if(left_read == 0 && center_read == 1 && right_read == 1)
            return shifted_right;

        // left on black, center on black, right on white
        else if(left_read == 1 && center_read == 1 && right_read == 0)
            return shifted_left;

        // left on black, center on white, right on white
        else if(left_read == 1 && center_read == 0 && right_read == 0)
            return right_edge;

        // left on white, center on white, right on black
        else if(left_read == 0 && center_read == 0 && right_read == 1)
            return left_edge;

        else
            return out_of_line;     
    }
}
