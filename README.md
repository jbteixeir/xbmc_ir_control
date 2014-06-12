#XBMC IR Control with TV Remote

Control XBMC using a arduino uno, IR sensor and your TV remote.

###Why?

Because my computer drivers do not support HDMI CEC (although the TV does), and arduino uno does not support sending keyboard strokes throught USB.

###The solution

Arduino recieves infrared signals form TV remote and sends codes to serial port.
A 'C' program on the computer reads the serial port codes and emulates the keystrokes.
Voilá!

----------------------
###Setting up the arduino
Just add a IR reciever to your favorite digital pin (make sure to change in the code the pin you choose).
Run the executable followed by the Serial port name (p.e. 'xbmcIR.exe COM0'(on windows) or './xbmcIR "tty/ACM0"'(on linux))

###Setting up the TV remote codes
Find out a way of knowing with TV remote button corresponds to which code.
Change the code in the arduino using the flags specified there.

###Keys Available
//Infrared code mapping
* UP
* DOWN
* LEFT
* RIGHT
* OK
* BACK
* PLAYPAUSE
* NXTTRCK
* PRVTRCK
* STOP
* VOLUP
* VOLDOWN
* MUTE
* SLEEP

###Compiling
* Linux: `gcc xbmcIR.c $(pkg-config --cflags --libs x11) -lXtst -o xbmcIR`
* Windows: `gcc xbmcIR.c`

###Addicional Notes
It's not yet fully tested, but it should work.
Contact me if you have any doubt.
