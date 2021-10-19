#include "TRS_80_Pinout.h"
#include "TRS_80_Keyboard.h"
#include <keylayouts.h>
#include <Wire.h>

TRS80KeyboardEvent::TRS80KeyboardEvent() {
  clear();
}

void TRS80KeyboardEvent::clear() {
  trsKey = -1;
  key = 0;
  modifiers = 0;
  trsModifiers = 0;
  keyDown = false;
  keyUp = false;
}

int TRS80Keyboard::readModifiers() {
  int result = 0;
  int flag = 1;
  digitalWrite(MODIFIER_COL, LOW);
  delay(1);
  for(int x = 0; x < ROWCOUNT; x++) {
    int readResult = digitalRead(rows[x]);
    if(readResult == LOW) {      
      result = result + flag;
    }
    flag = flag << 1;
  }
  digitalWrite(MODIFIER_COL, HIGH);  
  return result;
}

int TRS80Keyboard::readKey() {
  int result = -1;
  for(int x = 0; x < COLCOUNT; x++) {
    digitalWrite(cols[x], LOW);
    for(int y = 0; y < ROWCOUNT; y++) {
      if(digitalRead(rows[y]) == LOW) {
        result = y;
        break;
      }
    }
    digitalWrite(cols[x], HIGH);
    if(result >= 0) {
      return x + (8 * result);
    }
  }
  return result;
}

TRS80Keyboard::TRS80Keyboard() {
  previousKey = -1;
  previousModifiers = 0;
  capslockOn = false;
  numlockOn = false;
}

void TRS80Keyboard::begin() {
  for(int x = 0; x < COLCOUNT; x++) {
    pinMode(cols[x], OUTPUT);
    digitalWrite(cols[x], HIGH);
  }  
  pinMode(MODIFIER_COL, OUTPUT);
  digitalWrite(MODIFIER_COL, HIGH);
  
  for(int x = 0; x < ROWCOUNT; x++) {
    pinMode(rows[x], INPUT_PULLUP);
  }
};


int TRS80Keyboard::press(int trsModKey, int modifiers, int previousModifiers) {
  bool inModifiers = modifierOn(trsModKey, modifiers);
  bool inPreviousModifiers = modifierOn(trsModKey, previousModifiers);
  return inModifiers == inPreviousModifiers ? 0 : inModifiers ? -1 : 1;
}

bool TRS80Keyboard::modifierOn( int modifier, int trsModifiers) {
  return (trsModifiers & modifier) == modifier;
}

void TRS80Keyboard::getKeyEvent(TRS80KeyboardEvent *event) {
  event->clear();  
  int trsModifiers = readModifiers();
  delay(30);
  int trsKey = readKey();

  int modifiers = 0;
  modifiers += modifierOn(TRS_SHIFT, trsModifiers) ? MODIFIERKEY_SHIFT : 0;
  modifiers += modifierOn(TRS_GRPH, trsModifiers) ? MODIFIERKEY_GRPH : 0;
  modifiers += modifierOn(TRS_CODE, trsModifiers) ? MODIFIERKEY_CODE : 0;
  modifiers += modifierOn(TRS_CTRL, trsModifiers) ? MODIFIERKEY_CTRL : 0;
  modifiers += modifierOn(TRS_BRAKE, trsModifiers) ?  MODIFIERKEY_BRAKE : 0;

  int capsPress = press(TRS_CAPS, trsModifiers, previousModifiers);
  int numPress = press(TRS_NUM, trsModifiers, previousModifiers);
  
  bool keyDown = (trsKey != -1 && trsKey != previousKey) || 
    capsPress == -1 ||
    numPress == -1 ||
    trsModifiers > previousModifiers;
    
  bool keyUp = (previousKey != -1 && trsKey != previousKey) || 
    capsPress == 1 ||
    numPress == 1 ||
    trsModifiers < previousModifiers;

  int key = capsPress != 0 ? KEY_CAPS_LOCK : numPress != 0 ? KEY_NUM_LOCK : trsKey != -1 ? keymap[trsKey]: 0;

  event->keyDown = keyDown;
  event->keyUp = keyUp;
  event->key = key;
  event->modifiers = modifiers;
  event->trsKey = trsKey;
  event->trsModifiers = trsModifiers;
  
  previousKey = trsKey;
  previousModifiers = trsModifiers;
}

const int TRS80Keyboard::keymap[64] = {
  KEY_Z,  KEY_A,  KEY_Q,  KEY_O,          KEY_1,  KEY_9,      KEY_SPACE,  KEY_F1, 
  KEY_X,  KEY_S,  KEY_W,  KEY_P,          KEY_2,  KEY_0,      KEY_INSERT, KEY_F2,
  KEY_C,  KEY_D,  KEY_E,  KEY_BRACES,     KEY_3,  KEY_MINUS,  KEY_TAB,    KEY_F3,
  KEY_V,  KEY_F,  KEY_R,  KEY_SEMICOLON,  KEY_4,  KEY_EQUAL,  KEY_ESC,    KEY_F4,
  KEY_B,  KEY_G,  KEY_T,  KEY_QUOTE,      KEY_5,  KEY_DOWN,   KEY_LABEL,  KEY_F5,
  KEY_N,  KEY_H,  KEY_Y,  KEY_COMMA,      KEY_6,  KEY_UP,     KEY_PASTE,  KEY_F6,
  KEY_M,  KEY_J,  KEY_U,  KEY_PERIOD,     KEY_7,  KEY_LEFT,   KEY_CLR,    KEY_F7,
  KEY_L,  KEY_K,  KEY_I,  KEY_SLASH,      KEY_8,  KEY_RIGHT,  KEY_ENTER,  KEY_F8
};

const int TRS80Keyboard::rows[8] = {
  CN_WHITE_11,
  CN_WHITE_12,
  CN_WHITE_13,
  CN_WHITE_14,
  CN_WHITE_15,
  CN_WHITE_16,
  CN_WHITE_17,
  CN_WHITE_18,
};

const int TRS80Keyboard::cols[8] = {
  CN_BLACK_1,
  CN_BLACK_2,
  CN_BLACK_3,
  CN_BLACK_4,
  CN_BLACK_5,
  CN_BLACK_6,
  CN_BLACK_7,
  CN_BLACK_8,
};
