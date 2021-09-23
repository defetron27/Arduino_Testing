#include <SoftwareSerial.h>
#include <ArduinoJson.h>

SoftwareSerial mySerial(5, 6); // RX, TX

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
}

void loop() {
  StaticJsonDocument<1000> jsonDocument;
  jsonDocument["name"] = "deffe";

  Serial.println("Json has sent.");
  serializeJson(jsonDocument, mySerial);
}
