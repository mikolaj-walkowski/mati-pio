#include "led.h"
#include "FastLED.h"
#include "HardwareSerial.h"
#include "esp32-hal.h"
#include "pixeltypes.h"
#include "pzim3x5_font.h"
#include <stdint.h>

using namespace led;

CRGB leds[NUM_LEDS];

void led::write(const int &x, const int &y, const CRGB &c) {
  if (x >= ROWS || x < 0 || y >= COLS || y < 0)
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
  int p = 0;
  if (h12) {
    p = 4;
  }
  auto pos = h_NumPos;
  displayChar('0' + (hour / 10), pos[p + 0]);
  displayChar('0' + (hour % 10), pos[p + 1]);
  displayChar('0' + (minute / 10), pos[p + 2]);
  displayChar('0' + (minute % 10), pos[p + 3]);
  if (!h12) {
    write(7, 9, CRGB::Aqua);
    write(7, 7, CRGB::Aqua);
  } else {
    led::write(7, 0, CRGB::Maroon);
  }
}

void led::displayChar(char c, Point pos) {
  uint8_t i, j;
  c = c & 0x7F;
  if (c < ' ') {
    c = 0;
  } else {
    c -= ' ';
  }
  const uint8_t *chr = &font[c][0];
  for (j = 0; j < CHAR_WIDTH; j++) {
    for (i = 0; i < CHAR_HEIGHT; i++) {

      if (chr[j] & (1 << i)) {
        write(pos.x + j, pos.y - i, CRGB::White);
      }
    }
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
  i = (i + 1) % NUM_LEDS;
}
