#include<stdlib.h>
#include<stdio.h>
#include<wiringPi.h>
const int ECHO = 22, TRIG = 21, RED = 0;

void displayCM(double time)
{	
	double distance = time / 58.0;
		
		if(distance < 100 && distance > 2)
		{
			printf("The distance from object is: %.2fcm\n",distance);
			digitalWrite(RED, HIGH);
		}
		else
		{
			digitalWrite(RED, LOW);
		}
}
void pulse()
{
	while (1)
	{
		double distance = 0;
		double startTime = 0;
		double endTime = 0;
		digitalWrite(TRIG, LOW);
		delay(500);
		digitalWrite(TRIG, HIGH);
		delay(0.05);
		digitalWrite(TRIG, LOW);

		while (digitalRead(ECHO) == LOW)
		{
			startTime = micros();
		}
		while (digitalRead(ECHO) == HIGH)
		{
				endTime = micros();
		}
			displayCM(endTime - startTime);
	}
}
int main(void)
{
	
	if (wiringPiSetup() == -1)
	{
		return 0;
	}
	pinMode(TRIG, OUTPUT);
	pinMode(ECHO, INPUT);
	pinMode(RED, OUTPUT);
	pulse();
	return 0;
}
