#include <Wire.h>
#include <hd44780.h>                       // main hd44780 header
#include <hd44780ioClass/hd44780_I2Cexp.h> // i2c expander i/o class header

hd44780_I2Cexp lcd; // declare lcd object: auto locate & auto config expander chip

const int LCD_COLS = 16;
const int LCD_ROWS = 2;

float sensor_volt;
float RS_gas; 
float RS; 
float R0;
float R00;
float ratio;
float BAC;
int R2 = 2000;

void setup()
{
  /*
   * USE ONLY USB POWER
   * 
   * I2C GND - NodeMCU GND
   * I2C Vcc - NodeMCU VU
   * I2C SDA - NodeMCU D3
   * I2C SDL - NodeMCU D4
  */
  Serial.begin(9600);
  Wire.begin(0,2);
  
  int status;
  status = lcd.begin(LCD_COLS, LCD_ROWS);
  if(status) // non zero status means it was unsuccesful
  {
    status = -status;
    hd44780::fatalError(status);
  }
  
  lcd.print("Hello, World!");
  delay(2000);
}

int r = 0;
void loop() {
  int status;
  status = lcd.begin(LCD_COLS, LCD_ROWS);
  if(status)
  {
    status = -status;
    hd44780::fatalError(status);
  }

  int sensorValue = analogRead(A0);
  sensor_volt=(float)sensorValue/1024*5.0;

  RS = (5.0-sensor_volt)/sensor_volt; // 
  R00 = RS/60.0; // 60 is found using interpolation
  Serial.print("R00 = ");
  Serial.println(R00);
  
  RS_gas = ((5.0 * R2)/sensor_volt) - R2; 
 /*-Replace the value of R0 with the value of R0 in your test -*/
  R0 = 16000;
  ratio = RS_gas/R0;// ratio = RS/R0
  double x = 0.4*ratio;   
  BAC = pow(x,-1.431);  //BAC in mg/L
  Serial.print("BAC = ");
  Serial.print(BAC*0.0001);  //convert to g/dL
  Serial.print(" g/DL\n\n");
    
  lcd.print(BAC*0.0001);
  lcd.print(" g/DL ");
  lcd.print(sensorValue);
  delay(1000); 
  r++; 
}
