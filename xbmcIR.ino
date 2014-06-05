/*
Remote control for XBMC
Author: José Teixeira - jbteixeir@gmail.com
*/
#include <IRremote.h>

//Infrared code mapping
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define OK 5
#define BACK 6
#define PLAY 7
#define PAUSE 8
#define STOP 9

//infrared pin
#define IRPIN 3

IRrecv irrecv(IRPIN);
decode_results results;

void setup(){
	Serial.begin(9600);
}

void loop(){
	if (irrecv.decode(&results)) {
		switch (results.value) {
		    case UP:
		      // do something
		      Serial.println("UP");
		      break;
		    case DOWN:
		      // do something
		      Serial.println("DOWN");
		      break;
		    case LEFT:
		      // do something
		      Serial.println("LEFT");
		      break;
		    case RIGHT:
		      // do something
		      Serial.println("RIGHT");
		      break;
		    case OK:
		      // do something
		      Serial.println("OK");
		      break;
		    case BACK:
		      // do something
		      Serial.println("BACK");
		      break;
		    case PLAYPAUSE:
		      // do something
		      Serial.println("PLAY/PAUSE");
		      break;
		    case NXTTRCK:
		      // do something
		      Serial.println("NXTTRCK");
		      break;
		    case PRVTRCK:
		      // do something
		      Serial.println("PRVTRCK");
		      break;
		    case STOP:
		      // do something
		      Serial.println("STOP");
		      break;
		    case VOLUP:
		      // do something
		      Serial.println("VOLUP");
		      break;
		    case VOLDOWN:
		      // do something
		      Serial.println("VOLDOWN");
		      break;
		    case MUTE:
		      // do something
		      Serial.println("MUTE");
		      break;
		    case SLEEP:
		      // do something
		      Serial.println("SLEEP");
		      break;
		    default:
		      // do something     
		      Serial.println(results.value);
		}
    	// Receive the next value
    	irrecv.resume();
    }
}