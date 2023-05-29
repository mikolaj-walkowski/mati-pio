#pragma once
#include "Task.h"
#ifndef FFT_HEADER
#define FFT_HEADER

#include "led.h"
#include <arduinoFFT.h>
#include <stdint.h>
#define SAMPLE_BUFFER_SIZE 1024
#define SAMPLE_RATE 44100

namespace tFFT {

static double vImg[SAMPLE_BUFFER_SIZE], vReal[SAMPLE_BUFFER_SIZE];
static int32_t rawSamples[SAMPLE_BUFFER_SIZE];

static arduinoFFT fft(vReal, vImg, SAMPLE_BUFFER_SIZE, SAMPLE_RATE);

const float band_sizes[ROWS] = {
    2,  3,  5,  7,  9,   13,  18,  25,
    36, 50, 69, 97, 135, 189, 264, SAMPLE_BUFFER_SIZE / 2};

static float maximums[ROWS], curr[ROWS], bands[ROWS], maxVal = 1.f;

static const char *path = "FFT";

void task(void *);

void init(void *);

void onFFT();

Task createTask();
} // namespace tFFT
#endif
