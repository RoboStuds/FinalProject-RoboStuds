#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>
#include <stdlib.h>
#include "Motor.h"

// pin BCM: 2,3,21
#define IR_L 8
#define IR_C 9 
#define IR_R 29

void sensor_setup()
{
    setup(); //motor setup
    pinMode(IR_L, INPUT);
    pineMode(IR_C, INPUT);
    pinMode(IR_R, INPUT);

}
// Assume left is m1 and right is m2
void left(Motor motors[])
{
    printf("Turning left...\n");
    digitalWrite(motors[m1].e(), LOW);
    digitalWrite(motors[m1].f(), LOW);
    digitalWrite(motors[m1].r(), LOW);

    digitalWrite(motors[m2].e(), HIGH);
    digitalWrite(motors[m2].f(), HIGH);
    digitalWrite(motors[m2].r(), LOW);
}

void right(Motor motors[])
{
    printf("Turning right...\n");

    digitalWrite(motors[m1].e(), HIGH);
    digitalWrite(motors[m1].f(), HIGH);
    digitalWrite(motors[m1].r(), LOW);

    digitalWrite(motors[m2].e(), LOW);
    digitalWrite(motors[m2].f(), LOW);
    digitalWrite(motors[m2].r(), LOW);

}

// black is 1
// white is 0
void sensor()
{
    while (1) 
    {
        // move forward: left on white, center on black, right on white 
        if((digitalRead(IR_L) == 0) && (digitalRead(IR_C) == 1)&& (digitalRead(IR_R)== 0))
        {
            return forward();
        }
        // turn left: left on black, center on white, right on white
        else if((digitalRead(IR_L == 1)) && (digitalRead(IR_C == 0))&& (digitalRead(IR_C == 0))
        {
            return left();
        }
        // turn right:left on white, center on black, right on white
        else if((digitalRead(IR_L == 0)) && (digitalRead(IR_C == 0))&& (digitalRead(IR_C == 1))
        {
            return right();
        }
        // Stops if all black(1)
        else ((digitalRead(IR_L == 1)) && (digitalRead(IR_C == 1))&& (digitalRead(IR_C == 1))
        {
            return stop();
        }
    }
}

int main(void)
{
    Motor motors[] = {m1, m2, m3, m4};

    wiringPiSetup();
    
    if(wiringPiSetup() == -1)
    {
        printf("Setup has failed.\n");
        return 0;
    }

    int i = 0;
    int speed = 20;

    while(1) 
    {
        forward();
        sensor();
        delay(5000);
    }
    return 0;
}
