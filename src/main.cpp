#include <Arduino.h>
#include "display/display.h"
#include "keyboard/keyboard.h"
#include "keypad/keypad.h"
#include "led/blink.h"
#include "utils/logger.h"

void setupKeypadCallback();

void setup() {
    initLogger(115200);
    logPrintln("Initializing ESP32 ETS2 Button Box...");

    initDisplay();
    initKeyboard();
    initBlink();
    setupKeypadCallback();
}

void loop() {
    updateKeyPad();
    updateBlink();
}

void setupKeypadCallback() {
    addKeyListener(logPrintln);
    addKeyListener(updateDisplay);
    addKeyListener(sendKeyboadKey);
    addKeyListener(onKeyPressed);
}