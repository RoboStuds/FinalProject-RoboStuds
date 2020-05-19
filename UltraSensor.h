#ifndef ULTRA_SENSOR_H
#define ULTRA_SENSOR_H

    extern int echo, trig;

    void setup_ultra_sensor();
    double measure_distance();

#endif