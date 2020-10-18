const int led1 = 10; //b
const int led2 = 6; //r
const int led3 = 3; //g
const int led4 = 14; //w

int b = 0;
int r = 0;
int g = 0;

int ls = 100;
int steps = 1;

//int l = random(1, 255);
//int ll = random(1, 255);
//int lll = random(1, 255);
//int llll = random(1, 255);

int l = random(1, 100);
int ll = random(1, 100);
int lll = random(1, 100);
int llll = random(1, 100);

void setup() {
  // put your setup code here, to run once:
  pinMode(led1, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);

  Serial.begin(115200);
}

void loop() {

//  int j = random(1, 255);
//  int jj = random(1, 255);
//  int jjj = random(1, 255);
//  int jjjj = random(1, 255);

  int j = random(1, 100);
  int jj = random(1, 100);
  int jjj = random(1, 100);
  int jjjj = random(1, 100);

  // Serial.print("11111/\r");
  changeColor(led1, l, j);
  changeColor(led2, ll, jj);
  changeColor(led3, lll, jjj);

  l = j;
  ll = jj;
  lll = jjj;
  llll = jjjj;
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
