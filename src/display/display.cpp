#include <TFT_eSPI.h>
#include "icons.h"
#include "../utils.h"
#include "display.h"

TFT_eSPI display = TFT_eSPI();

void initDisplay() {
    display.init();
    display.setRotation(1);
    display.fillScreen(TFT_BLACK);
    display.setTextColor(TFT_WHITE, TFT_BLACK);
    display.drawCentreString("PAINEL ETS2", 160, 10, 4);
}

void updateDisplay(const char key) {
    display.fillRect(0, 80, 320, 160, TFT_BLACK);

    display.setTextDatum(MC_DATUM);

    // Texto
    display.setTextColor(TFT_YELLOW);
    display.drawString("COMANDO", 160, 90, 2);

    display.setTextColor(TFT_GREEN);
    display.drawString(getKeyName(key), 160, 140, 4);

    // ICONS
    switch (key) {
        case 'e':
            display.pushImage(20, 100, ICON_WIDTH, ICON_HEIGHT, icon_engine_start_1);
            break;
        case 'f':
            display.pushImage(20, 100, ICON_WIDTH, ICON_HEIGHT, icon_hazard_on);
            break;
        case 'h':
            display.pushImage(20, 100, ICON_WIDTH, ICON_HEIGHT, icon_buzina);
            break;
        case 'i':
            display.pushImage(20, 100, ICON_WIDTH, ICON_HEIGHT, icon_wipers_off);
            break;
        case 'k':
            display.pushImage(20, 100, ICON_WIDTH, ICON_HEIGHT, icon_high_beam_on);
            break;
        case 'l':
            display.pushImage(20, 100, ICON_WIDTH, ICON_HEIGHT, icon_low_beam_on);
            break;
        case 'm':
            display.pushImage(20, 100, ICON_WIDTH, ICON_HEIGHT, icon_F5);
            break;
        case 'n':
            display.pushImage(20, 100, ICON_WIDTH, ICON_HEIGHT, icon_buzina);
            break;
        case 'o':
            display.pushImage(20, 100, ICON_WIDTH, ICON_HEIGHT, icon_beacon_on);
            break;
        case 'p':
            display.pushImage(20, 100, ICON_WIDTH, ICON_HEIGHT, icon_wipers_on);
            break;
        case 't':
            display.pushImage(20, 100, ICON_WIDTH, ICON_HEIGHT, icon_trailer_on);
            break;
        case ']':
            display.pushImage(20, 100, ICON_WIDTH, ICON_HEIGHT, icon_indicator_left_on);
            break;
        case '[':
            display.pushImage(20, 100, ICON_WIDTH, ICON_HEIGHT, icon_indicator_right_on);
            break;
        case ' ':
            display.pushImage(20, 100, ICON_WIDTH, ICON_HEIGHT, icon_parkbreak_on);
            break;
        case '+':
            display.pushImage(20, 100, ICON_WIDTH, ICON_HEIGHT, icon_window_left_up);
            break;
        case '-':
            display.pushImage(20, 100, ICON_WIDTH, ICON_HEIGHT, icon_window_left_down);
            break;
    }
}
