make: main.c Motor.c UltraSensor.c LineSensor.c Arrow.c
	gcc -Wall main.c Motor.c UltraSensor.c LineSensor.c Arrow.c -o robocar -lwiringPi -lpthread

clean:
	rm robocar
