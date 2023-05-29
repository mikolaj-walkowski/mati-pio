#pragma once

#ifndef SERVER_H_
#define SERVER_H_

#include "Task.h"
#include <Arduino.h>
#include <ESPmDNS.h>
#include <WebServer.h>

namespace server {
extern char *ssid;
extern char *password;
static const char *domain = "MatLed";

static WebServer MY_server(80);

void init(void *);
void loop(void *);

void addTasks();

} // namespace server

#endif
