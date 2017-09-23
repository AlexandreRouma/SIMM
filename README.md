# SIMM
SIMM RAM is a library for the Arduino MEGA 2560 that can ge used to control
30 pin SIMM RAM modules.

# First, Why ?!
I made this library mostly for fun, but I also had a use for it.
I needed to show changing images on a display, but it would take 2 or 3
seconds to update because I was loading them from an SD card. But with the
ram, I can just load the images to RAM on startup and read them very
quickly when I need them !

# Pros and cons:
Pros:
* VERY fast !
* A lot of storage compared to the internal ram of the arduino (can be up to 16Mb)
* No other components needed except the RAM module itself

Cons:
* Takes a bit of CPU power aprox. 16 times per second to refresh the RAM
* Uses a lot of wires (27 wires to be exact)

# How to use the library
You will need:
* An Arduino MEGA 2560
* A 30 pin SIMM RAM module
* Wires to connect it all up

The schematic:

* DQ0 - DQ7 -> PORTL
* A0 - A7 -> PORTA
* A8 -> Pin 37
* A9 -> Pin 36
* A10 -> Pin 35
* A11 -> Pin 34
* CAS -> Pin 32
* WE -> Pin 31
* RAS -> Pin 30

![SIMM_PINOUT](https://i.imgur.com/brw7Bud.png)
![ARDUINO_PORTS](https://i.imgur.com/UYL8Lah.png)
