#include "Arduino.h"
#include "ESP8266WiFi.h"
#include "PubSubClient.h"

#include "MqttService/MqttService.h"
#include "Config/Config.h"

int lastTime2 = 0;

void setup_wifi() {

  delay(10);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("WiFi connected");
}

void reconnect() {
  while (!client.connected()) {
    long now = millis();
    ESP.wdtFeed();
    if (now - lastTime2 > 10000) {
      lastTime2 = now;
      Serial.print("Attempting MQTT connection...");
      String clientId = deviceName;

      clientId += String(random(0xffff), HEX);
      if (client.connect(clientId.c_str())) {
        Serial.println("connected");

        String msg = String(deviceName) + ",1";
        client.publish(deviceName, msg.c_str());

        client.subscribe((String(deviceName) + "Sub").c_str());
      } else {
        Serial.print("failed, rc=");
        Serial.print(client.state());
        Serial.println(" try again in 10 seconds");
      }
    }
  }
}

void callback(char* topic, byte* payload, int length) {
  String output = "";
  for (int i = 0; i < length; i++) {
    output = output + (char)payload[i];
  }
  if (output.equals("TOGGLE")) {
    state = !state;
    publishStatus();
    digitalWrite(relay, state);
    Serial.println("------------------");
    Serial.println("Toggled via app");
    Serial.print("State= ");
    Serial.println(state);
    Serial.println("------------------");
  }
}

void publishStatus() {
  String msg = String(deviceName) + "," + String(state);
  Serial.print("Publish message: ");
  Serial.println(msg);
  client.publish(deviceName, msg.c_str());
}

void changeState() {
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();

  if (interrupt_time - last_interrupt_time > 200)
  {
    state = !state;
    digitalWrite(relay, state);
    publishStatus();
    ESP.wdtFeed();
    Serial.println("------------------");
    Serial.println("Toggled via switch");
    Serial.print("State= ");
    Serial.println(state);
    Serial.println("------------------");
  }
  last_interrupt_time = interrupt_time;
}
