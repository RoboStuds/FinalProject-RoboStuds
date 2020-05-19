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

void sensor_setup()
{
    pinMode(IR_L, INPUT);
    pinMode(IR_C, INPUT);
    pinMode(IR_R, INPUT);
}

PI_THREAD(detect_line)
{
    while (1)
    {
        // move forward if left sensor is on white, center sensor is on black, right sensor is on white
        if ((digitalRead(IR_L) == 0) && (digitalRead(IR_C) == 1) && (digitalRead(IR_R) == 0))
        {
            return move_straight();
        }
        // turn left if left sensor is on black, center sensor is on white, left sensor is on white
        else if((digitalRead(IR_L == 1)) && (digitalRead(IR_C == 0)) && (digitalRead(IR_R == 0))
        {
            return move_left();
        }
        // turn right if left sensor is on white, center sensor is on white, right sensor is on black
        else if((digitalRead(IR_L == 0)) && (digitalRead(IR_C == 0))&& (digitalRead(IR_R == 1))
        {
            return move_right();
        }
        // Stops if all sensors are black(1)
        else ((digitalRead(IR_L == 1)) && (digitalRead(IR_C == 1))&& (digitalRead(IR_R == 1))
        {
            return stop();
        }
    }
    return 0;
}
