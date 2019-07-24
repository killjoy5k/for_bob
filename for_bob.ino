//---------------------------------------------------------------------------------//
#include "Keyboard.h"
char ctrlKey = KEY_LEFT_CTRL;

//---------------------------------------------------------------------------------//
#include "Mouse.h"

//---------------------------------------------------------------------------------//
#include "Flasher.h"
#define LED_0_PIN 13 // LED0 is connected to pin 13
#define LED_1_PIN A5 // LED1 is connected to pin A1
Flasher LED_0(LED_0_PIN, 500, 500);
Flasher LED_1(LED_1_PIN, 500, 500);

//---------------------------------------------------------------------------------//
#include "Button.h"
#define BUTTON_1_PIN A4 // button1 is connected to pin 
#define BUTTON_2_PIN 7  // button2 is connected to pin 
#define BUTTON_DEBOUNCE_TIME 15
Button button1(BUTTON_1_PIN, BUTTON_DEBOUNCE_TIME); // create an object for button 1
Button button2(BUTTON_2_PIN, BUTTON_DEBOUNCE_TIME); // create an object for button 2

//---------------------------------------------------------------------------------//
#include "Multipress.h"
Multipress MP0;
Multipress MP1;

//-------------------------------wiggle--------------------------------------------//
const int wiggle_interval = 5000;
const int little_wiggle_interval = 100;
unsigned long previousWiggle = 0;
unsigned long previousLittleWiggle = 0;
bool wiggle_bits;
int wiggle_itr;
bool wiggle = false;

//---------------------------------------------------------------------------------//
// Returns if it has been more than interval (in ms) ago. Used for periodic actions
bool hasExpired(unsigned long &prevTime, unsigned long interval) {
  if (  millis() - prevTime > interval )
  {
    prevTime = millis();
    return true;
  }
  else
    return false;
}

void setup() {
  // put your setup code here, to run once:

  //  Serial.begin(115200);
  //  while (! Serial); // Wait until Serial is ready - Leonardo
  //  if (Serial) {
  //    Serial.println("Serial interface started");
  //  }

}

void loop() {
  // put your main code here, to run repeatedly:
  button1.scanState(); // call the method of scanning button1 signal
  button2.scanState(); // call the method of scanning button2 signal

  switch (MP0.menu(button1.flagClick, button1.flagPress, LED_1.pop)) {
    case 0:
      break;
    case 1:
      wiggle = ! wiggle;
      break;
    case 2:          //Ctrl - b
      Keyboard.press(ctrlKey);
      Keyboard.press('b');
      delay(100);
      Keyboard.releaseAll();
      break;
    case 3:          //synchronize-panes off
      Keyboard.press(ctrlKey);
      Keyboard.press('b');
      delay(100);
      Keyboard.releaseAll();
      Keyboard.println(F(":setw synchronize-panes off"));
      break;
    case 4:          //synchronize-panes
      Keyboard.press(ctrlKey);
      Keyboard.press('b');
      delay(100);
      Keyboard.releaseAll();
      Keyboard.println(F(":setw synchronize-panes"));
      break;
    case 6:
      Keyboard.println(F("https://github.com/killjoy5k/for_bob"));
      break;

    default: break;
  }

  switch (MP1.menu(button2.flagClick, button2.flagPress, LED_1.pop)) {
    case 0:
      break;
    case 1:
      Keyboard.press(ctrlKey);
      Keyboard.press('v');
      delay(100);
      Keyboard.releaseAll();
      break;
    case 2:
      Keyboard.press(ctrlKey);
      Keyboard.press('c');
      delay(100);
      Keyboard.releaseAll();
      break;
    case 3:
      Keyboard.println(F("username"));
      break;
    case 4:
      Keyboard.print(F("password"));
      break;
    case 6:
      Keyboard.println(F("https://www.arduino.cc/en/main/software"));
      break;

    default: break;
  }

  if (wiggle) {
    if (hasExpired(previousWiggle, wiggle_interval)) // Toggle according to definition above, default 60
    {
      wiggle_bits = true;
      wiggle_itr = 1;
    }
    if (wiggle_bits) {
      if (hasExpired(previousLittleWiggle, little_wiggle_interval)) // Toggle according to definition above, default 60
      {
        switch (wiggle_itr) {
          case 1:
            Mouse.move(4, 0, 0);
            wiggle_itr++;
            LED_0.pop = true;
            break;
          case 2:
            Mouse.move(-8, 0, 0);
            wiggle_itr++;
            LED_0.pop = true;
            break;
          case 3:
            Mouse.move(4, 0, 0);
            wiggle_itr = 0;
            wiggle_bits = false;
            LED_0.pop = true;
            break;
          default:
            break;
        }
      }
    }
  }

  LED_0.Update();
  LED_1.Update();
}
