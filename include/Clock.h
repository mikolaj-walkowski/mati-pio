#pragma once
#include "Task.h"
#include <stdint.h>
#ifndef CLOCK_H_
#define CLOCK_H_

#define EZTIME_WIFIESP
#define EZTIME_EZT_NAMESPACE
#include <Arduino.h>
#include <ezTime.h>

namespace tClock {
static Timezone curr;
static const char *path = "Clock";
static struct {
  char *tzName = "Europe/Warsaw";
  uint8_t size;
} pref;

void init(void *);
void loop(void *);
void onInternet();

Task createTask();
} // namespace tClock
#endif
