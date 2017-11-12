#include <stdio.h>   
#include <signal.h>
#include <wiringPi.h>
#include <stdlib.h>

#define RED 5
#define GREEN 6
#define BLUE 13
#define YELLOW 19

void cleanup() {
	digitalWrite(RED, LOW);
	digitalWrite(GREEN, LOW);
	digitalWrite(BLUE, LOW);
	digitalWrite(YELLOW, LOW);
	exit(0);
}

void plm() {
	printf("Pressed\n");
}

int main(void) {
	int time = 100000;
	signal(SIGINT, cleanup);
	wiringPiSetupGpio();
	wiringPiISR(26, INT_EDGE_RISING, plm);
	pinMode(RED, OUTPUT);
	pinMode(GREEN, OUTPUT);
	pinMode(BLUE, OUTPUT);
	pinMode(YELLOW, OUTPUT);
	pinMode(20, INPUT);
	digitalWrite(RED, LOW);
	digitalWrite(GREEN, LOW);
	digitalWrite(BLUE, LOW);
	digitalWrite(YELLOW, LOW);
	int x = 0;

	while(1) {
		//if(digitalRead(20))
		///	time -= 5000;
		if(x % 4 == 0) {
		digitalWrite(RED, LOW);
		digitalWrite(GREEN, LOW);
		digitalWrite(BLUE, LOW);
		digitalWrite(YELLOW, HIGH);
		} else if (x % 4 == 1) {
		digitalWrite(GREEN, LOW);
		digitalWrite(BLUE, LOW);
		digitalWrite(YELLOW, LOW);
		digitalWrite(RED, HIGH);
		} else if (x % 4 == 2) {
		digitalWrite(BLUE, LOW);
		digitalWrite(YELLOW, LOW);
		digitalWrite(RED, LOW);
		digitalWrite(GREEN, HIGH);
		} else if (x % 4 == 3) {	
		digitalWrite(YELLOW, LOW);
		digitalWrite(RED, LOW);
		digitalWrite(GREEN, LOW);
		digitalWrite(BLUE, HIGH);
		}
		x++;
	usleep(time);
	}
	return 0;
}
