#include <SoftwareSerial.h>
#include <ArduinoJson.h>

SoftwareSerial arduinoUno(6,5);

void setup() {
  arduinoUno.begin(115200);
}

void loop() {
  StaticJsonDocument<1000> jsonDocument;
  jsonDocument["name"] = "deffe";

  serializeJson(jsonDocument, arduinoUno);

  delay(5000);
}
