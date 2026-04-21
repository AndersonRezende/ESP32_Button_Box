#include "icons.h"
#include "USB.h"
#include "USBHIDKeyboard.h"
#include <Keypad.h>
#include <TFT_eSPI.h>

USBHIDKeyboard Keyboard;
TFT_eSPI tft = TFT_eSPI();

// ========================
// CONFIG TECLADO
// ========================
const byte ROWS = 4;
const byte COLS = 4;

char lastKey = 0;
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
// MAPA DE NOMES (para display)
// ========================
const char* getKeyName(char key) {
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
    
    default: return "DESCONHECIDO";
  }
}

// ========================
// SETUP
// ========================
void setup() {
  Serial.begin(115200);

  // Display
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);

  tft.drawCentreString("PAINEL ETS2", 160, 10, 4);

  // USB HID
  Keyboard.begin();
  USB.begin();
}

// ========================
// LOOP
// ========================
void loop() {
  char key = keypad.getKey();

  if (key && key != lastKey) {
    handleKeyboard(key);
    lastKey = key;
  }
}

// ========================
// AÇÃO
// ========================
void handleKeyboard(char key) {
  Serial.print("Tecla: ");
  Serial.println(key);

  // Envia tecla
  sendKey(key);

  // Atualiza display
  updateDisplay(key);
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
void updateDisplay(char key) {
  tft.fillRect(0, 80, 320, 160, TFT_BLACK);

  tft.setTextDatum(MC_DATUM);

  // Texto
  tft.setTextColor(TFT_YELLOW);
  tft.drawString("COMANDO", 160, 90, 2);

  tft.setTextColor(TFT_GREEN);
  tft.drawString(getKeyName(key), 160, 140, 4);

  // Ícones
  switch (key) {
    case 'e': 
      tft.pushImage(20, 100, 32, 32, icon_engine_start_1);
      break;
    case 'f': 
    tft.pushImage(20, 100, 32, 32, icon_hazard_on);
      break;
    case 'h': 
    tft.pushImage(20, 100, 32, 32, icon_engine_start_1);
      break;
    case 'i': 
    tft.pushImage(20, 100, 32, 32, icon_wipers_off);
      break;
    case 'k': 
    tft.pushImage(20, 100, 32, 32, icon_high_beam_on);
      break;
    case 'l': 
    tft.pushImage(20, 100, 32, 32, icon_low_beam_on);
      break;
    case 'm': 
    tft.pushImage(20, 100, 32, 32, icon_F5);
      break;
    case 'n': 
    tft.pushImage(20, 100, 32, 32, icon_engine_start_1);
      break;
    case 'o': 
    tft.pushImage(20, 100, 32, 32, icon_beacon_2_on);
      break;
    case 'p': 
    tft.pushImage(20, 100, 32, 32, icon_wipers_on);
      break;
    case 't': 
    tft.pushImage(20, 100, 32, 32, icon_trailer_on);
      break;
    case ']': 
    tft.pushImage(20, 100, 32, 32, icon_indicator_left_on);
      break;
    case '[': 
    tft.pushImage(20, 100, 32, 32, icon_indicator_right_on);
      break;
    case ' ': 
    tft.pushImage(20, 100, 32, 32, icon_parkbreak_on);
      break;
  }
}
