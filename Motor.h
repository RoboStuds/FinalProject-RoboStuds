#ifndef MOTOR_H
#define MOTOR_H

    typedef struct Motor {
        int num, e, f, r;
    } Motor;

    extern int keyboard_interrupt;
    extern Motor m1, m2, m3, m4;

    void cleanup_motor(Motor motor);
    void setup_motors(Motor right_motor, Motor left_motor);
    void stop_motors(Motor right_motor, Motor left_motor);
    void move_forward(Motor right_motor, Motor left_motor, int speed);
    void move_backward(Motor right_motor, Motor left_motor, int speed);
    void move_right(Motor right_motor, Motor left_motor, int speed);
    void move_left(Motor right_motor, Motor left_motor, int speed);
    void set_speed(Motor motor, int speed);
    
#endif
