#include <arduino.h>
#include "xbee_programmer.h"
#include <cstring>

//Return 0 for success and 1 for failure.
uint8_t init() {
    Serial.begin(9600);
    Serial5.begin(115200);
    while(!Serial);
    while(!Serial5);
    Serial.println("Initializing programmer");

    delay(1500);
    Serial.println("+++");
    Serial5.print("+++");

    if (ok()) {
        delay(1000);
        return 0;
    } 

    Serial.println("Failed to connect");
    return 1;
}

uint8_t ok() {
    unsigned long timer = millis();
    char data[4] = {};
    while (Serial5.available() < 3) {
        if (millis()-timer > 1200) {
                Serial.println("timer");
                return 0;
            } 
        }
        Serial5.readBytes(data, 3);
        Serial.println(data);
        if(check_response(data, "OK\r")) {
            Serial.println("check");
            return 0;
        }
        return 1;
}

uint8_t check_response(const char c1[], const char c2[]) {
    if (strcmp(c1, c2)) {
        return 1;
    }
    return 0;
}

uint8_t send_command(const char command[]) {
    Serial.print("AT ");
    Serial.println(command);
    Serial5.print("AT ");
    Serial5.print(command);
    Serial5.print('\r');
}

