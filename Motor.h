#ifndef MOTOR_H
#define MOTOR_H
    typedef struct Motor {
        int num, e, f, r;
    } Motor;

    typedef struct Arrow {
        int af, ab, ar, al;
    } Arrow;

    extern int keyboard_interrupt;
    extern Motor back_left_motor, back_right_motor, front_right_motor, front_left_motor;
    extern Arrow arrows;

    void setup(Motor motors[], int n, Arrow arrows);
    void cleanup(Motor motors[], int n, Arrow arrows);
    void stop(Motor motors[], int n, Arrow arrows);
    void forward(Motor motors[], int n, int duty_cycle, Arrow arrows);
    void backward(Motor motors[], int n, int duty_cycle, Arrow arrows);
    void move_straight(Motor right_motor, Motor left_motor, int duty_cycle, Arrow arrows);
    void move_right(Motor right_motor, Motor left_motor, int duty_cycle, Arrow arrows);
    void move_left(Motor right_motor, Motor left_motor, int duty_cycle, Arrow arrows);
    void change_speed(Motor motors[], int n, int duty_cycle);
#endif
