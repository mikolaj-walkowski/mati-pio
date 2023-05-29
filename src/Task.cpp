#include "Task.h"

Task tasks[TASK_SIZE];

String TaskStrings[TASK_SIZE] = {"FFT", "CLOCK", "REMOTE"};

TaskNames currentTask = CLOCK;
