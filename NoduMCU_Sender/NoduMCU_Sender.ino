#include <SoftwareSerial.h>
#include <ArduinoJson.h>

SoftwareSerial nodeMCU(D6, D5);

void setup() {
  Serial.begin(9600);
  nodeMCU.begin(9600);
}

void loop() {
//  int i = 10;
//  nodeMCU.print(i);
//  nodeMCU.println("\n");
//  delay(30);

  nodeMCU.write("s");

  if (nodeMCU.available() > 0) {
    int data = nodeMCU.read();
    Serial.println("hello");
  }
  
//  StaticJsonDocument<1000> jsonDocument;
//
//  DeserializationError error = deserializeJson(jsonDocument, s);
//
//  if (error) {
//    Serial.print("Error founded -> ");
//    Serial.println(error.c_str());
//    return;
//  }
//
//  Serial.println("Json received and parsed");
//  serializeJsonPretty(jsonDocument, s);
//  
//  Serial.print("Data 1 -> ");
//  Serial.println("");
//
//  int data1 = jsonDocument["data1"];
//  Serial.println(data1);
//
//  Serial.print("Data 2 -> ");
//  Serial.println("");
//
//  int data2 = jsonDocument["data2"];
//  Serial.println(data2);
//
//  Serial.println("<------------------Finished--------------------->");
}
