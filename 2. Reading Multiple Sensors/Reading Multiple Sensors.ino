/*
  Reading Multiple Sensors
  
  Push Button reading contains Debounce

  Each time the input pin goes from LOW to HIGH (e.g. because of a push-button
  press), the output pin is toggled from LOW to HIGH or HIGH to LOW. There's a
  minimum delay between toggles to debounce the circuit (i.e. to ignore noise).
  

*/

#include <DHT.h>
#include <LiquidCrystal.h>

// Constants won't change.
const int rightButtonPin = 12;    // right push button pin
const int leftButtonPin = 13;    // left push button pin
const int ledPin = 8;      // LED pin
const int dhtPin = 2;      // dht data pin
const int dhtType = DHT11; // set dht type

DHT dht(dhtPin, dhtType);

const int rs = 11;
const int en = 10;
const int d4 = 6;
const int d5 = 5;
const int d6 = 4;
const int d7 = 3;

const int heartbeatPin = 0;
const int magReedPin = 9;

const int photoResPin = 1;
const int metalTouchPin = 3;


LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Variables will change:
int ledState = LOW;         // the current state of the output pin
int rightButtonState;             // the current readRight from the input pin
int lastRightButtonState = LOW;   // the previous readRight from the input pin
int leftButtonState;             // the current readRight from the input pin
int lastLeftButtonState = LOW;   // the previous readRight from the input pin
int pageState = 1;  // variable for store the machine-state.
int minPage = 1;  // first page of LCD
int maxPage = 6;  // last page of LCD
double alpha = 0.75; // for heartbeat sensor
double change = 0.0; // for heartbeat sensor
double minval = 0.0; // for heartbeat sensor
double value = 0.0; // for heartbeat sensor
int rawValue = 0; // for heartbeat sensor
static double oldValue = 0; // for heartbeat sensor
static double oldChange = 0; // for heartbeat sensor

String magReedVal = "ON"; // for magnetic reed sensor

int photoResValue = 0;

float metalTouchValue = 0.0;

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() {
  pinMode(rightButtonPin, INPUT);
  pinMode(leftButtonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(metalTouchPin, INPUT);

  // set initial LED state
  digitalWrite(ledPin, ledState);

  dht.begin();
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
}

void loop() {
  // read the state of the switch into a local variable:
  int readRight = digitalRead(rightButtonPin);
  int readLeft = digitalRead(leftButtonPin);

  debounce(readRight, readLeft);
  displayLEDPage();
  readHeartbeat();
  readMagReed();
  readPhotoRes();
  readMetalTouch();
  // set the LED:
  digitalWrite(ledPin, ledState);

  // save the readRight. Next time through the loop, it'll be the lastRightButtonState:
  lastRightButtonState = readRight;
  lastLeftButtonState = readLeft;

  lcd.clear();
}

void debounce(int readRight, int readLeft) {
  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (readRight != lastRightButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if (readLeft != lastLeftButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the readRight is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (readRight != rightButtonState) {
      rightButtonState = readRight;

      // only toggle the LED if the new button state is HIGH
      if (rightButtonState == HIGH) {
        if (pageState < maxPage) {
          pageState++;
        } else {
          pageState = minPage;
        }
      }
    }

    // if the button state has changed:
    if (readLeft != leftButtonState) {
      leftButtonState = readLeft;

      // only toggle the LED if the new button state is HIGH
      if (leftButtonState == HIGH) {
        if (pageState > 1) {
          pageState--;
        } else {
          pageState = maxPage;
        }
      }
    }
  }
}

void displayLEDPage() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  switch (pageState) {
    case 1:
      lcd.setCursor(0, 0);
      lcd.print("Humidity: ");
      lcd.setCursor(0, 1);
      lcd.print(h);
      lcd.print("%");
      break;
    case 2:
      lcd.setCursor(0, 0);
      lcd.print("Temperature: ");
      lcd.setCursor(0, 1);
      lcd.print(dht.computeHeatIndex(t, h, false));
      lcd.print((char)223);
      lcd.print("C");
      break;
    case 3:
      lcd.setCursor(0, 0);
      lcd.print("Heartbeat: ");
      lcd.setCursor(0, 1);
      lcd.print(value);
      lcd.print(", ");
      lcd.print(rawValue);
      break;
    case 4:
      lcd.setCursor(0, 0);
      lcd.print("Magnetic Reed: ");
      lcd.setCursor(0, 1);
      lcd.print(magReedVal);
      break;
    case 5:
      lcd.setCursor(0, 0);
      lcd.print("Photo Resistor: ");
      lcd.setCursor(0, 1);
      lcd.print(photoResValue);
      break;
    case 6:
      lcd.setCursor(0, 0);
      lcd.print("Metal Touch: ");
      lcd.setCursor(0, 1);
      lcd.print(metalTouchValue);
      break;
    default:
      lcd.print("Page Default");
      break;
  }
  delay(30);
}

void readHeartbeat() {
  rawValue = analogRead (heartbeatPin);
  value = alpha * oldValue + (1 - alpha) * rawValue;
  oldValue = value;
}

void readMagReed() {
  switch (digitalRead(magReedPin)) {
    case 1:
      magReedVal = "OFF";
      ledState = LOW;
      break;
    case 0:
      magReedVal = "ON";
      ledState = HIGH;
      break;
    default:
      magReedVal = "OFF";
      break;
  }
  
}

void readPhotoRes() {
  photoResValue = analogRead(photoResPin);
}

void readMetalTouch() {
  metalTouchValue = analogRead(metalTouchPin);
}
