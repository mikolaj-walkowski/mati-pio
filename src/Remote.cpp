#include "Remote.h"
#include "Arduino.h"
#include "led.h"

using namespace tRemote;

void tRemote::init(void *_p) {}

void tRemote::loop(void *_p) { led::test(); }

void tRemote::onRemote() {}

Task tRemote::createTask() {
  init(NULL);
  return Task{init, loop, onRemote, path};
}
