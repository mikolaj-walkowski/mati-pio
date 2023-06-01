#include "Remote.h"
#include "Arduino.h"
#include "Task.h"
#include "led.h"

using namespace tRemote;

void tRemote::init(void *_p) {}

void tRemote::loop(void *_p) { led::test(); }

void tRemote::onRemote() {}

Task tRemote::createTask() { return Task{init, loop, onRemote, {}, REMOTE}; }
