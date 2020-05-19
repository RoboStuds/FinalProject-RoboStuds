#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "Motor.h"
#include "LineSensor.h"

//BCM: 22, 14, 10
#define IR_L 6
#define IR_C 15 
#define IR_R 12

int straight = 1, right = 0, left=0;

void sensor_setup() {
    pinMode(IR_L, INPUT);
    pinMode(IR_C, INPUT);
    pinMode(IR_R, INPUT);

}

void detect_line() {
    // move straight: left on white, center on black, right on white 
    if(digitalRead(IR_L) == 0 && digitalRead(IR_C) == 1 && digitalRead(IR_R)== 0) {
        straight = 1; 
        right = 0; 
        left = 0;
    }
    // turn left: left on black, center on white, right on white
    else if(digitalRead(IR_L) == 1 && digitalRead(IR_C) == 0 && digitalRead(IR_R) == 0) {
        straight = 0; 
        right = 0; 
        left = 1;
    }
    // turn left: left on black, center on black, right on white
    else if(digitalRead(IR_L) == 1 && digitalRead(IR_C) == 1 && digitalRead(IR_R) == 0) {
        straight = 0; 
        right = 0; 
        left = 1;
    }
    else if(digitalRead(IR_L) == 0 && digitalRead(IR_C) == 0 && digitalRead(IR_R) == 1) {
        straight = 0; 
        right = 1; 
        left = 0;
    }
    // turn right:left on white, center on black, right on black
    else if(digitalRead(IR_L) == 0 && digitalRead(IR_C) == 1 && digitalRead(IR_R) == 1) {
        straight = 0; 
        right = 1; 
        left = 0;
    } 

}
