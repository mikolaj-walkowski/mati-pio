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
  led::clear();
  led::showTime(ezt::hour(), ezt::minute(), false);
  led::showTime(ezt::day(), ezt::month(), true);
  led::show();
}
void tClock::onInternet() {}
Task tClock::createTask() { return Task{init, loop, onInternet, {}, CLOCK}; }
