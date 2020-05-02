make: main.c Motor.c 
	gcc -Wall main.c Motor.c -o robocar -lwiringPi -lpthread

clean:
	rm robocar
