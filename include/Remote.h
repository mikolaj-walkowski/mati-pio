#pragma once

#include "Task.h"
#ifndef REMOTE_H_
#define REMOTE_H_

namespace tRemote {
void init(void *);
void loop(void *);
void onRemote();
static const char *path = "remote";
Task createTask();
} // namespace tRemote
#endif
