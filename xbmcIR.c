/*
Remote control for XBMC
Maps serial commands to keyboard keystrokes
Author: José Teixeira - jbteixeir@gmail.com
*/

#include <string.h> 
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef _WIN32
	#include <windows.h>
#endif

#ifdef linux
	#include <X11/Xlib.h>
	#include <X11/keysym.h>
	#include <X11/extensions/XTest.h>
	
	Display *display;
	unsigned int keycode;
	display = XOpenDisplay(NULL);
	
	keycode = XKeysymToKeycode(display, XK_Pause);
	XTestFakeKeyEvent(display, keycode, True, 0);
	XTestFakeKeyEvent(display, keycode, False, 0);
	XFlush(display);
	//compile with -lX11 -lXtst
	//gcc my-program.c $(pkg-config --cflags --libs x11) -o my-program
	//codes: http://www.virtualbox.org/svn/vbox/trunk/src/VBox/Frontends/VirtualBox/src/platform/x11/XKeyboard-new.cpp
#endif

//#define VK_UP
//#define VK_DOWN
//#define VK_LEFT
//#define VK_RIGHT
//#define VK_RETURN
//#define VK_BACK
//#define VK_MEDIA_PLAY_PAUSE
//#define VK_MEDIA_PLAY_PAUSE
//#define VK_MEDIA_STOP
//#define VK_VOLUME_UP
//#define VK_VOLUME_DOWN
//#define VK_VOLUME_MUTE
//#define VK_SLEEP

FILE *serial_port;

int open_serial(char *serial_port_name);
int read_serial();
int click_key(int key);
int serial_to_key(char *key_string);

int main(int argc, char *argv[]){
	open_serial(argv[1]);
	read_serial();
	return 0;
}

int open_serial(char *serial_port_name){
	printf("Connecting to %s.\n", serial_port_name);
	fflush(stdout);
    serial_port = fopen(serial_port_name,"r");
    if (serial_port == NULL)
    {
        /* Could not open the port. */
        printf("Unable to open %s.\n", serial_port_name);
        fflush(stdout);
        return -1;
    }
    else{
    	printf("Port opened %s.\n", serial_port_name);
    	fflush(stdout);
    	return 0;
    }
}

int read_serial(){
	char buffer[32];

	while((fgets(buffer, sizeof(buffer), serial_port)) != NULL){
    	//printf("%s",buffer);
    	serial_to_key(buffer);
		fflush(stdout);
    }
    return 0;
}

int click_key(int key){
	keybd_event(key, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);
	keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
	return 0;
}

int serial_to_key(char *key_string){
	if(strcmp(key_string, "UP\n")==0){
		click_key(VK_UP);
		printf("Up arrow.\n");
	}
	else if(strcmp(key_string, "DOWN\n")==0){
		click_key(VK_DOWN);
		printf("Down arrow.\n");
	}
	else if(strcmp(key_string, "LEFT\n")==0){
		click_key(VK_LEFT);
		printf("Left arrow.\n");
	}
	else if(strcmp(key_string, "RIGHT\n")==0){
		click_key(VK_RIGHT);
		printf("Right arrow.\n");
	}
	else if(strcmp(key_string, "OK\n")==0){
		click_key(VK_RETURN);
		printf("Ok.\n");
	}
	else if(strcmp(key_string, "BACK\n")==0){
		click_key(VK_BACK);
		printf("Back.\n");
	}
	else if(strcmp(key_string, "PLAY/PAUSE\n")==0){
		click_key(VK_MEDIA_PLAY_PAUSE);
		printf("Play/Pause.\n");
	}
	else if(strcmp(key_string, "STOP\n")==0){
		click_key(VK_MEDIA_STOP);
		printf("Stop.\n");
	}
	else if(strcmp(key_string, "NXTTRCK\n")==0){
		click_key(VK_MEDIA_NEXT_TRACK);
		printf("Next track.\n");
	}
	else if(strcmp(key_string, "PRVTRCK\n")==0){
		click_key(VK_MEDIA_PREV_TRACK);
		printf("Previous track.\n");
	}
	else if(strcmp(key_string, "VOLUP\n")==0){
		click_key(VK_VOLUME_UP);
		printf("Volume up.\n");
	}
	else if(strcmp(key_string, "VOLDOWN\n")==0){
		click_key(VK_VOLUME_DOWN);
		printf("Volume down.\n");
	}
	else if(strcmp(key_string, "MUTE\n")==0){
		click_key(VK_VOLUME_MUTE);
		printf("Volume mute.\n");
	}
	else if(strcmp(key_string, "SLEEP\n")==0){
		click_key(VK_SLEEP);
		printf("Sleep.\n");
	}
	else{
		printf("No matching key.\n");
		return -1;
	}
	return 0;
}