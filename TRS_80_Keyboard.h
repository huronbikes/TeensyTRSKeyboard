#ifndef TRS_80_KEYBOARD_H_
#define TRS_80_KEYBOARD_H_

#define KEY_BRACES KEY_LEFT_BRACE
#define KEY_LABEL KEY_HOME
#define KEY_PASTE KEY_END
#define KEY_CLR KEY_BACKSPACE
#define MODIFIERKEY_GRPH MODIFIERKEY_LEFT_ALT
#define MODIFIERKEY_CODE MODIFIERKEY_RIGHT_ALT

// NOTE that this refers to the pause/break key on the TRS 80 keyboard.  This is the name in the tech manual, typo
// and all.
#define MODIFIERKEY_BRAKE MODIFIERKEY_GUI
#define MODIFIERKEY_UNUSED 0
#define MODIFIERKEY_NUMLOCK MODIFIERKEY_UNUSED
#define MODIFIERKEY_CAPSLOK MODIFIERKEY_UNUSED

#define TRS_SHIFT 0x01
#define TRS_CTRL 0x02
#define TRS_GRPH 0x04
#define TRS_CODE 0x08
#define TRS_NUM 0x10
#define TRS_CAPS 0x20
#define TRS_BRAKE 0x80

#define KEYDOWN 0x01
#define KEYUP 0x02

#define ROWCOUNT 8
#define COLCOUNT 8

class TRS80KeyboardEvent {
  public:
    TRS80KeyboardEvent();
    void clear();    
    bool keyUp;
    bool keyDown;
    int key;
    int trsKey;
    int modifiers;
    int trsModifiers;
};

class TRS80Keyboard {
  public:
    TRS80Keyboard();
    void begin();
    void getKeyEvent(TRS80KeyboardEvent* event);
    bool numlockOn;
    bool capslockOn;
  private:
    int readKey();
    int readModifiers();
    int previousKey;
    int previousModifiers;
    int press(int modifierKey, int trsModifiers, int previousTrsModifiers);
    bool modifierOn(int modifierKey, int trsModifiers);
    static const int keymap[64];
    static const int modifiers[8];
    static const int rows[8];
    static const int cols[8];
};

#endif
