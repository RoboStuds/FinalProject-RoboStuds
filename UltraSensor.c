#include <stdlib.h>
#include <stdio.h>
#include <wiringPi.h>
#include "UltraSensor.h"

int echo = 22, trig = 21;

// void displayCM(double time) {	
// 	double distance = time / 58.0;
		
// 	if(distance < 50 && distance > 2)
// 		printf("The distance from object is: %.2fcm\n", distance);
// }

void setup_ultra_sensor() {
	pinMode(trig, OUTPUT);
	pinMode(echo, INPUT);
}

double measure_distance() {
	double startTime = 0;
	double endTime = 0;
	digitalWrite(trig, LOW);
	delay(500);
	digitalWrite(trig, HIGH);
	delay(0.05);
	digitalWrite(trig, LOW);

	while (digitalRead(echo) == LOW)
		startTime = micros();

	while (digitalRead(echo) == HIGH) 
		endTime = micros();

	return (endTime - startTime) / 58.0;
}

// void pulse() {
// 	while (1) {
// 		double distance = 0;
// 		double startTime = 0;
// 		double endTime = 0;
// 		digitalWrite(trig, LOW);
// 		delay(500);
// 		digitalWrite(trig, HIGH);
// 		delay(0.05);
// 		digitalWrite(trig, LOW);

// 		while (digitalRead(echo) == LOW)
// 			startTime = micros();

// 		while (digitalRead(echo) == HIGH) 
// 			endTime = micros();

// 		displayCM(endTime - startTime);
// 	}
// }

// int main(void) {
	
// 	if (wiringPiSetup() == -1) {
// 		return 0;
// 	}
// 	pinMode(trig, OUTPUT);
// 	pinMode(echo, INPUT);
// 	pulse();
// 	return 0;
// }
