#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <time.h>

void forward()
{

    printf("Motor moving forward\n");

    //Motor 1 moves forward
    digitalWrite(0, HIGH);
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);

    //Motor 2 moves forward
    digitalWrite(6, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
}

void left()
{

    printf("Motors moving to the left\n");

    //Motor 1
    digitalWrite(0, LOW);
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);

    //Motor 2
    digitalWrite(6, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
}

void right()
{

    printf("Motors moving to the right\n");

    //Motor 1
    digitalWrite(0, HIGH);
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);

    //Motor 2
    digitalWrite(6, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
}

void backward()
{

    printf("Motor moving backward\n");

    //Motor 1 moves Backward
    digitalWrite(0, HIGH);
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);

    //Motor 2 moves Backward
    digitalWrite(6, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
}

void stop()
{

    printf("Motors stop\n");

    //Stop the Motors
    digitalWrite(0, LOW);
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(6, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
}

int main(void)
{

    wiringPiSetup();

    //Motor 1
    pinMode(0, OUTPUT);
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);

    //Motor 2
    pinMode(6, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);

    //Sensor Pins
    pinMode(7, INPUT);
    pinMode(12, INPUT;

    int speed = 10;

    softPwmCreate(0, speed, 100);int var = 0;
    softPwmCreate(6, speed, 100);

    int var = 0;

    while(var < 2){
        //Move Forward
        if ((digitalRead(7) == 0) && (digitalRead(12) == 0))
        {
            forward();
            delay(5000);
        }
        //Make a Right turn
        else
            ((digitalRead(7) == 0) && (digitalRead(12) == 1))
            {
                right();
                delay(5000);
            }

        //Make a left turn
        else((digitalRead(7) == 1) && (digitalRead(12) == 0))
        {
            left();
            delay(5000);
        }
        else
        {
            stop();
        }
        var++;
        speed += 30;
    }
    return 0;
}