#include <SoftwareSerial.h>
#include <ArduinoJson.h>

SoftwareSerial arduinoUno(5,6);

void setup() {
  Serial.begin(9600);
  arduinoUno.begin(9600);
}

void loop() {
//  StaticJsonDocument<1000> jsonDocument;
//  jsonDocument["data1"] = 100;
//  jsonDocument["data2"] = 200;
//
//  if(s.available()>0) {
//    serializeJson(jsonDocument, s);
//  }

  int data = 50;

  if(arduinoUno.available()>0) {
    arduinoUno.write(data);
  }

//  while(arduinoUno.available() > 0) {
//    float val = arduinoUno.parseFloat();
//
//    if(arduinoUno.read() == '\n') {
//      Serial.println(val);
//    }
//  }
//
//  delay(30);
}
