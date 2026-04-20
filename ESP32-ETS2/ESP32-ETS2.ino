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

char keys[ROWS][COLS] = {
  {'h', 'n', '[', ']'},
  {'0', 'l', 'k', 'o'},
  {',', 'f', '.', 'm'},
  {' ', 'u', 'j', 't'}
};

byte rowPins[ROWS] = {1, 2, 3, 4};
byte colPins[COLS] = {5, 6, 7, 8};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// ========================
// MAPA DE NOMES (para display)
// ========================
const char* getKeyName(char key) {
  switch (key) {
    case 'h': return "BUZINA";
    case 'n': return "LIMPADOR";
    case '[': return "LIMPADOR -";
    case ']': return "LIMPADOR +";
    case '0': return "DESLIGAR";
    case 'l': return "FAROL BAIXO";
    case 'k': return "FAROL ALTO";
    case 'o': return "GIROFLEX";
    case ',': return "SETA ESQ";
    case '.': return "SETA DIR";
    case 'f': return "ALERTA";
    case 'm': return "MAPA";
    case ' ': return "FREIO MAO";
    case 'u': return "VIDRO SOBE";
    case 'j': return "VIDRO DESCE";
    case 't': return "REBOQUE";
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

  if (key) {
    handleKeyboard(key);
  }
}

// ========================
// AÇÃO
// ========================
void handleKeyboard(char key) {
  Serial.print("Tecla: ");
  Serial.println(key);

  // Envia tecla
  Keyboard.press(key);
  delay(20);
  Keyboard.releaseAll();

  // Atualiza display
  updateDisplay(key);
}

// ========================
// DISPLAY
// ========================
void updateDisplay(char key) {
  tft.fillRect(0, 80, 320, 100, TFT_BLACK);

  tft.setTextDatum(MC_DATUM);

  tft.drawString("COMANDO", 160, 90, 2);
  tft.drawString(getKeyName(key), 160, 120, 4);
}