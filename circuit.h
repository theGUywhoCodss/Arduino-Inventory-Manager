#ifndef CIRCUIT_H
#define CIRCUIT_H

#include <Arduino.h>

class Circuit{
private:
  int LED_PIN = 0;
  int BUTTON1_PIN = 0;
  bool BUTTON1_STATUS = false;
  int BUTTON2_PIN = 0;
  bool BUTTON2_STATUS = false;
  int BUTTON3_PIN = 0;
  bool BUTTON3_STATUS = false;
  // Do display pins last I guess because IDk how many it needs
  int JOYSTICK_PIN = 0;
public:
  Circuit(int LEDPIN, int BUTTONPIN1, int BUTTONPIN2, int BUTTON3PIN): LED_PIN(LEDPIN), BUTTON2_PIN(BUTTONPIN2), BUTTON1_PIN(BUTTONPIN1), BUTTON3_PIN(BUTTON3PIN) {
    pinMode(LED_PIN, OUTPUT);
    pinMode(BUTTON1_PIN, INPUT);
    pinMode(BUTTON2_PIN, INPUT);
    pinMode(BUTTON3_PIN, INPUT);
  };
  void ledSet(bool condition){
    digitalWrite(LED_PIN, condition?HIGH:LOW);
  }

  // Button is pressed if it was originally off.
  bool isButton1Pressed(){
    if (!BUTTON1_STATUS && digitalRead(BUTTON1_PIN)){
      BUTTON1_STATUS = true;
      return true;
    }else if (!digitalRead(BUTTON1_PIN)){
      BUTTON1_STATUS = false;
    }
    return false;
  }
  bool isButton2Pressed(){
    if (!BUTTON2_STATUS && digitalRead(BUTTON2_PIN)){
      BUTTON2_STATUS = true;
      return true;
    }else if (!digitalRead(BUTTON2_PIN)){
      BUTTON2_STATUS = false;
    }
    return false;
  }
  bool isButton3Pressed(){
    if (!BUTTON3_STATUS && digitalRead(BUTTON3_PIN)){
      BUTTON3_STATUS = true;
      return true;
    }else if (!digitalRead(BUTTON3_PIN)){
      BUTTON3_STATUS = false;
    }
    return false;
  }
};
int countDigit(int n);

#endif    