#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Servo.h>

#ifndef STASSID
#define STASSID "Fast"
#define STAPSK  "demopwd123"
#endif

Servo myservoV;
Servo myservoO;

const char* ssid = STASSID;
const char* password = STAPSK;

ESP8266WebServer server(80);

const int led = 13;

void handleRoot() {
  
  if (server.arg("toiminto")== "eteen"){
    eteen();
  }
  else if (server.arg("toiminto")== "taakse"){
    taakse();
  }
  else if (server.arg("toiminto")== "vasen"){
    vasen();
  }
  else if (server.arg("toiminto")== "oikea"){
    oikea();
  }
  
  digitalWrite(led, 1);
  char html[] = "<form action='' method='get'><input id='eteen' name='toiminto' value='eteen' type='submit'><input id='taakse' name='toiminto' value='taakse' type='submit'><input id='vasen' name='toiminto' value='vasen' type='submit'><input id='oikea' name='toiminto' value='oikea' type='submit'></form>";
  server.send(200, "text/html", html);
  digitalWrite(led, 0);
}

void eteen() {
  Serial.print("eteen");
  int myservoVspeed = myservoV.read() + 10;
  myservoV.write(myservoVspeed);

  int myservoOspeed = myservoO.read() - 3 ;
  myservoO.write(myservoOspeed);

  delay(3000);
  zeroPoint();
}

void taakse() {
  Serial.print("taakse");
  int myservoVspeed = myservoV.read() - 10;
  myservoV.write(myservoVspeed);

  int myservoOspeed = myservoO.read() + 10;
  myservoO.write(myservoOspeed);

  delay(1000);
  zeroPoint();
}

void vasen() {
  Serial.print("vasen: ");
  int myservoVspeed = myservoV.read() - 10;
  Serial.print(myservoVspeed);
  myservoV.write(myservoVspeed);
  delay(1000);
  zeroPoint();
}

void oikea() {
  Serial.print("oikea: ");
  int myservoOspeed = myservoO.read() + 10;
  Serial.print(myservoOspeed);
  myservoO.write(myservoOspeed);
  delay(1000);
  zeroPoint();
}

void zeroPoint() {
  Serial.print("|");
  myservoV.write(92);
  myservoO.write(102);
  delay(1000);
}

void handleNotFound() {
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}

void setup(void) {
  myservoV.attach(0);  // attaches the servo on GIO0 to the servo object // 92 center
  myservoO.attach(2);  // attaches the servo on GIO2 to the servo object // 102 center
  zeroPoint();
  
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });

  server.on("/gif", []() {
    static const uint8_t gif[] PROGMEM = {
      0x47, 0x49, 0x46, 0x38, 0x37, 0x61, 0x10, 0x00, 0x10, 0x00, 0x80, 0x01,
      0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x2c, 0x00, 0x00, 0x00, 0x00,
      0x10, 0x00, 0x10, 0x00, 0x00, 0x02, 0x19, 0x8c, 0x8f, 0xa9, 0xcb, 0x9d,
      0x00, 0x5f, 0x74, 0xb4, 0x56, 0xb0, 0xb0, 0xd2, 0xf2, 0x35, 0x1e, 0x4c,
      0x0c, 0x24, 0x5a, 0xe6, 0x89, 0xa6, 0x4d, 0x01, 0x00, 0x3b
    };
    char gif_colored[sizeof(gif)];
    memcpy_P(gif_colored, gif, sizeof(gif));
    // Set the background to a random set of colors
    gif_colored[16] = millis() % 256;
    gif_colored[17] = millis() % 256;
    gif_colored[18] = millis() % 256;
    server.send(200, "image/gif", gif_colored, sizeof(gif_colored));
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
  MDNS.update();
}
