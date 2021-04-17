/*
Bradyn Braithwaite 2021
*/

#include "credentials.h" // contains ssid and pwsd
#include "index.hpp"     // contains ndx

#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>

#define nodegpio_d2 4

ESP8266WebServer *server;
static uint8_t relayState = 0;

void handleRoot() { server->send(200, "text/html", String(ndx)); }
void handleNotFound() { server->send(404); }
void handleS0() {}
void handleS1() {}
void handleGETS() {

  relayState = digitalRead(nodegpio_d2);
  server->send(200, "text/plain", String(relayState));
}

void setup() {

  server = new ESP8266WebServer(80);

  pinMode(nodegpio_d2, OUTPUT);

  delay(100);
  WiFi.begin(ssid, pswd);
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
  }

  server->onNotFound(handleNotFound);
  server->on("/", handleRoot);
  server->on("/off", handleS0);
  server->on("/on", handleS1);
  server->begin();
}
void loop() {
  server->handleClient();
  yield();
}
