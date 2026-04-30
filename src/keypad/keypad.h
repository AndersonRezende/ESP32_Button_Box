#pragma once
#include <Arduino.h>
#include <Keypad.h>

typedef void (*KeyCallback)(char);

void addKeyListener(KeyCallback callback);
void updateKeyPad();