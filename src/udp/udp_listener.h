#pragma once

typedef void (*UdpCallback)(const char* data);

void initUDP(int port, UdpCallback callback);
void updateUDP();