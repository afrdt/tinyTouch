/* Use an ATtiny85 to play a simple squarewave oscillator that changes frequency through touch.
 *
 * Circuit: 
 * ATtiny85 
 * Capacitive sensors on pins 2,3,4
 * 3 x 4.7 MΩ resistors between pins 1 and 2,3,4
 * speaker-sound output on pin 0 (PWM pin for further developement of the code)
 *
 * March-April 2014
 */

// include the Arduino CapSense library
#include <CapacitiveSensor.h>

// sound output connected to pin 0
#define speaker 0

// frequency variable
int noiseVal;

// frequency duration variable
int duration;

// capacitive sensors
CapacitiveSensor yellow = CapacitiveSensor(1,3);        // 4.7 MΩ resistor between pins 1 and 3, pin 3 is the sensor pin
CapacitiveSensor orange = CapacitiveSensor(1,4);        // 4.7 MΩ resistor between pins 1 and 4, pin 4 is the sensor pin
CapacitiveSensor green = CapacitiveSensor(1,2);        // 4.7 MΩ resistor between pins 1 ans 2, pin 2 is the sensor pin

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

  noiseVal = constrain(yellowVal, 60, 880);
  duration = constrain(greenVal, 10, 50);

  makeNoise();
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

// our oscillator
void makeNoise () {
  noise(speaker, noiseVal, duration); 
}
