#include "Arduino.h"
#include "PubSubClient.h"
#include "PrivData.h"

#ifndef CONFIG_H
#define CONFIG_H

#define relay D1
#define deviceName "speakers"
#define mqtt_server "10.0.98.125"

extern PubSubClient client;
extern boolean state;

void setup_config(PubSubClient newClient);

#endif