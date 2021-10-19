#include "TRS_80_Keyboard.h"

TRS80Keyboard keyboard;
TRS80KeyboardEvent event;

void setup() {
  keyboard.begin();
  Serial.begin(9600);
  Serial.println("initialized");
}

void loop() {
  keyboard.getKeyEvent(&event);
  if(event.keyDown) {
    Serial.print("key pressed: ");
    Serial.println(event.key);
    Serial.println(event.modifiers);
    Serial.println(event.trsModifiers);
  }
}
