/*
Sony av system RM-AAU001

irsend.sendSony(codeValue, codeLen);

Power on/off: 21516/15
Volume up: 9228/15
Volume down: 25612/15

 */

#include <IRremote.h>


int codeLen = 15;

int RECV_PIN = 11;
int BUTTON_PIN = 12;
int STATUS_PIN = 13;


IRrecv irrecv(RECV_PIN);
IRsend irsend;

void setup()
{
  Serial.begin(9600);
  // pinMode (3, OUTPUT);  //output used in library

  irrecv.enableIRIn(); // Start the receiver
  pinMode(BUTTON_PIN, INPUT);
  pinMode(STATUS_PIN, OUTPUT);
}

void loop() {

  Serial.println("send");

  loopper(21516, codeLen);
  delay (2000);

  loopper(9228, codeLen);
  delay (1000);

  loopper(25612, codeLen);
  delay (2000);

  loopper(21516, codeLen);
  delay (2000);

}//end of loop

void loopper(int c, int codeLen){
  for(int i=50; i<1000; i=i+50){
    irsend.sendSony(c, codeLen);
    delay (50);
  }
}
