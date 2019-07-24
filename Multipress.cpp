#include "Arduino.h"
#include "Multipress.h"

// class constructor Button
Multipress::Multipress() {

}

int Multipress::menu(boolean &flagClick, boolean &flagPress, boolean &pop) {
  if (_overload) {
    _count = 0;
    flagClick = false;
    flagPress = false;
    _cmd_item = 0;
    if ((millis() - _wdwTimeBegin) > (2 * PUSH_BUTTON_LONG_PRESS_TIME)) {
      _overload = false;
    }
    return 0;
  } else {
    if (flagClick) {
      _count++;
      flagClick = false;
      pop = true;
      _wdwTimeBegin = millis();
    }
    if (_count == 5) {
      _count = 0;
      _cmd_item = 0;
      _overload = true;
    }

    if (((millis() - _wdwTimeBegin) > PUSH_BUTTON_WINDOW_TIME) && !(flagPress)) {
      _cmd_item = _count;
      _count = 0;
    }


    if (((millis() - _wdwTimeBegin) > PUSH_BUTTON_LONG_PRESS_TIME) && (flagPress)) {
        _cmd_item = 6; // longpress
        lp = true;
        _count = 0;
        flagPress = false;
        flagClick = false;
        _overload = true;
    }

    //  return _cmd_item;
    if (_lastCount != _cmd_item) {            // only do output if the count has changed
      //do something
      return _cmd_item;
      _lastCount = _cmd_item;    // track last press count
    } else {
      _cmd_item = 0;
      return _cmd_item;
    }
  }
}
