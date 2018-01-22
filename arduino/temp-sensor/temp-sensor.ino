//temperature DS18B20
//ESP8266 ESP12-E (nodeMCU v1.0)

#include <ESP8266WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2  // D4 on Node
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);

void setup() {
  Serial.begin(115200);
}

void loop() {
  float temp;
  DS18B20.requestTemperatures(); 
  temp = DS18B20.getTempCByIndex(0);
  Serial.print("Temp: ");
  Serial.println(temp);
  delay(1000);
}

