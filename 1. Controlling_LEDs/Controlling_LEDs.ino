/* Potentiometer Analog Read to LEDs
 * ------------------ 
 *
 * Turning the potentiometer changes which LED turns on according 
 * to the value obtained by analogRead(). 
 *
 * Created 12 April 2020
 *
 */

int potPin = 0;    // select the input pin for the Potentiometer
int ledPin1 = 6;   // select the pin for the Red LED
int ledPin2 = 5;   // select the pin for the Yellow LED
int ledPin3 = 4;   // select the pin for the Teal LED
int ledPin4 = 3;   // select the pin for the Blue LED
int ledPin5 = 2;   // select the pin for the White LED
int analogPotPinVal = 0;       // variable to store the value coming from the sensor

void setup() {
  pinMode(ledPin1, OUTPUT);  // 
  pinMode(ledPin2, OUTPUT);  // 
  pinMode(ledPin3, OUTPUT);  // declare the ledPin1-5 as an OUTPUT
  pinMode(ledPin4, OUTPUT);  // 
  pinMode(ledPin5, OUTPUT);  // 
}

void loop() {
  analogPotPinVal = analogRead(potPin);    // read the value from the sensor
  if (analogPotPinVal >= 0 && analogPotPinVal < 204){
    turnOnLED(ledPin1);
  } else if (analogPotPinVal >= 204 && analogPotPinVal < 408) {
    turnOnLED(ledPin2);
  } else if (analogPotPinVal >= 408 && analogPotPinVal < 612) {
    turnOnLED(ledPin3);
  } else if (analogPotPinVal >= 612 && analogPotPinVal < 816) {
    turnOnLED(ledPin4);
  } else {
    turnOnLED(ledPin5);
  }
}

void turnOnLED(int pin) {
  for(int i = 2 ; i < 7 ; i++){
    digitalWrite(i, LOW);
  }
  digitalWrite(pin, HIGH);
}
