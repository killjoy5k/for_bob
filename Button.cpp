#include "Arduino.h"
#include "Button.h"

// method for checking the status of the button
// when the flagPress = true button is pressed
// when the flagPress = false is free
// when you click flagClick = true
void Button::scanState() {

  if ( flagPress == !(digitalRead(_pin)) ) {
    // flagPress flag = current button state 
    // (inversion because the active state of the LOW button) 
    // i.e. button state remains the same 
    _buttonCount= 0; // reset acknowledge counter
  }
  else {
    // flagPress flag not = current button state 
    // button state changed
    _buttonCount++; // +1 to the acknowledge counter

    if ( _buttonCount >= _timeButton ) {
      // the state of the button did not change for the time _timeButton
      // the state of the button became stable
      flagPress= ! flagPress; // inversion of the state sign
      _buttonCount= 0; // reset acknowledge counter

      if ( flagPress == true ) flagClick= true; // sign of the button click 
    } 
  }
}

// method of setting pin number and time of acknowledgment
void Button::setPinTime(byte pin, byte timeButton) {
  _pin= pin;
  _timeButton= timeButton;
  pinMode(_pin, INPUT_PULLUP); // define the pin of the button as an input
}

// class constructor Button
Button::Button(byte pin, byte timeButton) {
  _pin= pin;
  _timeButton= timeButton;
  pinMode(_pin, INPUT_PULLUP); // define the pin of the button as an input
}
