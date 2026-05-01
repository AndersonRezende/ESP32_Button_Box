#include "udp_listener.h"
#include <WiFiUdp.h>

static WiFiUDP udp;
static int udpPort;
static UdpCallback callback;

static char buffer[512];

void initUDP(const int port, UdpCallback cb) {
    udpPort = port;
    callback = cb;
    udp.begin(udpPort);
}

void updateUDP() {
    int packetSize = udp.parsePacket();

    if (packetSize) {
        int len = udp.read(buffer, sizeof(buffer) - 1);
        if (len > 0) {
            buffer[len] = '\0';
        }

        if (callback) {
            callback(buffer);
        }
    }
}