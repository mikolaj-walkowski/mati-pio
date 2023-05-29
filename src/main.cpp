#include "Clock.h"
#include "FastLED.h"
#include "Remote.h"
#include "server.h"
#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif

#include "FFT.h"
#include "HardwareSerial.h"
#include "Task.h"
#include "esp32-hal.h"
#include "led.h"
#include <Arduino.h>

// TCP server at port 80 will respond to HTTP requests

void TaskMaster(void *pvParams) {

  for (;;) {
    tasks[currentTask].loop(NULL);
  }
}

void TaskSlave(void *pvParams) {
  for (;;) {
    server::loop(NULL);
  }
}

void setup() {

  Serial.begin(115200);
  led::init();
  server::init(NULL);
  tasks[FFT] = tFFT::createTask();
  tasks[CLOCK] = tClock::createTask();
  tasks[REMOTE] = tRemote::createTask();
  currentTask = CLOCK;

  xTaskCreatePinnedToCore(TaskMaster, "TaskMaster" // A name just for humans
                          ,
                          3072 // This stack size can be checked & adjusted by
                               // reading the Stack Highwater
                          ,
                          NULL, 2 // Priority, with 3 (configMAX_PRIORITIES - 1)
                                  // being the highest, and 0 being the lowest.
                          ,
                          NULL, ARDUINO_RUNNING_CORE);

  xTaskCreatePinnedToCore(TaskSlave, "TaskSlave", 3072 // Stack size
                          ,
                          NULL, 1 // Priority
                          ,
                          NULL, ARDUINO_RUNNING_CORE);
}

void loop() {}
