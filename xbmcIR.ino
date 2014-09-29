/*
Remote control for XBMC
Author: José Teixeira - jbteixeir@gmail.com
*/
#include <IRremote.h>

//Infrared code mapping
#define UP 551486205
#define DOWN 551518845
#define LEFT 551542815
#define RIGHT 551510175
#define OK 551494365
#define BACK 551490795
#define PLAY 551489010
#define PAUSE 551509410
#define STOP 551521650
#define SLEEP 551514255
#define MUTE 551522415
#define VOLDOWN 551534655
#define VOLUP 551502015
#define PRVTRCK 1551547150
#define NXTTRCK 551514510
#define PLAYPAUSE 16
#define LASTKEY 4294967295

//infrared pin
#define IRPIN 11

IRrecv irrecv(IRPIN);
decode_results results;

void setup(){
	Serial.begin(9600);
        irrecv.enableIRIn(); // Start the receiver
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
		    case PLAY:
		      // do something
		      Serial.println("PLAY");
		      break;
		    case PAUSE:
		      // do something
		      Serial.println("PAUSE");
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
            case LASTKEY:
		      // do something
		      Serial.println("LASTKEY");
		      break;
		    default:
		      // do something     
		      Serial.println(results.value);
              Serial.println("UNKNOWN");
		}
    	// Receive the next value
    	irrecv.resume();
    }
}
