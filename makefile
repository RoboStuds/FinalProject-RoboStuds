make: main.c Motor.c UltraSensor.c
	gcc -Wall main.c Motor.c UltraSensor.c -o robocar -lwiringPi -lpthread

clean:
	rm robocar
