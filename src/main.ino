/*
Bradyn Braithwaite 2021
*/

#include "credentials.h"
#include "index.hpp"

#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>

ESP8266WebServer *server;

void handleRoot() {}
void handleNotFound() {}

void setup() { server = new ESP8266WebServer(80); }
void loop() { server.handleClient(); }
