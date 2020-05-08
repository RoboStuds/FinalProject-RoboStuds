#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <softPwm.h>
#include "Motor.h"

int keyboard_interrupt = 0;

// wiringPi 0 = P11, wiringPi 2 = P13, wiringPi 3 = P15
Motor back_left_motor = {.num = 1, .e = 0, .f = 3, .r = 2};
// wiringPi 6 = P22, wiringPi 4 = P16, wiringPi 5 = P18
Motor back_right_motor = {.num = 2, .e = 6, .f = 5, .r = 4}; 
// wiringPi 12 = P19, wiringPi 13 = P21, wiringPi 14 = P23
Motor front_right_motor = {.num = 3, .e = 12, .f = 14, .r = 13};
// wiringPi 26 = P32, wiringPi 10 = P24, wiringPi 11 = P26
Motor front_left_motor = {.num = 4, .e = 26, .f = 11, .r = 10};


// wiringPi 25 = P37, wiringPi 23 = P33, wiringPi 27 = P36, wiringPi 24 = P35
Arrow arrows = {.af = 25, .ab = 23, .ar = 27, .al = 24};

// sets the motor and arrow pins to output mode
void setup(Motor motors[], int n, Arrow arrows) {
    for (int i = 0; i < n; i++) {
        pinMode(motors[i].e, OUTPUT);
        pinMode(motors[i].f, OUTPUT);
        pinMode(motors[i].r, OUTPUT);
        softPwmCreate(motors[i].e, 0, 100);
        digitalWrite(motors[i].e, HIGH);
        digitalWrite(motors[i].f, LOW);
        digitalWrite(motors[i].r, LOW);
    }
    pinMode(arrows.af, OUTPUT);
    pinMode(arrows.ab, OUTPUT);
    pinMode(arrows.ar, OUTPUT);
    pinMode(arrows.al, OUTPUT);
}

// sets all the motor and arrow pins to low and switches them into input mode
void cleanup(Motor motors[], int n, Arrow arrows) {
    for (int i = 0; i < n; i++) {
        softPwmWrite(motors[i].e, 0);
        digitalWrite(motors[i].e, LOW);
        digitalWrite(motors[i].f, LOW);
        digitalWrite(motors[i].r, LOW);
        pinMode(motors[i].e, INPUT);
        pinMode(motors[i].f, INPUT);
        pinMode(motors[i].r, INPUT);
    }

    digitalWrite(arrows.af, LOW); 
    digitalWrite(arrows.ab, LOW); 
    digitalWrite(arrows.ar, LOW); 
    digitalWrite(arrows.al, LOW); 
    pinMode(arrows.af, INPUT); 
    pinMode(arrows.ab, INPUT);
    pinMode(arrows.ar, INPUT);
    pinMode(arrows.al, INPUT);
}

/*
* changes the duty_cycle to 0% and sets the forward and reverse pins to low
* turns off the light of the arrows in the motorshield
* cleans up the pins when there is a keyboard interrupt and exits the program
*/
void stop(Motor motors[], int n, Arrow arrows) {
    for (int i = 0; i < n; i++) {
        printf("Motor%d stops...\n", motors[i].num);
        softPwmWrite(motors[i].e, 0);
        digitalWrite(motors[i].f, LOW);
        digitalWrite(motors[i].r, LOW);
    }

    digitalWrite(arrows.af, LOW); 
    digitalWrite(arrows.ab, LOW); 
    digitalWrite(arrows.ar, LOW); 
    digitalWrite(arrows.al, LOW); 

    if (keyboard_interrupt) {
        printf("Cleaning up...\n");
        cleanup(motors, n, arrows);
        exit(1);
    }
}

/*
* sets the enable pin of the motors with the given duty_cycle 
* and sets the forward pin to high and the reverse pin to low
* lights up the forward arrow in the motorshield
* cleans up the pins when there is a keyboard interrupt and exits the program
*/
void forward(Motor motors[], int n, int duty_cycle, Arrow arrows) {
    for (int i = 0; i < n; i++) {
        printf("Motor%d is moving forward with %d%% power\n", motors[i].num, duty_cycle);
        softPwmWrite(motors[i].e, duty_cycle);
        digitalWrite(motors[i].f, HIGH);
        digitalWrite(motors[i].r, LOW);
    }

    digitalWrite(arrows.af, HIGH); 
    digitalWrite(arrows.ab, LOW); 

    if (keyboard_interrupt) {
        printf("Cleaning up...\n");
        cleanup(motors, n, arrows);
        exit(1);
    }
}

/* 
* sets the enable pin of the motors with the given duty_cycle 
* and sets the forward pin to low and the reverse pin to high
* lights up the backward arrow in the motorshield
* cleans up the pins when there is a keyboard interrupt and exits the program
*/ 
void backward(Motor motors[], int n, int duty_cycle, Arrow arrows) {
    for (int i = 0; i < n; i++) {
        printf("Motor%d is moving backward with %d%% power\n", motors[i].num, duty_cycle);
        softPwmWrite(motors[i].e, duty_cycle);
        digitalWrite(motors[i].f, LOW);
        digitalWrite(motors[i].r, HIGH);
    }

    digitalWrite(arrows.af, LOW); 
    digitalWrite(arrows.ab, HIGH); 

    if (keyboard_interrupt) {
        printf("Cleaning up...\n");
        cleanup(motors, n, arrows);
        exit(1);
    }
}

void right(Motor right_motor, int n, int duty_cycle, Arrow arrows) {
    
}

void left(Motor left_motor, int n, int duty_cycle, Arrow arrows) {

}

// sets the enable pin of the motors with the given duty_cycle 
void change_speed(Motor motors[], int n, int duty_cycle) {
    for (int i = 0; i < n; i++) {
        printf("The speed of Motor%d is changing with %d%% power\n", motors[i].num, duty_cycle);
        softPwmWrite(motors[i].e, duty_cycle);
    }
}