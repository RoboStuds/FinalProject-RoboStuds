#ifndef MOTOR_H
#define MOTOR_H

    typedef struct Motor {
        int num, e, f, r;
    } Motor;

    typedef struct Arrow {
        int af, ab, ar, al;
    } Arrow;

    extern int keyboard_interrupt;
    extern Motor m1, m2, m3, m4;
    extern Arrow arrows;

    void setup_motor(Motor motors[], int num_motors, Arrow arrows);
    void cleanup(Motor motors[], int num_motors, Arrow arrows);
    void stop(Motor motors[], int num_motors, Arrow arrows);
    void forward(Motor motors[], int num_motors, Arrow arrows);
    void backward(Motor motors[], int num_motors, Arrow arrows);
    void move_straight(Motor right_motor, Motor left_motor, int duty_cycle, Arrow arrows);
    void move_right(Motor right_motor, Arrow arrows);
    void move_left(Motor left_motor, Arrow arrows);
    void set_speed(Motor motors[], int num_motors, int duty_cycle);
    
#endif
