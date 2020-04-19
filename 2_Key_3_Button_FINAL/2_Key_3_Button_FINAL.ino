//----------------------------------------------------------------------------------
#include <USBKeyboard.h>

#define BL       11
#define BR       10
#define B1       A5
#define B2       12
#define B3       9
#define LAYOUT   LAYOUT_US

int State1, State2, State3, StateR, StateL;
int holdR, holdL, oldR, oldL;
USBKeyboard nonoKey = USBKeyboard();

//----------------------------------------------------------------------------------
void setup() {
  TIMSK = 0;        // MEGA8
  //TIMSK0 = 0;     // MEGA328
  pinMode(BL, INPUT_PULLUP);
  pinMode(BR, INPUT_PULLUP);
  pinMode(B1, INPUT_PULLUP);
  pinMode(B2, INPUT_PULLUP);
  pinMode(B3, INPUT_PULLUP);
}
//----------------------------------------------------------------------------------
void loop() {
  nonoKey.update();
  if (digitalRead(BL) == LOW and StateL == LOW) {
    nonoKey.sendReport(0, nonoKey.asciiToKeycode('z'), 0, 0, 0, 0, 0); StateL = HIGH;
  }
  if (digitalRead(BR) == LOW and StateR == LOW) {
    nonoKey.sendReport(0, nonoKey.asciiToKeycode('x'), 0, 0, 0, 0, 0); StateR = HIGH;
  }
  if (digitalRead(B1) == LOW and State1 == LOW) {
    nonoKey.sendKeys(0x51, 0, 0, 0, 0, 0); State1 = HIGH;
  }
  if (digitalRead(B2) == LOW and State2 == LOW) {
    nonoKey.sendKeys(0x29, 0, 0, 0, 0, 0); State2 = HIGH;
  }
  if (digitalRead(B3) == LOW and State3 == LOW) {
    nonoKey.sendKeys(0x52, 0, 0, 0, 0, 0); State3 = HIGH;
  }

  //-----------------------------------------------------------------------
  if (holdL > 50) {
    holdL = 100;
    if (oldL > 10) {
      nonoKey.sendReport(0, nonoKey.asciiToKeycode('z'), 0, 0, 0, 0, 0); oldL = 0;
    }
  }
  if (holdR > 50) {
    holdR = 100;
    if (oldR > 10) {
      nonoKey.sendReport(0, nonoKey.asciiToKeycode('x'), 0, 0, 0, 0, 0); oldR = 0;
    }
  }



  //-----------------------------------------------------------------------

  if (digitalRead(BL) == HIGH and digitalRead(BR) == HIGH) {
    nonoKey.sendReport(0, 0, 0, 0, 0, 0, 0);
  }

  if (digitalRead(BL) == HIGH) {
    StateL = LOW; oldL = 0; holdL = 0;
    if (digitalRead(BR) == LOW) {
      nonoKey.sendReport(0, nonoKey.asciiToKeycode('x'), 0, 0, 0, 0, 0);
    }
  }
  if (digitalRead(BR) == HIGH) {
    StateR = LOW; oldR = 0; holdR = 0;
    if (digitalRead(BL) == LOW) {
      nonoKey.sendReport(0, nonoKey.asciiToKeycode('z'), 0, 0, 0, 0, 0);
    }
  }
  if (digitalRead(B1) == HIGH) {
    State1 = LOW;
  }
  if (digitalRead(B2) == HIGH) {
    State2 = LOW;
  }
  if (digitalRead(B3) == HIGH) {
    State3 = LOW;
  }

  delayMicroseconds(20000);
  holdL = holdL + 1;
  holdR = holdR + 1;
  oldL = oldL + 1;
  oldR = oldR + 1;
}
//----------------------------------------------------------------------------------
