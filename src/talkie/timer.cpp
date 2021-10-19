
#include <Arduino.h>
#include <ESP32TimerInterrupt.h>

#include "talkie/timer.h"

static ESP32Timer timer_0(0);

static byte playback_buffer[PLAYBACK_BUFFER_SIZE];

static unsigned int playback_head;
static unsigned int playback_tail;

void playback_write(const byte *data, size_t size)
{
    size_t n = 0;
    while (n < size)
    {
        size_t bb = playback_tail % PLAYBACK_BUFFER_SIZE;
        size_t nn = PLAYBACK_BUFFER_SIZE - bb;
        if (n + nn >= size)
            nn = size - n;
        memcpy(&playback_buffer[bb], data + n, nn);
        playback_tail += nn;
        n += nn;
    }
}

static void IRAM_ATTR handler_0()
{
    if (playback_head == playback_tail)
        return;
    byte b = playback_buffer[playback_head % PLAYBACK_BUFFER_SIZE];
    dacWrite(PLAYBACK_PIN_DAC, 128 + b);
    playback_head += 1;
}

void timer_0_begin()
{
    timer_0.attachInterruptInterval(31, handler_0); // 32000 Hz -> 31.25 us/frame
    Serial.println("Timer 0 begin");
}
