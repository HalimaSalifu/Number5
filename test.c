#include <stdio.h>
#include <wiringPi.h>

void main() {

	wiringPiSetup();
	pinMode (1, OUTPUT);
	pinMode (3, INPUT);
	pullUpDnControl(3, PUD_UP);
	
	int x = digitalRead(3);
	for(;;){
	if(x == 0)
		digitalWrite(1, HIGH);
	}

}
