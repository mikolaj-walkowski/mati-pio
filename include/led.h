#pragma once
#ifndef LED_HEADER
#define LED_HEADER

#include <stdint.h>
#define LED_DATA_PIN 12
#define COLS 12
#define ROWS 16
#define NUM_LEDS (COLS * ROWS)
#define FASTLED_INTERNAL
#include <FastLED.h>

namespace led {

struct Point {
  uint8_t x;
  uint8_t y;
};

void createNumbers();

Point operator+(const Point &lhs, const Point &rhs);

struct Number {
  Point pixels[7 * 3];
  uint8_t size;
};

extern Number numbers_h[], numbers_v[], *numbers;

extern Point h_NumPos[], v_NumPos[], *NumPos;

struct {
  uint8_t brightness;
  CRGB fillCrown;
  CRGB blank;
} prefs;

void write(const Point &p, const CRGB &color);
void write(const int &x, const int &y, const CRGB &c);

CRGB *read(const int &x, const int &y);

void clear(const CRGB &clear = CRGB::Black);

// TODO swap to using color array
void fillColumn(const int &column, const float &percent, const CRGB &color);

void show();

void init();

void showTime(uint8_t hour, uint8_t minute, bool h12);

void displayNumber(const Number &num, const uint8_t &pos);

void test();

} // namespace led
#endif
