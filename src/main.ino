/*
Bradyn Braithwaite 2021
*/

#include "credentials.h" // contains ssid and pwsd
#include "index.hpp"     // contains ndx

#include <ESP8266HTTPClient.h> // only used for http definitions
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>

#define nodegpio_d2 4
#define longpressms 470

ESP8266WebServer *server;
static unsigned long toflastclickr = 0;

void handleRoot() {
    server->send(HTTP_CODE_OK, "text/html", String(ndx));
}
void handleNotFound() {
    server->send(HTTP_CODE_NOT_FOUND);
}

void handleS1() {
    if (toflastclickr + 5000L < millis()) {
        toflastclickr = millis();

        server->send(HTTP_CODE_OK);

        digitalWrite(nodegpio_d2, HIGH);
        delay(longpressms);
        digitalWrite(nodegpio_d2, LOW);
    }
    else {
        server->send(HTTP_CODE_FORBIDDEN, "text/html", String("denied"));
    }
}

void setup() {

    server = new ESP8266WebServer(80);

    digitalWrite(nodegpio_d2, LOW);
    pinMode(nodegpio_d2, OUTPUT);

    WiFi.begin(ssid, pswd);
    while (WiFi.status() != WL_CONNECTED) {
        delay(250);
    }

    server->onNotFound(handleNotFound);
    server->on("/", handleRoot);
    server->on("/rclick", handleS1);
    server->begin();
}
void loop() {
    server->handleClient();
}
