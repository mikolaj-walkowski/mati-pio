#pragma once

#ifndef SERVER_H_
#define SERVER_H_

#include "Task.h"
#include <Arduino.h>
#include <ESPmDNS.h>
#include <WebServer.h>
#include <WebSocketsServer.h>

namespace server {
extern char *ssid;
extern char *password;
static const char *domain = "matled";

static WebServer MY_server(80);
static WebSocketsServer webSocket(81);

void init(void *);
void loop(void *);

class Swap : public Setting {
public:
  Swap() : Setting("swap", no_flags, ACTION) {}
  Result onCommand(char *str) override;
};

} // namespace server

#endif
