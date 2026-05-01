#include "wifi_manager.h"
#include "wifi_events.h"
#include "wifi_udp.h"
#include <WiFi.h>

#define SSID "SSID"
#define PASSWORD "PASSWORD"

void initWiFi() {
    WiFi.onEvent(onWiFiEvent);
    WiFi.begin(SSID, PASSWORD);
}

void wifiUpdate() {
    udpUpdate();
}