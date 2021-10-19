
#include <Arduino.h>

#include "talkie/timer.h"
#include "talkie/wifi.h"
#include "talkie/i2s.h"
#include "talkie/mqtt.h"

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(PIN_PTT_BUTTON, INPUT);
    Serial.begin(9600);
    Serial.println("serial begin");
    timer_0_begin();
    i2s_1_begin();
    wifi_begin();
    mqtt_begin();
}

void loop()
{
    bool talking = digitalRead(PIN_PTT_BUTTON);
    digitalWrite(LED_BUILTIN, talking);
    mqtt_loop(talking);
}
