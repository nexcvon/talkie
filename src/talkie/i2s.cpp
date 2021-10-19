
#include <Arduino.h>
#include <driver/i2s.h>

#include "talkie/i2s.h"

static i2s_config_t i2s_1_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = I2S_1_SAMPLE_RATE,
    .bits_per_sample = I2S_1_BITS_PER_SAMPLE,
    .channel_format = I2S_1_CHANNEL_FORMAT,
    .communication_format = I2S_COMM_FORMAT_I2S,
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = I2S_1_DMA_BUFFER_COUNT,
    .dma_buf_len = I2S_1_DMA_BUFFER_LENGTH,
    .use_apll = false,
    .tx_desc_auto_clear = false,
    .fixed_mclk = 0,
};

static i2s_pin_config_t i2s_1_pin_config = {
    .bck_io_num = I2S_1_PIN_BCK,
    .ws_io_num = I2S_1_PIN_WS,
    .data_out_num = I2S_PIN_NO_CHANGE,
    .data_in_num = I2S_1_PIN_SDIN,
};

void i2s_1_begin()
{
    esp_err_t rc = i2s_driver_install(I2S_NUM_1, &i2s_1_config, 0, NULL);
    assert(rc == 0);
    rc = i2s_set_pin(I2S_NUM_1, &i2s_1_pin_config);
    assert(rc == 0);
    Serial.println("I2S 1 begin");
}

void i2s_1_read(void *dest, size_t size, size_t *bytes_read)
{
    i2s_read(I2S_NUM_1, dest, size, bytes_read, portMAX_DELAY);
}
