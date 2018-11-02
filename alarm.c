#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include "ifttt.h"

void ALARM_OFF();
void ALARM_ARMING();
void ALARM_ARMED();
void ALARM_TRIGGERED();
void ALARM_SOUNDING();

int main(int argc, char *argv[])
{
	wiringPiSetup();
	pinMode (1, OUTPUT);
	pinMode (2, OUTPUT);
	pinMode (4, OUTPUT);
	
	pinMode (0, INPUT);
	pinMode (3, INPUT);
	pullUpDnControl(3, PUD_UP);
	
	ALARM_OFF();
		
 	return 0;
}

void ALARM_OFF(){
	digitalWrite(1, HIGH);
	digitalWrite(2, LOW);
	digitalWrite(4, LOW);	
	for(;;)
	{
		if(digitalRead(3) == 0) {
		ALARM_ARMING();
		}
	}
}

void ALARM_ARMING(){
	int i;	
	for(i=0; i<=10; i++)
	{
		digitalWrite(1, HIGH); delay(100);
		digitalWrite(1, LOW); delay(100);
	}	
	digitalWrite(2, HIGH);	
	digitalWrite(1, LOW);	
	ALARM_ARMED();
}

void ALARM_ARMED(){
	for(;;)
	{
	while(1){
		while(digitalRead(0) == 1)
			{
				ALARM_TRIGGERED();
			}

		if(digitalRead(3) == 0)
			{
				delay(1000);
				ALARM_OFF();
			}	
	}		
	}
}

void ALARM_TRIGGERED(){	
	int x = 0;
	for(x=0; x<=10; x++)
	{
		digitalWrite(1, HIGH); delay(100);
		digitalWrite(2, HIGH); delay(100);
		digitalWrite(1, LOW); delay(100);
		digitalWrite(2, LOW); delay(100);		
		if(digitalRead(3) == 0)
		{
			delay(1000);
			ALARM_OFF();
			printf("ALARM_OFF \n");	
		}
	}
	ALARM_SOUNDING();
}

void ALARM_SOUNDING(){
		int i;
		for(i=0; i<=2; i++)
		{
		digitalWrite(4, HIGH); delay(200);
		digitalWrite(4, LOW);
		digitalWrite(1, HIGH); delay(200);
		digitalWrite(1, LOW);
		digitalWrite(2, HIGH); delay(200);
		digitalWrite(2, LOW);
		}
		
		printf("Trying to connect to server\n");
		ifttt("https://maker.ifttt.com/trigger/alarm_triggered/with/key/XDeI0D3254-X__Au11TX8l2hN3OBiy_2PTzUV6oRWX", "Halima", "The Alarm", "has been Triggered");
		
		if(digitalRead(3) == 0)
                        {
				delay(1000);
                                ALARM_OFF();
                                printf("ALARM OFF \n"); 
                        }	
}
