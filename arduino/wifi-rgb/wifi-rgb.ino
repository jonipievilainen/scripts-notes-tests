#include <ESP8266WiFi.h>            
#include <ESP8266WebServer.h>

const int led1 = 12;
const int led2 = 13;
const int led3 = 15;
const int led4 = 14;

ESP8266WebServer server(80);   //Web server object. Will be listening in port 80 (default for HTTP)

void handleSpecificArg() { 
  
  String message = "";
  int r = 0;
  int g = 0;
  int b = 0;
  int w = 0;

  message = "";
  
  if (server.arg("b") != ""){
    b = server.arg("b").toInt();
    message += "b = ";
    message += server.arg("b");     //Gets the value of the query parameter
  }

  if (server.arg("r") != ""){
    r = server.arg("r").toInt();
    message += " r = ";
    message += server.arg("r");     //Gets the value of the query parameter
  }

  if (server.arg("g") != ""){
    g = server.arg("g").toInt();
    message += " g = ";
    message += server.arg("g");     //Gets the value of the query parameter
  }

  if (server.arg("w") != ""){
    w = server.arg("w").toInt();
    message += " w = ";
    message += server.arg("w");     //Gets the value of the query parameter
  }

  analogWrite(led1, b);
  analogWrite(led2, r);
  analogWrite(led3, g   );
  analogWrite(led4, w   );
  
  server.send(200, "text/plain", message);          //Returns the HTTP response

}

void setup() {
  Serial.begin(115200);

  pinMode(led1, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  
  WiFi.begin("Tech_D0049668", "DDKKMPUV"); //Connect to the WiFi network
  
  while (WiFi.status() != WL_CONNECTED) { //Wait for connection
    
    delay(500);
    Serial.println("Waiting to connect…");
  
  }

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //Print the local IP to access the server
  server.on("/specificArgs", handleSpecificArg);   //Associate the handler function to the path
  
  server.begin();                                       //Start the server
  Serial.println("Server listening");   

}

void loop() {

  server.handleClient();    //Handling of incoming requests

}
