#pragma once
#ifndef TASK_HEADER
#define TASK_HEADER
#include "Settings.h"
#include <Arduino.h>
#include <vector>

typedef void (*Function)(void *);
typedef void (*WebHandler)();

enum TaskNames { FFT, CLOCK, REMOTE, TASK_SIZE };

struct Task {
  Function init;
  Function loop;
  WebHandler on;
  std::vector<Setting *> settings;
  TaskNames name;
};

extern String TaskStrings[TASK_SIZE];

extern Task tasks[TASK_SIZE];

extern TaskNames currentTask;
#endif
