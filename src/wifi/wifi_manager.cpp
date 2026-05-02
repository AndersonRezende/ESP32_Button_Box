#include "wifi_manager.h"
#include "wifi_events.h"
#include "wifi_udp.h"
#include <WiFi.h>

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASS;

void initWiFi() {
    WiFi.onEvent(onWiFiEvent);
    WiFi.begin(ssid, password);
}

void wifiUpdate() {
    udpUpdate();
}