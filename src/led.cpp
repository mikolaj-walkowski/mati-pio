#include "led.h"
#include "FastLED.h"
#include "esp32-hal.h"
#include "pixeltypes.h"
#include <stdint.h>

using namespace led;

CRGB leds[NUM_LEDS];

void led::write(const int &x, const int &y, const CRGB &c) {
  if (x >= ROWS || y >= COLS)
    return;
  leds[y * ROWS + (1 - y % 2) * x + (y % 2) * (ROWS - 1 - x)] = c;
}

void led::write(const Point &p, const CRGB &color) { write(p.x, p.y, color); }

CRGB *led::read(const int &x, const int &y) {
  return &leds[y * ROWS + (1 - y % 2) * x + (y % 2) * (ROWS - 1 - x)];
}

void led::clear(const CRGB &clear) {
  for (int i = 0; i < NUM_LEDS; ++i) {
    leds[i] = clear;
  }
}

void led::fillColumn(const int &column, const float &percent,
                     const CRGB &color) {
  int fill = percent * COLS;
  int i = 0;
  for (; i < fill; ++i) {
    write(column, i, color);
  }
  write(column, i++, prefs.fillCrown);
  for (; i < COLS; ++i) {
    write(column, i, prefs.blank);
  }
}

void led::show() { FastLED.show(); }

void led::init() {
  // TODO delete and swap for loading form memory
  prefs.fillCrown = CRGB::White;
  prefs.brightness = 70;
  prefs.blank = CRGB::Black;
  FastLED.addLeds<NEOPIXEL, LED_DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(prefs.brightness);

  createNumbers();
}

void led::showTime(uint8_t hour, uint8_t minute, bool h12) {
  clear();
  displayNumber(numbers[hour / 10], 0);
  displayNumber(numbers[hour % 10], 1);
  displayNumber(numbers[minute / 10], 2);
  displayNumber(numbers[minute % 10], 3);
  if (h12) {
    // TODO semi
  }

  show();
}

void led::displayNumber(const Number &num, const uint8_t &pos) {
  for (uint8_t i = 0; i < num.size; ++i) {
    write(NumPos[pos] + num.pixels[i], CRGB::White);
  }
}

Point led::operator+(const Point &lhs, const Point &rhs) {
  Point out;
  out.x = lhs.x + rhs.x;
  out.y = lhs.y + rhs.y;
  return out;
}

void led::test() {
  static int i = 0;
  int d = 500;
  leds[i] = CRGB::Blue;
  show();
  delay(d);
  leds[i] = CRGB::Black;
  ++i;
}
