#include "Arduino.h"
#include "Config/Config.h"

#ifndef MQTTSERVICE_H
#define MQTTSERVICE_H

void setup_wifi();

void reconnect();

void callback(char* topic, byte* payload, int length);

void publishStatus();

void changeState();

#endif