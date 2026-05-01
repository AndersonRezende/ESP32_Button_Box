#include "wifi_udp.h"
#include <WiFiUdp.h>
#include "utils/logger.h"

WiFiUDP udp;
constexpr int udpPort = 25555;

char packetBuffer[512];

void udpInit() {
    udp.begin(udpPort);
    logPrintln("UDP iniciado");
}

void udpUpdate() {
    const int packetSize = udp.parsePacket();

    if (packetSize) {
        const int len = udp.read(packetBuffer, sizeof(packetBuffer) - 1);

        if (len > 0) {
            packetBuffer[len] = '\0';
        }

        logPrintln(packetBuffer);

        // Aqui você pode integrar com display/led/etc
    }
}