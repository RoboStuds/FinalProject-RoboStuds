#ifndef LINESENSOR_H
#define LINESENSOR_H

    extern int white_line, black_line;
    extern int out_of_line, on_line, shifted_left, shifted_right;

    // typedef struct LineSensor {
    //     int white_line, black_line;
    //     int out_of_line, on_line, shifted_left, shifted_right;
    // } LineSensor;
    
    // extern LineSensor line_sensor;

    void sensor_setup();
    void detect_line();

#endif
