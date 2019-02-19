const int led1 = 10; //b
const int led2 = 6; //r
const int led3 = 2; //g

String dataFromClient = "0,0,0,0";
int g = 1;

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  Serial.begin(9600);

  Serial.println("Type RBG color like this: <blue>,<red>,<green> . Example 244,244,244 .");
}

void loop() {
  
  if (Serial.available() > 0) {
    dataFromClient = Serial.readString() + ",0";
    g = 1;
  }
  
  while(dataFromClient.indexOf(",")!=-1){
    // Serial.println(dataFromClient.substring(0,dataFromClient.indexOf(",")).toInt());

    int led = 0;
    switch (g) {
      case 1:
        led = led1;
        break;
      case 2:
        led = led2;
        break;
      case 3:
        led = led3;
        break;
      default:
        led = 0;
        break;
    }

    analogWrite(led, dataFromClient.substring(0,dataFromClient.indexOf(",")).toInt());

    
    dataFromClient = dataFromClient.substring(dataFromClient.indexOf(",")+1);
    g++;
  }
}
