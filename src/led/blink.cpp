#include <esp32-hal.h>

#define LED_LEFT_ARROW 17
#define LED_RIGHT_ARROW 18

unsigned long lastBlink = 0;
bool blinkState = false;
bool leftArrow = false;
bool rightArrow = false;
bool hazardLights = false;

void initBlink() {
    pinMode(LED_LEFT_ARROW, OUTPUT);
    pinMode(LED_RIGHT_ARROW, OUTPUT);

    digitalWrite(LED_LEFT_ARROW, LOW);
    digitalWrite(LED_RIGHT_ARROW, LOW);
}

void onKeyPressed(const char key) {
    switch (key) {
        case 'f':
            hazardLights = !hazardLights;
            leftArrow = false;
            rightArrow = false;
            break;
        case ']':
            leftArrow = !leftArrow;
            rightArrow = false;
            hazardLights = false;
            break;
        case '[':
            rightArrow = !rightArrow;
            leftArrow = false;
            hazardLights = false;
            break;
        default: ;
    }
}

void updateBlink() {
    if (millis() - lastBlink > 500) {
        if (hazardLights) {
            digitalWrite(LED_LEFT_ARROW, blinkState);
            digitalWrite(LED_RIGHT_ARROW, blinkState);
        }
        else if (leftArrow) {
            digitalWrite(LED_LEFT_ARROW, blinkState);
            digitalWrite(LED_RIGHT_ARROW, LOW);
        }
        else if (rightArrow) {
            digitalWrite(LED_RIGHT_ARROW, blinkState);
            digitalWrite(LED_LEFT_ARROW, LOW);
        }
        else {
            digitalWrite(LED_LEFT_ARROW, LOW);
            digitalWrite(LED_RIGHT_ARROW, LOW);
        }
        lastBlink = millis();
        blinkState = !blinkState;
    }
}
