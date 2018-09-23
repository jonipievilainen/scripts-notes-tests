/*
  D0 D1 D2 D7 leds 16 5 4 13
  D5 temp 14 -> D6 12
  D6 relay 12 -> D5 14

  192.168.0.124/setLeds
*/

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <OneWire.h>
#include <DallasTemperature.h>

const int led1 = 16;
const int led2 = 5;
const int led3 = 4;
const int led4 = 13;
const int temp = 12;
const int relay = 14;

int ls = 50;
int steps = 5;

int led1Status = 0;
int led2Status = 0;
int led3Status = 0;
int led4Status = 0;

ESP8266WebServer server(80);

OneWire oneWire(temp);
DallasTemperature DS18B20(&oneWire);

void setLeds() {
  String message = "";
  int r = 0;
  int g = 0;
  int b = 0;
  int w = 0;

  if (server.arg("b") != "") {
    b = server.arg("b").toInt();
    message += "b = ";
    message += server.arg("b");     //Gets the value of the query parameter
  }

  if (server.arg("r") != "") {
    r = server.arg("r").toInt();
    message += " r = ";
    message += server.arg("r");     //Gets the value of the query parameter
  }

  if (server.arg("g") != "") {
    g = server.arg("g").toInt();
    message += " g = ";
    message += server.arg("g");     //Gets the value of the query parameter
  }

  if (server.arg("w") != "") {
    w = server.arg("w").toInt();
    message += " w = ";
    message += server.arg("w");     //Gets the value of the query parameter
  }

  changeColor(led1, led1Status, w);
  changeColor(led2, led2Status, b);
  changeColor(led3, led3Status, g);
  changeColor(led4, led4Status, r);

  led1Status = w;
  led2Status = b;
  led3Status = g;
  led4Status = r;

  server.send(200, "text/plain", message);          //Returns the HTTP response
}

void getTemp() {
  String temp;
  DS18B20.requestTemperatures();
  temp = DS18B20.getTempCByIndex(0);
  server.send(200, "text/plain", temp);
}

void setRelay() {
  String message = "";
  int ms = 1000;

  if (server.arg("ms") != "") {
    ms = server.arg("ms").toInt();
    message += " ms = ";
    message += server.arg("ms");     //Gets the value of the query parameter

    digitalWrite(relay, HIGH);
    delay(ms);
    digitalWrite(relay, LOW);
  }

  server.send(200, "text/plain", message);
}

bool changeColor(int led, int x, int xNext) {
  if (led == xNext) {
    return false;
  } else if (x < xNext) {
    while (x <= xNext) {
      analogWrite(led, x);
      x = x + steps;
      delay(ls);
    }
    if (x != xNext) {
      analogWrite(led, xNext);
    }
  } else {
    while (x >= xNext) {
      analogWrite(led, x);
      x = x - steps;
      delay(ls);
    }
    if (x != xNext) {
      analogWrite(led, xNext);
    }
  }
  return true;
}

void setup() {
  Serial.begin(115200);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(relay, OUTPUT);

  analogWrite(led1, led1Status);
  analogWrite(led2, led2Status);
  analogWrite(led3, led3Status);
  analogWrite(led4, led4Status);

  WiFi.begin("Fast", "demopwd123");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Waiting to connect…");
  }

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  server.on("/setLeds", setLeds);
  server.on("/getTemp", getTemp);
  server.on("/setRelay", setRelay);

  server.begin();
  Serial.println("Server listening");
}

void loop() {
  server.handleClient();
}
