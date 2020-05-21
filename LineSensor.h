#ifndef LINESENSOR_H
#define LINESENSOR_H

    extern int white_line, black_line;
    extern int out_of_line, on_line;
    extern int shifted_left, shifted_right;
    extern int left_edge, right_edge;

    void setup_line_sensor();
    int detect_line();

#endif
