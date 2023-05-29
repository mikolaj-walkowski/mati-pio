#pragma once
#ifndef TASK_HEADER
#define TASK_HEADER
#include <Arduino.h>
typedef void (*Function)(void *);
typedef void (*WebHandler)();

struct Task {
  Function init;
  Function loop;
  WebHandler on;
  const char *path;
};

enum TaskNames { FFT, CLOCK, REMOTE, TASK_SIZE };

extern String TaskStrings[TASK_SIZE];

extern Task tasks[TASK_SIZE];

extern TaskNames currentTask;
#endif
