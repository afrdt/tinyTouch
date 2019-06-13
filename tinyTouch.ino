/* Use an ATtiny85 to control two squarewave oscillators that change frequency through touch.
 *
 * Circuit: 
 * ATtiny85 
 * Capacitive sensors on pins 3,4,1
 * 3 x 1.5 MΩ resistors between pins 2 and 3,4,1
 * Speaker-sound output on pin 0 (PWM pin for further developement of the code)
 *
 * April-May 2014
 * Revised on June 2019
 */

// include the Arduino CapSense library
#include <CapacitiveSensor.h>

// sound output connected to pin 0
#define speaker 0

// lower mid frequency oscillator variable
int LMFVal;

// low frequency oscillator variable
int LFVal;

// frequency duration variable
int duration;

// capacitive sensors
CapacitiveSensor yellow = CapacitiveSensor(2,3);        // 4.7 MΩ resistor between pins 2 and 3, pin 3 is the sensor pin
CapacitiveSensor orange = CapacitiveSensor(2,4);        // 4.7 MΩ resistor between pins 2 and 4, pin 4 is the sensor pin
CapacitiveSensor green = CapacitiveSensor(2,1);        // 4.7 MΩ resistor between pins 2 and 1, pin 1 is the sensor pin

// variables that hold the sensors' readings
long yellowVal;
long orangeVal;
long greenVal;

// initialization
void setup() {
  pinMode(speaker, OUTPUT);
  yellow.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
}

// loop over and over
void loop() {
  long start = millis();
  yellowVal = yellow.capacitiveSensor(10);
  orangeVal = orange.capacitiveSensor(10);
  greenVal = green.capacitiveSensor(10);

  LMFVal = constrain(yellowVal, 60, 880);
  LFVal = constrain(orangeVal, 60, 80);
  duration = constrain(greenVal, 10, 50);

  LMFOsc();
  LFOsc ();
}

// the sound generating function
void noise (unsigned char speakerPin, int frequencyInHertz, long timeInMilliseconds) {	 
  int x;	 
  long delayAmount = (long)(1000000/frequencyInHertz);
  long loopTime = (long)((timeInMilliseconds*1000)/(delayAmount*2));
  for (x=0;x<loopTime;x++) {	 
    digitalWrite(speakerPin,HIGH);
    delayMicroseconds(delayAmount);
    digitalWrite(speakerPin,LOW);
    delayMicroseconds(delayAmount);
  }	 
}

// a lower mid frequency oscillator
void LMFOsc () {
  noise(speaker, LMFVal, duration); 
}

// a lower frequency oscillator
void LFOsc () {
  noise(speaker, LFVal, duration); 
}

