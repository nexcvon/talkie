
#include <WiFi.h>

#include "talkie/wifi.h"

void on_connected(WiFiEvent_t event, WiFiEventInfo_t info)
{
    IPAddress ip = WiFi.localIP();
    Serial.print("Wi-Fi connected: ");
    Serial.println(ip);
}

void on_disconnected(WiFiEvent_t event, WiFiEventInfo_t info)
{
    WiFi.disconnect();
    WiFi.reconnect();
    Serial.println("Wi-Fi reconnect");
}

void wifi_begin()
{
    WiFi.onEvent(on_connected, SYSTEM_EVENT_STA_CONNECTED);
    WiFi.onEvent(on_disconnected, SYSTEM_EVENT_STA_DISCONNECTED);

    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSPHRASE);

    Serial.println("Wi-Fi begin");
}
