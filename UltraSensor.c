#include <stdlib.h>
#include <stdio.h>
#include <wiringPi.h>
#include "UltraSensor.h"

int echo = 22, trig = 21;

// sets the ultrasonic sensor pins
void setup_ultra_sensor() {
	pinMode(trig, OUTPUT);
	pinMode(echo, INPUT);
}

// returns the distance 
double measure_distance() {
	double startTime = 0;
	double endTime = 0;
	digitalWrite(trig, LOW);
	delay(100);
	digitalWrite(trig, HIGH);
	delay(0.05);
	digitalWrite(trig, LOW);

	while (digitalRead(echo) == LOW)
		startTime = micros();

	while (digitalRead(echo) == HIGH) 
		endTime = micros();

	return (endTime - startTime) / 58.0;
}
