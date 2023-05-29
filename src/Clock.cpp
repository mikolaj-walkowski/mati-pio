#include "Clock.h"
#include "HardwareSerial.h"
#include "ezTime.h"
#include "led.h"

using namespace tClock;

void tClock::init(void *_p) {
  ezt::waitForSync();
  curr.setLocation(pref.tzName);
  curr.setDefault();
}

void tClock::loop(void *_p) {
  led::showTime(ezt::hour(), ezt::minute(), false);
}
void tClock::onInternet() {}
Task tClock::createTask() {
  init(NULL);
  return Task{init, loop, onInternet, path};
}
