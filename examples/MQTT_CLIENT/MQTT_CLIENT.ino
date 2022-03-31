/*
    Description:
    Use UNIT PoESP32 to connect to the MQTT server, and implement subscription
    and publishing messages. Check the status through Serial. 
*/

#include "UNIT_PoESP32.h"

UNIT_PoESP32 eth;

void setup() {
    Serial.begin(115200);
    eth.Init(&Serial2, 9600, 32, 26);

    delay(10);

    Serial.println("wait device connect");
    while (!eth.checkDeviceConnect()) {
        delay(10);
    }

    Serial.println("device connected");

    Serial.println("wait ethernet connect");
    while (!eth.checkETHConnect()) {
        delay(10);
    }
    Serial.println("ethernet connected");

    Serial.println("wait mqtt connect");
    while (!eth.createMQTTClient("120.77.157.90", "1883", "client_id",
                                 "user_name", "password")) {
        delay(10);
    }
    Serial.println("mqtt connected");

    while (!eth.subscribeMQTTMsg("PoESP32_MQTT_D", "2")) {
        delay(10);
    }
}

void loop() {
    if (Serial.available()) {
        char ch = Serial.read();
        Serial2.write(ch);
    }
    if (Serial2.available()) {
        char ch = Serial2.read();
        Serial.write(ch);
    }
    eth.publicMQTTMsg("PoESP32_MQTT_U", "Hello From PoESP32", "2");
    delay(1000);
}
