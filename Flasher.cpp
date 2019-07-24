#include "Arduino.h"
#include "Flasher.h"

Flasher::Flasher(int pin, long on, long off) {
  _ledPin = pin;
  pinMode(_ledPin, OUTPUT);

  _OnTime = on;
  _OffTime = off;

  _ledState = LOW;
  _previousMillis = 0;
}

void Flasher::Update() {
  // check to see if it's time to change the state of the LED
  unsigned long _currentMillis = millis();
  if ((pop == true) && (_ledState == LOW)) {
    _ledState = HIGH;  // turn it on
    _previousMillis = _currentMillis;   // Remember the time
    digitalWrite(_ledPin, _ledState);   // Update the actual LED
  }
  if ((pop == true) && (_currentMillis - _previousMillis >= POP_LED_INTERVAL)) {
    _ledState = LOW;  // Turn it off
    digitalWrite(_ledPin, _ledState);  // Update the actual LED
    pop = false;
  }
}
