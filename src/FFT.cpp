#include "FFT.h"
#include "HardwareSerial.h"
#include "Settings.h"
#include "esp32-hal.h"
#include "mic.h"

using namespace tFFT;

void tFFT::init(void *p) {
  initMic();
  for (int i = 0; i < ROWS; ++i) {
    maximums[i] = 1;
    curr[i] = 0;
  }
}

void calc() {
  for (int i = 0; i < SAMPLE_BUFFER_SIZE; i++) {
    vReal[i] = (rawSamples[i] >> 16) * 3.3 / 4096.0;
    vImg[i] = 0.f;
  }
  fft.Windowing(FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  fft.Compute(FFT_FORWARD);
  fft.ComplexToMagnitude();
}

void splitToBands() {
  currMaxVal = 0.f;
  int bucket = 1;
  for (int i = 0; i < ROWS; i++) {
    bands[i] = 0;
    float s = band_sizes[i] - bucket;
    for (; bucket < band_sizes[i]; bucket++)
      bands[i] += vReal[bucket];
    // Serial.printf("AAAAAA s: %f\n", s);
    bands[i] /= s;
    // Serial.printf("Bands[%d]: %f\n", i, bands[i]);
    curr[i] = max(bands[i], curr[i]);
    currMaxVal = max(currMaxVal, curr[i]);
  }
}

float hue = 255.0 / ROWS;

void display() {
  // maxVal += ((1.2 * currMaxVal) - maxVal) * (1 - 10 * dT);
  // maxVal = constrain(maxVal, 1.0f, 10.f);
  for (int i = 0; i < ROWS; ++i) {
    curr[i] *= 1 - decay * dT;
    led::fillColumn(i, curr[i] / maxVal, CHSV(i * hue, 255, 255));
  }
  led::show();
}

void tFFT::task(void *p) {
  float start = millis();
  getData(rawSamples);
  calc();
  splitToBands();
  led::clear();
  display();
  dT = millis() - start;
  dT /= 1000;
}

Slider setMaxVal("maxVal");
Slider setDecay("decay");

Task tFFT::createTask() {
  return Task{init, task, onFFT, {&setMaxVal, &setDecay}, FFT};
}

void tFFT::onFFT() {}
