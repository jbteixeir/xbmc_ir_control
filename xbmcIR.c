/*
Remote control for XBMC
Maps serial commands to keyboard keystrokes
Author: José Teixeira - jbteixeir@gmail.com

For linux:
	compile with -lX11 -lXtst
	OR
	gcc my-program.c $(pkg-config --cflags --libs x11) -lXtst -o my-program

	keyboard codes: http://cgit.freedesktop.org/xorg/proto/x11proto/plain/keysymdef.h
	keyboard audio codes: http://code.haskell.org/X11/Graphics/X11/ExtraTypes/XF86.hsc

For windows:
	install linux (just kidding, work with both)
	keyboard codes: http://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx


For MacOS:
	comming soon
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

	int click_key(int key){
		keybd_event(key, 0, KEYEVENTF_EXTENDEDKEY | 0, 0);
		keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
		return 0;
	}
#endif

#ifdef linux
	#include <X11/Xlib.h>
	#include <X11/keysym.h>
	#include <X11/XF86keysym.h>
	#include <X11/extensions/XTest.h>
	
	Display *display;
	
	#define VK_UP XK_Up
    #define VK_DOWN XK_Down
    #define VK_LEFT XK_Left
    #define VK_RIGHT XK_Right
    #define VK_RETURN XK_Return
    #define VK_BACK XK_BackSpace
    #define VK_MEDIA_PLAY_PAUSE XF86XK_AudioPlay
    #define VK_MEDIA_NEXT_TRACK XF86XK_AudioNext
    #define VK_MEDIA_PREV_TRACK XF86XK_AudioPrev
    #define VK_MEDIA_STOP XF86XK_AudioStop
    #define VK_VOLUME_UP XF86XK_AudioRaiseVolume
    #define VK_VOLUME_DOWN XF86XK_AudioLowerVolume
    #define VK_VOLUME_MUTE XF86XK_AudioMute
    #define VK_SLEEP 13

    int click_key(int key){
    	display = XOpenDisplay(NULL);
		int keycode = XKeysymToKeycode(display, key);
		XTestFakeKeyEvent(display, keycode, True, 0);
		XTestFakeKeyEvent(display, keycode, False, 0);
		XFlush(display);
		return 0;
	}

#endif

FILE *serial_port;

int open_serial(char *serial_port_name);
int read_serial();
int serial_to_key(char *key_string);


int main(int argc, char *argv[]){
	open_serial(argv[1]);
    while(1)
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
	char buffer[100];

	while((fgets(buffer, sizeof(buffer), serial_port)) != NULL){

    	printf("%s\n",buffer);
    	serial_to_key(buffer);
    	fflush(stdout);
    	buffer[0] = '\0';
    }
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
    else if(strcmp(key_string, "LASTKEY\n")==0){
//		click_key(VK_SLEEP);
		printf("Last key.\n");
	}
	//else{
		//printf("No matching key.\n");
		//printf("%s", key_string);
		//return -1;
	//}
	fflush(stdout);
	return 0;
}
