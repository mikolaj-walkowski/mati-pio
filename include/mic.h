#pragma once
#ifndef MIC_HEADER
#define MIC_HEADER

#define I2S_PORT I2S_NUM_0
// most microphones will probably default to left channel but you may need to
// tie the L/R pin low
#define I2S_MIC_CHANNEL I2S_CHANNEL_FMT_ONLY_LEFT

#define I2S_MIC_SERIAL_CLOCK GPIO_NUM_26
#define I2S_MIC_LEFT_RIGHT_CLOCK GPIO_NUM_22
#define I2S_MIC_SERIAL_DATA GPIO_NUM_21

#include <Arduino.h>
#include <driver/i2s.h>

#ifndef SAMPLE_BUFFER_SIZE
#define SAMPLE_BUFFER_SIZE 1024
#endif
#ifndef SAMPLE_RATE
#define SAMPLE_RATE 44100
#endif
void initMic() {

  i2s_config_t i2s_config = {
      .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
      .sample_rate = SAMPLE_RATE,
      .bits_per_sample = i2s_bits_per_sample_t(16),
      .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
      .communication_format = i2s_comm_format_t(I2S_COMM_FORMAT_STAND_I2S),
      .intr_alloc_flags = 0,
      .dma_buf_count = 9,
      .dma_buf_len = 1024,
      .use_apll = false,
      .tx_desc_auto_clear = false,
      .fixed_mclk = 0};

  i2s_pin_config_t i2s_mic_pins = {.bck_io_num = I2S_MIC_SERIAL_CLOCK,
                                   .ws_io_num = I2S_MIC_LEFT_RIGHT_CLOCK,
                                   .data_out_num = I2S_PIN_NO_CHANGE,
                                   .data_in_num = I2S_MIC_SERIAL_DATA};

  i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
  i2s_set_pin(I2S_NUM_0, &i2s_mic_pins);

  i2s_start(I2S_PORT);
  delay(500);
}

int getData(int32_t *data) {
  size_t bytes_read = 0;
  i2s_read(I2S_NUM_0, data, sizeof(int32_t) * SAMPLE_BUFFER_SIZE, &bytes_read,
           portMAX_DELAY);
  return bytes_read / sizeof(int32_t);
}

#endif
