#include <esp32-hal.h>
#include "USBHIDKeyboard.h"
#include "keyboard.h"

USBHIDKeyboard Keyboard;

void initKeyboard() {
    Keyboard.begin();
}

void sendKeyboadKey(const char key) {
    if (Keyboard.availableForWrite()) {
        switch (key) {
            case '+':
                Keyboard.press(KEY_LEFT_SHIFT);
                Keyboard.press('=');
                break;
            case '_':
                Keyboard.press(KEY_LEFT_SHIFT);
                Keyboard.press('-');
                break;
            default:
                Keyboard.press(key);
                break;
        }

        delay(20);
        Keyboard.releaseAll();
    }
}