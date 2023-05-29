#include "server.h"
#include "Server.h"
#include "Task.h"
#include <stdint.h>

using namespace server;

const char *home = {
#include "../website/index.html"
};

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

  // Set up mDNS responder:
  // - first argument is the domain name, in this example
  //   the fully-qualified domain name is "esp32.local"
  // - second argument is the IP address to advertise
  //   we send our IP address on the WiFi network
  if (!MDNS.begin(domain)) {
    Serial.println("Error setting up MDNS responder!");
    while (1) {
      delay(1000);
    }
  }
  Serial.println("mDNS responder started");

  MY_server.on("/", []() {
    Serial.println("/\n" + MY_server.uri());
    MY_server.send(200, "text/html", home);
  });
  MY_server.on("/comm", []() {
    Serial.println("/comm\n" + MY_server.arg("title"));
    MY_server.send(200, "text/plain", MY_server.arg("title"));
  });
  MY_server.onNotFound([]() {
    Serial.println("notFound\n" + MY_server.uri());
    MY_server.send(404);
  });
  MY_server.on("/favicon.ico",
               []() { MY_server.send(200, "image/x-icon", ""); });

  MY_server.on("/swap", []() {
    String mode = MY_server.arg("mode");
    int i = 0;
    Serial.print("Argument val: ");
    Serial.println(mode);
    for (; i < TASK_SIZE; i++) {
      if (mode == TaskStrings[i]) {
        break;
      }
    }
    Serial.print("Switching to: ");
    Serial.println(i);
    currentTask = (TaskNames)i;
  });

  MY_server.begin();
  Serial.println("TCP server started");
}

void server::addTasks() {
  for (int i = 0; i < TASK_SIZE; i++) {
    MY_server.on(tasks[i].path, tasks[i].on);
  }
}

void server::loop(void *_p) { MY_server.handleClient(); }
