#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <softPwm.h>
#include "Motor.h"

int keyboard_interrupt = 0;

// wiringPi 0 = P11, wiringPi 2 = P13, wiringPi 3 = P15 
Motor m1 = {.num = 1, .e = 0, .f = 3, .r = 2};
// wiringPi 6 = P22, wiringPi 4 = P16, wiringPi 5 = P18 
Motor m2 = {.num = 2, .e = 6, .f = 5, .r = 4}; 
// wiringPi 12 = P19, wiringPi 13 = P21, wiringPi 14 = P23 
Motor m3 = {.num = 3, .e = 12, .f = 13, .r = 14};
// wiringPi 26 = P32, wiringPi 10 = P24, wiringPi 11 = P26 
Motor m4 = {.num = 4, .e = 26, .f = 11, .r = 10};

// cleans the motor pins (sets them to low and input)
void cleanup_motor(Motor motor) {
    softPwmWrite(motor.e, 0);
    digitalWrite(motor.e, LOW);
    digitalWrite(motor.f, LOW);
    digitalWrite(motor.r, LOW);

    pinMode(motor.e, INPUT);
    pinMode(motor.f, INPUT);
    pinMode(motor.r, INPUT);
}

// sets the motor pins
void setup_motors(Motor right_motor, Motor left_motor) {
    pinMode(right_motor.e, OUTPUT);
    pinMode(right_motor.f, OUTPUT);
    pinMode(right_motor.r, OUTPUT);

    pinMode(left_motor.e, OUTPUT);
    pinMode(left_motor.f, OUTPUT);
    pinMode(left_motor.r, OUTPUT);

    softPwmCreate(right_motor.e, 0, 100);
    digitalWrite(right_motor.e, HIGH);
    digitalWrite(right_motor.f, LOW);
    digitalWrite(right_motor.r, LOW);

    softPwmCreate(left_motor.e, 0, 100);
    digitalWrite(left_motor.e, HIGH);
    digitalWrite(left_motor.f, LOW);
    digitalWrite(left_motor.r, LOW);
}

// stops the right and left motor (sets the enable pins to 0)
void stop_motors(Motor right_motor, Motor left_motor) {
    softPwmWrite(right_motor.e, 0);
    softPwmWrite(left_motor.e, 0);
}

// moves the right and left motor forward with the given speed
void move_forward(Motor right_motor, Motor left_motor, int speed) {
    softPwmWrite(right_motor.e, speed);
    digitalWrite(right_motor.f, HIGH);
    digitalWrite(right_motor.r, LOW);

    softPwmWrite(left_motor.e, speed);
    digitalWrite(left_motor.f, HIGH);
    digitalWrite(left_motor.r, LOW);

    if (keyboard_interrupt) {
        printf("Cleaning up...\n");
        cleanup_motor(right_motor); 
        cleanup_motor(left_motor);
        exit(1);
    }

}

// moves the right and left motor backward with the given speed
void move_backward(Motor right_motor, Motor left_motor, int speed) {
    softPwmWrite(right_motor.e, speed);
    digitalWrite(right_motor.f, LOW);
    digitalWrite(right_motor.r, HIGH);

    softPwmWrite(left_motor.e, speed);
    digitalWrite(left_motor.f, LOW);
    digitalWrite(left_motor.r, HIGH);

    if (keyboard_interrupt) {
        printf("Cleaning up...\n");
        cleanup_motor(right_motor); 
        cleanup_motor(left_motor);
        exit(1);
    }
}

// moves the robot to the right direction (right-reverse, left-forward)
void move_right(Motor right_motor, Motor left_motor, int speed) {
    softPwmWrite(right_motor.e, speed);
    digitalWrite(right_motor.f, LOW);
    digitalWrite(right_motor.r, HIGH);

    softPwmWrite(left_motor.e, speed);
    digitalWrite(left_motor.f, HIGH);
    digitalWrite(left_motor.r, LOW);

    if (keyboard_interrupt) {
        printf("Cleaning up...\n");
        cleanup_motor(right_motor); 
        cleanup_motor(left_motor);
        exit(1);
    }
}

// moves the robot to the left direction (right-forward, left-reverse)
void move_left(Motor right_motor, Motor left_motor, int speed) {
    softPwmWrite(right_motor.e, speed);
    digitalWrite(right_motor.f, HIGH);
    digitalWrite(right_motor.r, LOW);

    softPwmWrite(left_motor.e, speed);
    digitalWrite(left_motor.f, LOW);
    digitalWrite(left_motor.r, HIGH);

    if (keyboard_interrupt) {
        printf("Cleaning up...\n");
        cleanup_motor(right_motor); 
        cleanup_motor(left_motor);
        exit(1);
    }
}

// sets the enable pin of the motors with the given speed 
void set_speed(Motor motor, int speed) {
    printf("Speed of Motor%d:  %d%%\n", motor.num, speed);
    softPwmWrite(motor.e, speed);
}
