#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include "Arrow.h"


// wiringPi 25 = P37, wiringPi 23 = P33, wiringPi 27 = P36, wiringPi 24 = P35
Arrow arrows = {.af = 25, .ab = 23, .ar = 27, .al = 24};

void setup_arrows() {
    pinMode(arrows.af, OUTPUT);
    pinMode(arrows.ab, OUTPUT);
    pinMode(arrows.ar, OUTPUT);
    pinMode(arrows.al, OUTPUT);
}

void cleanup_arrows() {
    digitalWrite(arrows.af, LOW); 
    digitalWrite(arrows.ab, LOW); 
    digitalWrite(arrows.ar, LOW); 
    digitalWrite(arrows.al, LOW); 

    pinMode(arrows.af, INPUT); 
    pinMode(arrows.ab, INPUT);
    pinMode(arrows.ar, INPUT);
    pinMode(arrows.al, INPUT);
}

void turn_on(int arrow) {
    digitalWrite(arrow, HIGH);
}

void turn_off(int arrow) {
    digitalWrite(arrow, LOW);
}

