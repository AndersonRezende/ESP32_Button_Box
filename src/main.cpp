#include <Arduino.h>
#include "display/display.h"
#include "keyboard/keyboard.h"
#include "keypad/keypad.h"
#include "led/blink.h"
#include "utils/logger.h"
#include "wifi/wifi_manager.h"

void setupKeypadCallback();
void onUdpMessage(const char* data);

void setup() {
    initLogger(115200);
    logPrintln("Initializing ESP32 ETS2 Button Box...");

    initDisplay();
    initKeyboard();
    initBlink();
    initWiFi();
    setupKeypadCallback();
}

void loop() {
    wifiUpdate();
    updateKeyPad();
    updateBlink();
}

void setupKeypadCallback() {
    addKeyListener(logPrintln);
    addKeyListener(updateDisplay);
    addKeyListener(sendKeyboadKey);
    addKeyListener(onKeyPressed);
}

void onUdpMessage(const char* data) {
    logPrintln(data);
}
