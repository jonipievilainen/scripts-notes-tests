
// SoftwareSerial lib allows to use digital pins for serial connection
#include <SoftwareSerial.h>

// Tx of A6 linked to pin 4
const int pinRxNano = 4;
// Rx of A6 linked to pin 2
const int pinTxNano = 2;

//Enter here the phone number
const String phoneNumber= "+";
const String messageInit = "A6 ready";

//Create serial connection on the pin
SoftwareSerial A6GSM(pinRxNano, pinTxNano);

//Function waiting for "OK", used for various purposes
void Response(){
  int a = 0;
  Serial.println();
  while(1){
    if(A6GSM.available()){
      String dataFromA6 =A6GSM.readString();
      dataFromA6.trim();
      Serial.println(dataFromA6);
      a++;
      if(dataFromA6.indexOf("OK")>0){break;}
    }
    if(a>500){a=0;break;}
    delay(200);
  }
}

//Function used to send "AT" to A6 until it answers with "OK"
void startAT(){
  int nbAT = 0;
  while(1){
    if (nbAT==0){A6GSM.println("AT");Serial.print(".");}
    if(A6GSM.available()){
      String dataFromA6 =A6GSM.readString();
      dataFromA6.trim();
      Serial.println(dataFromA6);
      if(dataFromA6.indexOf("OK")>0){break;}
    }
    delay(200);
    nbAT++;
    if(nbAT++>10){nbAT=0;}
  } 
}

//Function used to send a sms
void envoieSMS(String numeroEnvoi, String messageEnvoi) {
  delay(200);
  Serial.println("Selection format message SMS");
  A6GSM.println("AT+CMGF=1");
  Response();
  delay(200);
  Serial.println("Envoi message SMS");
  A6GSM.print("AT+CMGS=\"");
  A6GSM.print(numeroEnvoi);
  A6GSM.println("\"");
  delay(200);
  A6GSM.print(messageEnvoi);
  delay(200);
  A6GSM.println (char(26));
  Response();
}

void setup() {
  //GSM serial connection
  A6GSM.begin(9600);
  //Usual serial connection to display on console
  Serial.begin(9600);
  delay(200);
  Serial.println("Init");
  //AT
  startAT();
  envoieSMS(phoneNumber,messageInit);
}

void loop() {
}
