const int led1 = 12; //b
const int led2 = 13; //r
const int led3 = 15; //g
const int led4 = 14; //w

int b = 0;
int r = 0;
int g = 0;

int ls = 50;
int steps = 5;

void setup() {
  // put your setup code here, to run once:
  pinMode(led1, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);

  Serial.begin(115200);
}

void loop() {
  changeColor(led1, 0, 223);
  changeColor(led2, 0, 244);
  changeColor(led3, 0, 66);

  changeColor(led1, 223, 100);
  changeColor(led2, 244, 10);
  changeColor(led3, 66, 0);

  changeColor(led1, 100, 0);
  changeColor(led2, 10, 0);
  changeColor(led3, 0, 0);
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
