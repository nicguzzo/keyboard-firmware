#ifndef KEYBOARD_h
#define KEYBOARD_h

#include "./usb.h"
#include "usbd_hid.h"


#define MODIFIER_SHIFT 0x02

#define IS_KEY_CODE 0x80

//USB key code
enum {
    KEY_A = IS_KEY_CODE + 4,
    KEY_B = IS_KEY_CODE + 5,
    KEY_C = IS_KEY_CODE + 6,
    KEY_D = IS_KEY_CODE + 7,
    KEY_E = IS_KEY_CODE + 8,
    KEY_F = IS_KEY_CODE + 9,
    KEY_G = IS_KEY_CODE + 10,
    KEY_H = IS_KEY_CODE + 11,
    KEY_I = IS_KEY_CODE + 12,
    KEY_J = IS_KEY_CODE + 13,
    KEY_K = IS_KEY_CODE + 14,
    KEY_L = IS_KEY_CODE + 15,
    KEY_M = IS_KEY_CODE + 16,
    KEY_N = IS_KEY_CODE + 17,
    KEY_O = IS_KEY_CODE + 18,
    KEY_P = IS_KEY_CODE + 19,
    KEY_Q = IS_KEY_CODE + 20,
    KEY_R = IS_KEY_CODE + 21,
    KEY_S = IS_KEY_CODE + 22,
    KEY_T = IS_KEY_CODE + 23,
    KEY_U = IS_KEY_CODE + 24,
    KEY_V = IS_KEY_CODE + 25,
    KEY_W = IS_KEY_CODE + 26,
    KEY_X = IS_KEY_CODE + 27,
    KEY_Y = IS_KEY_CODE + 28,
    KEY_Z = IS_KEY_CODE + 29,
    KEY_1 = IS_KEY_CODE + 30,
    KEY_2 = IS_KEY_CODE + 31,
    KEY_3 = IS_KEY_CODE + 32,
    KEY_4 = IS_KEY_CODE + 33,
    KEY_5 = IS_KEY_CODE + 34,
    KEY_6 = IS_KEY_CODE + 35,
    KEY_7 = IS_KEY_CODE + 36,
    KEY_8 = IS_KEY_CODE + 37,
    KEY_9 = IS_KEY_CODE + 38,
    KEY_0 = IS_KEY_CODE + 39,
    KEY_ENTER = IS_KEY_CODE + 40,
    KEY_ESCAPE = IS_KEY_CODE + 41,
    KEY_DELETE = IS_KEY_CODE + 42,
    KEY_TAB = IS_KEY_CODE + 43,
    KEY_SPACE = IS_KEY_CODE + 44,
    KEY_MINUS = IS_KEY_CODE + 45,
    KEY_EQUALS = IS_KEY_CODE + 46,
    KEY_LEFTBRACKET = IS_KEY_CODE + 47,
    KEY_RIGHTBRACKET = IS_KEY_CODE + 48,
    KEY_BACKSLASH = IS_KEY_CODE + 49,
    KEY_SEMICOLON = IS_KEY_CODE + 51,
    KEY_QUOTE = IS_KEY_CODE + 52,
    KEY_GRAVE = IS_KEY_CODE + 53,
    KEY_COMMA = IS_KEY_CODE + 54,
    KEY_PERIOD = IS_KEY_CODE + 55,
    KEY_SLASH = IS_KEY_CODE + 56,
    KEY_CAPSLOCK = IS_KEY_CODE + 57,
    KEY_F1 = IS_KEY_CODE + 58,
    KEY_F2 = IS_KEY_CODE + 59,
    KEY_F3 = IS_KEY_CODE + 60,
    KEY_F4 = IS_KEY_CODE + 61,
    KEY_F5 = IS_KEY_CODE + 62,
    KEY_F6 = IS_KEY_CODE + 63,
    KEY_F7 = IS_KEY_CODE + 64,
    KEY_F8 = IS_KEY_CODE + 65,
    KEY_F9 = IS_KEY_CODE + 66,
    KEY_F10 = IS_KEY_CODE + 67,
    KEY_F11 = IS_KEY_CODE + 68,
    KEY_F12 = IS_KEY_CODE + 69,
    KEY_PRINTSCREEN = IS_KEY_CODE + 70,
    KEY_SCROLLLOCK = IS_KEY_CODE + 71,
    KEY_PAUSE = IS_KEY_CODE + 72,
    KEY_INSERT = IS_KEY_CODE + 73,
    KEY_HOME = IS_KEY_CODE + 74,
    KEY_PAGEUP = IS_KEY_CODE + 75,
    KEY_DELETEFORWARD = IS_KEY_CODE + 76,
    KEY_END = IS_KEY_CODE + 77,
    KEY_PAGEDOWN = IS_KEY_CODE + 78,
    KEY_RIGHT = IS_KEY_CODE + 79,
    KEY_LEFT = IS_KEY_CODE + 80,
    KEY_DOWN = IS_KEY_CODE + 81,
    KEY_UP = IS_KEY_CODE + 82,
    KP_NUMLOCK = IS_KEY_CODE + 83,
    KP_DIVIDE = IS_KEY_CODE + 84,
    KP_MULTIPLY = IS_KEY_CODE + 85,
    KP_SUBTRACT = IS_KEY_CODE + 86,
    KP_ADD = IS_KEY_CODE + 87,
    KP_ENTER = IS_KEY_CODE + 88,
    KP_1 = IS_KEY_CODE + 89,
    KP_2 = IS_KEY_CODE + 90,
    KP_3 = IS_KEY_CODE + 91,
    KP_4 = IS_KEY_CODE + 92,
    KP_5 = IS_KEY_CODE + 93,
    KP_6 = IS_KEY_CODE + 94,
    KP_7 = IS_KEY_CODE + 95,
    KP_8 = IS_KEY_CODE + 96,
    KP_9 = IS_KEY_CODE + 97,
    KP_0 = IS_KEY_CODE + 98,
    KP_DOT = IS_KEY_CODE + 99,
    KEY_NONUSBACKSLASH = IS_KEY_CODE + 100,
    KP_EQUALS = IS_KEY_CODE + 103,
};

typedef struct {
    HIDDevice_t device;
    uint8_t report[9];
}keyboard_t;
        
void keyboard_press(uint8_t ch);
void keyboard_release(uint8_t ch);

size_t keyboard_write(uint8_t ch);

void keyboard_pressScanCode(uint8_t keyCode);
void keyboard_releaseScanCode(uint8_t keyCode);
void keyboard_setModifiers(uint8_t modifiers);
        
void init_keyboard();

extern keyboard_t keyboard;

#endif
