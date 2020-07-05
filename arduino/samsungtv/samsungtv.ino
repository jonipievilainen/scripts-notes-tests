
//Turn Samsung TV on/off repeatedly to test program.
//IR LED connected to pin 3.

// #include <IRremote.h>

#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>


const uint16_t kIrLed = 4;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).

IRsend irsend(kIrLed);

unsigned int power[] = {4550,4400,600,1650,550,1650,600,1650,
550,550,600,500,600,550,550,550,600,500,600,1650,600,1600,600,
1650,550,550,600,500,600,550,600,500,600,500,650,450,650,1600,
600,500,650,450,650,500,600,500,600,500,600,550,600,1600,600,
500,650,1600,650,1550,650,1600,650,1550,650,1600,650,1600,600};

//IRsend irsend;

void setup()
{
  Serial.begin(9600);
  pinMode (3, OUTPUT);  //output used in library
}

void loop() {

  Serial.println("send");

 // irsend.sendRaw(power,68,38);
 irsend.sendRaw(power, 68, 38);  // Send a raw data capture at 38kHz.
     
  delay (5000);

}//end of loop
