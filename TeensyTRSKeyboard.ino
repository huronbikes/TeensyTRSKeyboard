#include "TRS_80_Keyboard.h"


TRS80Keyboard keyboard;
TRS80KeyboardEvent event;

void setup() {
  keyboard.begin();
  event.clear();
  Serial.begin(9600);
  Serial.println("initialized");
}

void loop() {
  keyboard.getKeyEvent(&event);

  if(event.keyDown) {
    Serial.print("key pressed: ");
  } else if(event.keyUp) {
    Serial.print("key released: ");
  }
  if(event.keyDown || event.keyUp) {  
    Serial.print(event.trsKey);
    Serial.print(" ");
    Serial.print(event.key);
    Serial.print(" ");
    Serial.println(event.modifiers);
    Serial.println(event.trsModifiers);
  }
}
