#include "Config.h"
#include "PubSubClient.h"

boolean state = false;

void setup_config(PubSubClient newClient) {
    client = newClient;
}