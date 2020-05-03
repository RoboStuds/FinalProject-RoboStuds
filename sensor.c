#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>
#include <stdlib.h>
#include "Motor.h"

#define IR_L 8
#define IR_C 9 
#define IR_R 7

void sensor_setup()
{
    setup();
    pinMode(IR_L, INPUT);
    pineMode(IR_C, INPUT);
    pinMode(IR_R, INPUT);

}

void sensor()
{
    while (1) 
    {
        // move forward: left on white, center on black, right on white 
        if((digitalRead(IR_L) == 0) && (digitalRead(IR_C) == 1)&& (digitalRead(IR_R)== 0))
        {
            forward();
        }
        // turn left: left on black, center on white, right on white
        else if((digitalRead(IR_L == 1)) && (digitalRead(IR_C == 0))&& (digitalRead(IR_C == 0))
        {
            digitalWrite(m1.f, LOW);
            digitalWrite(m2.f, HIGH);
            digitalWrite(m3.f, LOW);
            digitalWrite(m4.f, HIGH);
        }
        //turn right
        else if((digitalRead(IR_L == 0)) && (digitalRead(IR_C == 0))&& (digitalRead(IR_C == 1))
        {
            digitalWrite(m1.f, HIGH);
            digitalWrite(m2.f, LOW);
            digitalWrite(m3.f, HIGH);
            digitalWrite(m4.f, LOW);
        }
        // stops
        else ((digitalRead(IR_L == 1)) && (digitalRead(IR_C == 1))&& (digitalRead(IR_C == 1))
        {
            stop();
        }
    }
}