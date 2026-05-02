#include "wifi_events.h"
#include "wifi_udp.h"
#include "utils/logger.h"

auto onWiFiEvent(const WiFiEvent_t event) -> void {
    switch(event) {
        case ARDUINO_EVENT_WIFI_STA_CONNECTED:
            logPrintln("WiFi conectado");
            break;
        case ARDUINO_EVENT_WIFI_STA_GOT_IP:
            logPrintln("IP obtido");
            udpInit();
            break;
        case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
            logPrintln("WiFi desconectado");
            WiFi.reconnect();
            break;
        default:
            break;
    }
}
