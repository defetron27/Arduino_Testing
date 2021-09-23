#include <SoftwareSerial.h>

#include <ArduinoJson.h>

SoftwareSerial s(5,6);

void setup() {
  Serial.begin(115200);
  s.begin(9600);
}

void loop() {
//  String data = s.readStringUntil('\r');
//  Serial.println(s.read());
//  delay(1000);

  StaticJsonDocument<1000> jsonDocument;

  DeserializationError error = deserializeJson(jsonDocument, s);

  if (error) {
    Serial.print("Error Occurred -> ");
    Serial.println(error.c_str());
    return;
  }

  Serial.println("Json received and parsed successfully.");

  String name = jsonDocument["name"];

  Serial.print("name -> ");
  Serial.println(name);

  delay(2000);
}
