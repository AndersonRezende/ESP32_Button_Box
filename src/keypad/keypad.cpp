#include "keypad.h"
#define MAX_LISTENERS 5

constexpr byte ROWS = 4;
constexpr byte COLS = 4;

char keys[ROWS][COLS] = {
    {'e', 'h', ']', 'm'},
    {' ', 'n', 'f', '+'},
    {'i', 'l', '[', '-'},
    {'p', 'k', 'o', 't'}
};

byte rowPins[ROWS] = {1, 2, 3, 4};
byte colPins[COLS] = {5, 6, 7, 8};

auto keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

static KeyCallback listeners[MAX_LISTENERS];
static int count = 0;

void addKeyListener(const KeyCallback callback) {
    if (count < MAX_LISTENERS) {
        listeners[count++] = callback;
    }
}

void updateKeyPad() {
    const char key = keypad.getKey();
    if (key && keypad.getState() == PRESSED) {
        for (int i = 0; i < count; i++) {
            listeners[i](key);
        }
    }
}
