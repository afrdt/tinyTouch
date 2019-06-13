tinyTouch+-
===========

An embroidered 8-bit synthesizer based on the ATtiny85 that controls two squarewave oscillators that change frequency through touch. 
The synth has three capacitive sensors (made with conductive thread) and uses the Arduino CapSense library. 

Circuit:
1 x ATtiny85
1 x LilyPad Simple Power (different iterations: coin cell battery socket, or 3 x AAA socket with switch)
1 x 3.7V LiPo battery (+ connected to VCC pin and - to GND pin) (different iterations: 3V with CR2032 coin cell, or 4.5V with 3 x AAA batteries)
3 x Capacitive sensors (connected to digital pins 1, 3, 4)
3 x 1 MΩ resistors (between digital pin 2 and the sensors' pins) (different iterations: 1M - 4.7M Ohms resistors)
1 x 1/8" audio jack/speaker (audio output connected to digital pin 0)

* update: I have remade the synth by burning the ATtiny85 bootloader at 16MHz and it works great! I strongly recomment this addition.

