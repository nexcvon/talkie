
#include <Arduino.h>
#include <ArduinoUniqueID.h>
#include <PubSubClient.h>
#include <WiFi.h>

#include "talkie/i2s.h"
#include "talkie/mqtt.h"
#include "talkie/timer.h"
#include "talkie/wifi.h"

static char mqtt_id[7 + UniqueIDsize * 2 + 1];

static WiFiClient wifi_client;
static PubSubClient mqtt_client(wifi_client);

static void on_message(const char *topic, const byte *payload, unsigned int length)
{
    String topic2(topic);

    if (topic2 == "talkie/heartbeat")
    {
        if (strcmp(mqtt_id, (const char *)payload) != 0)
            mqtt_client.subscribe((const char *)payload);
        return;
    }

    // Serial.print(topic2);
    // Serial.print(' ');
    // Serial.print(length);
    // Serial.println();

    playback_write(payload, length);
}

void mqtt_begin()
{
    strcpy(mqtt_id, "talkie/");
    for (size_t i = 0; i < UniqueIDsize; ++i)
        sprintf(mqtt_id + 7 + i * 2, "%02x", UniqueID[i]);
    mqtt_id[7 + UniqueIDsize * 2] = 0;
    Serial.println(mqtt_id);

    mqtt_client.setCallback(on_message);
    mqtt_client.setServer(MQTT_BROKER_DOMAIN, MQTT_BROKER_PORT);
    mqtt_client.setSocketTimeout(1);
    mqtt_client.setBufferSize(1200);

    Serial.println("MQTT begin");
}

void mqtt_loop(bool talking)
{
    if (!mqtt_client.connected())
    {
        Serial.println("MQTT connect");
        if (!mqtt_client.connect(mqtt_id))
        {
            delay(1000);
            return;
        }

        Serial.println("MQTT subscribe");
        mqtt_client.subscribe("talkie/heartbeat");
        return;
    }

    if (talking)
    {
        byte buffer[I2S_1_DMA_BUFFER_LENGTH];
        size_t bytes_read = 0;
        i2s_1_read(buffer, I2S_1_DMA_BUFFER_LENGTH, &bytes_read);
        // Serial.println(bytes_read);
        // mqtt_client.publish("talkie/heartbeat", id);
        mqtt_client.publish(mqtt_id, buffer, bytes_read);
    }

    mqtt_client.loop();
}
