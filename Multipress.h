#ifndef Multipress_h // if the Button library is not connected
#define Multipress_h // then connect it

#include "Arduino.h"

#define PUSH_BUTTON_LONG_PRESS_TIME 1000
#define PUSH_BUTTON_WINDOW_TIME 500

// signal processing class
class Multipress {
  public:
    Multipress(); // constructor
    int menu(boolean &flagClick, boolean &flagPress, boolean &pop); // -> signals: in, in, out
    boolean lp; // window time to push button again is active    
  private:
    boolean _overload; // window time to push button again is active
    int _count; // number of button presses
    int _lastCount; // number of button presses 
    int _cmd_item;   
    long _wdwTimeBegin;
};
#endif
