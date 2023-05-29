#include "FFT.h"
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
  int bucket = 1;
  // BUG mayby i should take avg instead of sum
  for (int i = 0; i < ROWS; i++) {
    bands[i] = 0;
    for (; bucket <= band_sizes[i]; bucket++)
      bands[i] += vReal[bucket];
    curr[i] = max(bands[i], curr[i]);
    maxVal = max(maxVal, curr[i]);
  }
}

float hue = 255.0 / ROWS;

void display() {
  maxVal *= 0.9;
  for (int i = 0; i < ROWS; ++i) {
    curr[i] *= 0.9;
    led::fillColumn(i, curr[i] / maxVal, CHSV(i * hue, 255, 255));
  }
  led::show();
}

void tFFT::task(void *p) {
  getData(rawSamples);
  calc();
  splitToBands();
  display();
}

Task tFFT::createTask() {
  init(NULL);
  return Task{init, task, onFFT, path};
}

void tFFT::onFFT() {}
