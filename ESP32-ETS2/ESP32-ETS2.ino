#include <WiFi.h>
#include "config.h"
#include "icons.h"
#include "USB.h"
#include "USBHIDKeyboard.h"
#include <Keypad.h>
#include <TFT_eSPI.h>
#include "display/display.h"

#define LED_LEFT_ARROW 17
#define LED_RIGHT_ARROW 18

bool blinkState = false;
unsigned long lastBlink = 0;
bool leftArrow = false;
bool rightArrow = false;
bool hazardLights = false;


USBHIDKeyboard Keyboard;
TFT_eSPI tft = TFT_eSPI();

// ========================
// CONFIG TECLADO
// ========================
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'e', 'h', ']', 'm'},
  {' ', 'n', 'f', '+'},
  {'i', 'l', '[', '-'},
  {'p', 'k', 'o', 't'}
};

byte rowPins[ROWS] = {1, 2, 3, 4};
byte colPins[COLS] = {5, 6, 7, 8};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// ========================
// NAME MAP (for display)
// ========================
/*const char* getKeyName(char key) {
  switch (key) {
    case 'e': return "IGNICAO";
    case 'f': return "ALERTA";
    case 'h': return "BUZINA";
    case 'i': return "LIMPADOR -";
    case 'k': return "FAROL ALTO";
    case 'l': return "FAROL";
    case 'm': return "MAPA";
    case 'n': return "BUZINA A AR";
    case 'o': return "GIROFLEX";
    case 'p': return "LIMPADOR +";
    case 't': return "REBOQUE";
    case ']': return "SETA ESQ";
    case '[': return "SETA DIR";
    case ' ': return "FREIO MAO";
    case '+': return "VIDRO +";
    case '-': return "VIDRO -";
    
    default: return "DESCONHECIDO";
  }
}*/

// ========================
// SETUP
// ========================
void setup() {
  Serial.begin(115200);

  // Blinks
  pinMode(LED_LEFT_ARROW, OUTPUT);
  pinMode(LED_RIGHT_ARROW, OUTPUT);

  // Display
  /*tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);

  tft.drawCentreString("PAINEL ETS2", 160, 10, 4);*/

  initDisplay();

  // USB HID
  Keyboard.begin();
  USB.begin();
}

// ========================
// LOOP
// ========================
void loop() {
  char key = keypad.getKey();

  if (key && keypad.getState() == PRESSED) {
    handleKeyboard(key);
    updateDisplay(key);
  }

  updateBlink();
}

// ========================
// ACTION
// ========================
void handleKeyboard(char key) {
  Serial.print("Tecla: ");
  Serial.println(key);

  // Envia tecla
  sendKey(key);
}

void sendKey(char key) {
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

// ========================
// DISPLAY
// ========================
void updateDisplays(char key) {
  tft.fillRect(0, 80, 320, 160, TFT_BLACK);

  tft.setTextDatum(MC_DATUM);

  // Texto
  tft.setTextColor(TFT_YELLOW);
  tft.drawString("COMANDO", 160, 90, 2);

  tft.setTextColor(TFT_GREEN);
  tft.drawString(getKeyName(key), 160, 140, 4);

  // ICONS
  switch (key) {
    case 'e': 
      tft.pushImage(20, 100, ICON_WIDTH, ICON_HEIGH, icon_engine_start_1);
      break;
    case 'f': 
    tft.pushImage(20, 100, ICON_WIDTH, ICON_HEIGH, icon_hazard_on);
      hazardLights = !hazardLights;
      leftArrow = false;
      rightArrow = false;
      break;
    case 'h': 
    tft.pushImage(20, 100, ICON_WIDTH, ICON_HEIGH, icon_buzina);
      break;
    case 'i': 
    tft.pushImage(20, 100, ICON_WIDTH, ICON_HEIGH, icon_wipers_off);
      break;
    case 'k': 
    tft.pushImage(20, 100, ICON_WIDTH, ICON_HEIGH, icon_high_beam_on);
      break;
    case 'l': 
    tft.pushImage(20, 100, ICON_WIDTH, ICON_HEIGH, icon_low_beam_on);
      break;
    case 'm': 
    tft.pushImage(20, 100, ICON_WIDTH, ICON_HEIGH, icon_F5);
      break;
    case 'n': 
    tft.pushImage(20, 100, ICON_WIDTH, ICON_HEIGH, icon_buzina);
      break;
    case 'o': 
    tft.pushImage(20, 100, ICON_WIDTH, ICON_HEIGH, icon_beacon_on);
      break;
    case 'p': 
    tft.pushImage(20, 100, ICON_WIDTH, ICON_HEIGH, icon_wipers_on);
      break;
    case 't': 
    tft.pushImage(20, 100, ICON_WIDTH, ICON_HEIGH, icon_trailer_on);
      break;
    case ']': 
    tft.pushImage(20, 100, ICON_WIDTH, ICON_HEIGH, icon_indicator_left_on);
      leftArrow = !leftArrow;
      rightArrow = false;
      hazardLights = false;
      break;
    case '[': 
    tft.pushImage(20, 100, ICON_WIDTH, ICON_HEIGH, icon_indicator_right_on);
      rightArrow = !rightArrow;
      leftArrow = false;
      hazardLights = false;
      break;
    case ' ': 
    tft.pushImage(20, 100, ICON_WIDTH, ICON_HEIGH, icon_parkbreak_on);
      break;
    case '+': 
    tft.pushImage(20, 100, ICON_WIDTH, ICON_HEIGH, icon_window_left_up);
      break;
    case '-': 
    tft.pushImage(20, 100, ICON_WIDTH, ICON_HEIGH, icon_window_left_down);
      break;
  }
}

// ========================
// BLINKS
// ========================
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