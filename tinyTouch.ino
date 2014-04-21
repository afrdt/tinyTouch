/* Use an ATtiny85 to play a simple squarewave oscillator that changes frequency through a capacitive sensor
 *
 * Circuit: 
 * ATtiny85 
 * Capacitive sensors on pins 2,3,4
 * 1 MΩ resistor on between pins 1 and 2,4
 * 4.7 MΩ resistor on between pins 1 and 3
 * speaker-sound output on pin 0 (PWM pin for further developement of the code)
 *
 * March-April 2014
 */

#include <CapacitiveSensor.h>

#define speaker 0

long yellowVal;
long orangeVal;
long greenVal;

int noiseVal;
int duration;

//for ATtiny
CapacitiveSensor yellow = CapacitiveSensor(1,3);        // 4.7 MΩ resistor between pins, pin 3 is sensor pin
CapacitiveSensor orange = CapacitiveSensor(1,4);        // 4.7 MΩ resistor between pins, pin 3 is sensor pin
CapacitiveSensor green = CapacitiveSensor(1,2);        // 4.7 MΩ resistor between pins, pin 3 is sensor pin

void setup() {
  pinMode(speaker, OUTPUT);
  yellow.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
}

void loop() {
  long start = millis();
  yellowVal = yellow.capacitiveSensor(10);
  orangeVal = orange.capacitiveSensor(10);
  greenVal = green.capacitiveSensor(10);

  noiseVal = constrain(yellowVal, 60, 880);
  duration = constrain(greenVal, 10, 50);

  makeNoise();
}

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

void makeNoise () {
  noise(speaker, noiseVal, duration); 
}

