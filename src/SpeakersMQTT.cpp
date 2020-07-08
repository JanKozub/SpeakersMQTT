#include "ESP8266WiFi.h"
#include "PubSubClient.h"

#include "Config/Config.h"
#include "MqttService/MqttService.h"

WiFiClient espClient;
PubSubClient client(espClient);

int lastTime = 0;

void setup() {

  pinMode(relay, OUTPUT);
  digitalWrite(relay, state);

  Serial.begin(115200);
  Serial.println("Starting ESP12-E sketch");
  setup_wifi();

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}
void loop() {
  long now = millis();

  if (!client.connected()) {
    reconnect();
  } else {
    client.loop();

    if (now - lastTime > 5000) {
      lastTime = now;
      publishStatus();
      ESP.wdtFeed();
    }
  }
}
