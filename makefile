make: main.c Motor.c UltraSensor.c LineSensor.c
	gcc -Wall main.c Motor.c UltraSensor.c LineSensor.c -o robocar -lwiringPi -lpthread

clean:
	rm robocar
