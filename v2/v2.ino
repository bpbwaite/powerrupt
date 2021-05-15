// same time every day (for ATTiny85, etc)

#include "Arduino.h"

#define GPIO        0x0 // pin no 5
#define PRESSMS     500UL
#define DAYINMILLIS 86400000UL

unsigned long previousEvent = 0;

void setup() {
    digitalWrite(GPIO, LOW);
    pinMode(GPIO, OUTPUT);
}

void loop() {

    unsigned long currentMillis = millis();
    if ((unsigned long) (currentMillis - previousEvent) > DAYINMILLIS) {

        digitalWrite(GPIO, HIGH);
        delay(PRESSMS);
        digitalWrite(GPIO, LOW);

        previousEvent = currentMillis;
    }
}
