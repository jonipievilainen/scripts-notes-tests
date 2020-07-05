const int led1 = 10; //b
const int led2 = 6; //r
const int led3 = 3; //g
const int led4 = 14; //w

int b = 0;
int r = 0;
int g = 0;

int ls = 80;
int steps = 1;

void setup() {
  // put your setup code here, to run once:
  pinMode(led1, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);

  Serial.begin(115200);
}

void loop() {

  // Serial.print("11111/\r");
  changeColor(led1, 20, 223);
  changeColor(led2, 20, 100);
  changeColor(led3, 20, 66);

  Serial.print("22222\r");
  changeColor(led1, 223, 100);
  Serial.print("333333\r");
  changeColor(led2, 100, 10);
  Serial.print("44444\r");
  changeColor(led3, 66, 254);

  // Serial.print("3333\r");
  changeColor(led1, 100, 0);
  changeColor(led2, 10, 0);
  changeColor(led3, 254, 0);
}

bool changeColor(int led, int x, int xNext){
  if(x == xNext){
    return false;
  }
  
  if(x < xNext){
    while(x < xNext){
      analogWrite(led, x);
      x = x + steps;
      delay(ls);
    }
  }else{
    while(x > xNext){
      analogWrite(led, x);
      x = x - steps;
      delay(ls);
    }
  }
  return true;
}
