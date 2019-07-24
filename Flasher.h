#ifndef Flasher_h // if the Flasher library is not connected
#define Flasher_h // then connect it

#include "Arduino.h"

#define POP_LED_INTERVAL 60

// signal processing class
class Flasher
{
    // Constructor - creates a Flasher
    // and initializes the member variables and state
  public:
    Flasher(int pin, long on, long off);
    boolean pop;   
    void Update();
  private:
    // Class Member Variables
    // These are initialized at startup
    int _ledPin;      // the number of the LED pin
    long _OnTime;     // milliseconds of on-time
    long _OffTime;    // milliseconds of off-time

    // These maintain the current state
    int _ledState;                 // ledState used to set the LED

    unsigned long _previousMillis;   // will store last time LED was updated
};
#endif
