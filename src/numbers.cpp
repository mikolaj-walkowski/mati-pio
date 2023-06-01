#include "led.h"
#include "pzim3x5_font.h"
#include <stdint.h>

using namespace led;

Number led::numbers_h[10], led::numbers_v[10], *led::numbers;
Point led::h_NumPos[8], led::v_NumPos[8], *led::NumPos;

#define UP (p = &numbers_h[num].pixels[(++numbers_h[num].size)])

#define SET(A)                                                                 \
  num = (A);                                                                   \
  numbers_h[num].size = 0;                                                     \
  p = &numbers_h[num].pixels[numbers_h[num].size];

#define P(X, Y)                                                                \
  p->x = (X);                                                                  \
  p->y = (Y);                                                                  \
  UP

#define V(A)                                                                   \
  p = &numbers_h[num].pixels[numbers_h[num].size];                             \
  A = 0;                                                                       \
  for (; A < h; A++)

#define H(A)                                                                   \
  p = &numbers_h[num].pixels[numbers_h[num].size];                             \
  A = 0;                                                                       \
  for (; A < w; A++)

void led::createNumbers() {
  uint8_t start_x = 0;
  uint8_t offset_x = (CHAR_WIDTH + 1);
  uint8_t start_y = 12;
  uint8_t offset_y = -(CHAR_HEIGHT + 1);
  uint8_t i = 0;
  for (uint8_t y = 0; y < 2; y++) {
    for (uint8_t x = 0; x < 4; x++) {
      h_NumPos[i++] = {static_cast<uint8_t>(start_x + (x * offset_x)),
                       static_cast<uint8_t>(start_y + (y * offset_y))};
    }
  }
  /*
    int w = 3;
    int h = 7;
    Point *p;
    int i;
    int num;

    SET(0)
    V(i) {
      P(0, i);
      P(2, i);
    }
    P(1, 0);
    P(1, h - 1);

    SET(1)
    V(i) { P(2, i); }
    P(1, 1);
    P(0, 2);

    SET(2)
    V(i) {
      if (i < 4) {
        P(2, i);
      }
    }
    H(i) { P(i, h - 1); }
    P(1, h - 3);
    P(0, h - 2);
    P(0, 0);
    P(1, 0);

    SET(3)
    V(i) { P(2, i); }
    P(0, 0);
    P(1, 0);
    P(0, 3);
    P(1, 3);
    P(0, h - 1);
    P(1, h - 1);

    SET(4)
    V(i) {
      P(2, i);
      if (i < 3) {
        P(0, i);
      }
    }
    P(1, 3);

    SET(5)
    V(i) {
      if (i < 4) {
        P(0, i);
      }
      if (i >= 3) {
        P(2, i);
      }
    }
    P(1, 0);
    P(2, 0);
    P(0, h - 1);
    P(1, h - 1);
    P(1, 3);

    SET(6)
    V(i) {
      P(0, i);
      if (i >= 3)
        P(2, i);
    }
    P(1, 0);
    P(2, 0);
    P(1, 3);
    P(1, h - 1);

    SET(7)
    V(i) { P(2, i); }
    P(0, 0);
    P(1, 0);

    SET(8);
    V(i) {
      if (i != 3) {
        P(0, i);
        P(2, i);
      }
    }
    P(1, 0);
    P(1, 3);
    P(1, h - 1);

    SET(9);
    V(i) {
      P(2, i);
      if (i < 3) {
        P(0, i);
      }
    }
    P(1, 0);
    P(1, 3);
    P(0, h - 1);
    P(1, h - 1);

    for (int a = 0; a < 10; a++) {
      for (int b = 0; b < numbers_h[a].size; b++) {
        numbers_h[a].pixels[b].y = h - numbers_h[a].pixels[b].y;
      }
    }
    */
  numbers = numbers_h;
  NumPos = h_NumPos;
}
