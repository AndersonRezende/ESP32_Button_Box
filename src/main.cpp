#include <Arduino.h>
#include <WiFi.h>
#include "display/display.h"
#include "keyboard/keyboard.h"
#include "keypad/keypad.h"
#include "led/blink.h"

void setupKeypadCallback();

void setup() {
    Serial.begin(115200);
    Serial.println("Initializing ESP32 ETS2 Button Box...");

    initDisplay();
    initKeyboard();
    initBlink();
    setupKeypadCallback();
}

void loop() {
    updateKeyPad();
    updateBlink();
}

void logKey(const char key) {
    Serial.println(key);
}

void setupKeypadCallback() {
    addKeyListener(logKey);
    addKeyListener(updateDisplay);
    addKeyListener(sendKeyboadKey);
    addKeyListener(onKeyPressed);
}