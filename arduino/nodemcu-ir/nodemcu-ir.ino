#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>

const uint16_t kIrLed = 4;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).
IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.
ESP8266WebServer server(80);

// Samsung on/off data
uint16_t rawData[] = {4550,4400,600,1650,550,1650,600,1650,
550,550,600,500,600,550,550,550,600,500,600,1650,600,1600,600,
1650,550,550,600,500,600,550,600,500,600,500,650,450,650,1600,
600,500,650,450,650,500,600,500,600,500,600,550,600,1600,600,
500,650,1600,650,1550,650,1600,650,1550,650,1600,650,1600,600};

void samsungOnOff() {
  int repeats = 2;
  
  if (server.arg("repeats") != "") {
    repeats = server.arg("repeats").toInt();
  }

  Serial.println("a rawData capture from IRrecvDumpV2");
  Serial.println(repeats);
  
  int i = 1;
  while(i < repeats){
    irsend.sendRaw(rawData, 68, 38);  // Send a raw data capture at 38kHz.
    Serial.println(i);
    delay(20);
    i++;
  }
  delay(2000);

  server.send(200, "text/plain", "samsungOnOff: OK");
}

void sonyOnOff() {
  int repeats = 2;
  
  if (server.arg("repeats") != "") {
    repeats = server.arg("repeats").toInt();
  }

  Serial.println("Sony");
  Serial.println(repeats);
  
  irsend.sendSony(21516, 15, repeats);  // 12 bits & 2 repeats
  delay(2000);

  server.send(200, "text/plain", "sonyOnOff: OK");
}

void sonyRemote() {
  int button = 21516; // default button on/off
  int repeats = 2;    // 15 = 1 irl volume

  if (server.arg("button") != "") {
    button = server.arg("button").toInt();
  }
  
  if (server.arg("repeats") != "") {
    repeats = server.arg("repeats").toInt();
  }

  Serial.println("Sony");
  Serial.println(repeats);
  
  irsend.sendSony(button, 15, repeats);  // 12 bits & 2 repeats
  delay(2000);

  server.send(200, "text/html", "<style> a.button { border: solid 1px; padding: 1em; display: block; } </style> <table> <tr> <td><a href='/sonyRemote?button=21004&repeats=2' class='button'>SA-CD/CD</a></td> <td><a href='/sonyRemote?button=8716&repeats=2' class='button'>Video 1</a></td> </tr> <tr> <td><a href='/sonyRemote?button=25612&repeats=255' class='button'>Volume -74</a></td> <td><a href='/sonyRemote?button=25612&repeats=255' class='button'>Volume -74</a></td> </tr> <tr> <td><a href='/sonyRemote?button=25612&repeats=143' class='button'>Volume -40</a></td> <td><a href='/sonyRemote?button=9228&repeats=143' class='button'>Volume +40</a></td> </tr> <tr> <td><a href='/sonyRemote?button=25612&repeats=15' class='button'>Volume -1</a></td> <td><a href='/sonyRemote?button=9228&repeats=15' class='button'>Volume +1</a></td> </tr> <tr> <td><a href='/sonyRemote?button=25612&repeats=25' class='button'>Volume -4</a></td> <td><a href='/sonyRemote?button=9228&repeats=25' class='button'>Volume +4</a></td> </tr> <tr> <td><a href='/sonyRemote?button=25612&repeats=42' class='button'>Volume -10</a></td> <td><a href='/sonyRemote?button=9228&repeats=42' class='button'>Volume +10</a></td> </tr> </table>");
}

void setup() {
  irsend.begin();
#if ESP8266
  Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY);
#else  // ESP8266
  Serial.begin(115200, SERIAL_8N1);
#endif  // ESP8266

  WiFi.begin("Fast", "demopwd123");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Waiting to connect…");
  }

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  server.on("/samsungOnOff", samsungOnOff);
  server.on("/sonyOnOff", sonyOnOff);
  server.on("/sonyRemote", sonyRemote);

  server.begin();
  Serial.println("Server listening");
}

void loop() {
  server.handleClient();
}
