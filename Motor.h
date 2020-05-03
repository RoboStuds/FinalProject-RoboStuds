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

    void setup(Motor motors[], int n, Arrow arrows);
    void cleanup(Motor motors[], int n, Arrow arrows);
    void stop(Motor motors[], int n, Arrow arrows);
    void forward(Motor motors[], int n, int duty_cycle, Arrow arrows);
    void backward(Motor motors[], int n, int duty_cycle, Arrow arrows);
    void right(Motor right_motor, int n, int duty_cycle, Arrow arrows);
    void left(Motor left_motor, int n, int duty_cycle, Arrow arrows);
    void change_speed(Motor motors[], int n, int duty_cycle);
#endif
