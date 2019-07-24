#ifndef Button_h // if the Button library is not connected
#define Button_h // then connect it

#include "Arduino.h"

// signal processing class
class Button {
  public:
    Button(byte pin, byte timeButton); // constructor
    boolean flagPress; // sign button is pressed (low signal)
    boolean flagClick; // sign of a button click (front)
    void scanState(); // method waiting for a stable signal state
    void setPinTime(byte pin, byte timeButton); // set the output number and filter time

  private:
    byte _buttonCount; // filtering time counter 
    byte _timeButton; // filtering time
    byte _pin; // pin number
};
#endif
