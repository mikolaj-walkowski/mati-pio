#include "led.h"

using namespace led;

Number led::numbers_h[10], led::numbers_v[10], *led::numbers;
Point led::h_NumPos[4], led::v_NumPos[4], *led::NumPos;

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
  h_NumPos[0] = {1, 2};
  h_NumPos[1] = {5, 2};
  h_NumPos[2] = {9, 2};
  h_NumPos[3] = {13, 2};

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
  numbers = numbers_h;
  NumPos = h_NumPos;
}
