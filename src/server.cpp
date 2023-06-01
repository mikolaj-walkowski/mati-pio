#include "server.h"
#include "Server.h"
#include "Settings.h"
#include "Task.h"
#include "WebSocketsClient.h"
#include <stdint.h>
#include <vector>

using namespace server;

const char *home = {
#include "../website/index.html"
};

WebSocketsClient currentClient;

Result Swap::onCommand(char *str) {
  if (str[0] != c.sign)
    return BAD_COMMAND;

  int i = 0;
  for (; i < TASK_SIZE; i++) {
    if (String(&str[1]) == TaskStrings[i]) {
      break;
    }
  }
  if (i == TASK_SIZE) {
    return FAILURE;
  }
  currentTask = (TaskNames)i;
  webSocket.broadcastTXT(String(c.sign) + TaskStrings[currentTask]);
  return SUCCESS;
}

Swap swap;
std::vector<Setting *> commands = {
    &swap,
};

String commandList() {
  String out = "";
  for (auto &&c : commands) {
    out += c->serialize() + ',';
  }
  for (auto &&task : tasks) {
    out += TaskStrings[task.name];
    for (auto &&setting : task.settings) {
      out += setting->serialize() + '.';
    }
    out += ',';
  }
  return out;
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload,
                    size_t length) {
  switch (type) {
  case WStype_ERROR: {
    break;
  }
  case WStype_DISCONNECTED: {
    break;
  }
  case WStype_CONNECTED: {
    IPAddress ip = webSocket.remoteIP(num);
    Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0],
                  ip[1], ip[2], ip[3], payload);
    webSocket.sendTXT(num, commandList().c_str());
    webSocket.sendTXT(num, String(swap.c.sign) + TaskStrings[currentTask]);
    break;
  }
  case WStype_TEXT: {
    bool exit = false;
    for (auto &&command : commands) {
      if (command->onCommand((char *)payload) != BAD_COMMAND) {
        exit = true;
        break;
      }
    }
    if (exit)
      break;
    for (auto &&task : tasks) {
      for (auto &&setting : task.settings) {
        if (setting->onCommand((char *)payload) != BAD_COMMAND) {
          exit = true;
          break;
        }
      }
      if (exit)
        break;
    }
    break;
  }
  default:
    break;
  }
}

void server::init(void *_p) {
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (!MDNS.begin(domain)) {
    Serial.println("Error setting up MDNS responder!");
    while (1) {
      delay(1000);
    }
  }

  Serial.println("mDNS responder started");

  MY_server.on("/", []() { MY_server.send(200, "text/html", home); });

  MY_server.onNotFound([]() {
    Serial.println("notFound\n" + MY_server.uri());
    MY_server.send(404);
  });

  MY_server.begin();
  Serial.println("TCP server started");

  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
  Serial.println("WebSocket server started");

  MDNS.addService("html", "tcp", 80);
  MDNS.addService("ws", "tcp", 81);
}

void server::loop(void *_p) {
  MY_server.handleClient();
  webSocket.loop();
}
