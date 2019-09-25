#define R1_RED 4
#define R1_GREEN 10
#define R1_BLUE 11
#define R2_RED 13
#define R2_GREEN 3
#define R2_BLUE 2
#define R3_RED 6
#define R3_GREEN 5
#define R3_BLUE 12

void light(byte num, byte r, byte g, byte b){
  switch (num) {
    case 1:
      analogWrite(R1_RED, r);
      analogWrite(R1_GREEN, g);
      analogWrite(R1_BLUE, b);
      break;
    case 2:
      analogWrite(R2_RED, r);
      analogWrite(R2_GREEN, g);
      analogWrite(R2_BLUE, b);
      break;
    case 3:
      analogWrite(R3_RED, r);
      analogWrite(R3_GREEN, g);
      analogWrite(R3_BLUE, b);
    default:
      
      break;
  }
}

void setup() {
  // put your setup code here, to run once:
pinMode(R1_RED, OUTPUT);
pinMode(R1_GREEN, OUTPUT);
pinMode(R1_BLUE, OUTPUT);
pinMode(R2_RED, OUTPUT);
pinMode(R2_GREEN, OUTPUT);
pinMode(R2_BLUE, OUTPUT);
pinMode(R3_RED, OUTPUT);
pinMode(R3_GREEN, OUTPUT);
pinMode(R3_BLUE, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i = 1; i<4; i++){
    for(int a = 0; a<255; a++){
      byte b = 255 - a;
      light(i, a, 0, b);
      delay(10);
      }
    }
    for(int i = 1; i<4; i++){
    for(int a = 0; a<255; a++){
      byte b = 255 - a;
      light(i, b, a, 0);
      delay(10);
      }
    }
    for(int i = 1; i<4; i++){
    for(int a = 0; a<255; a++){
      byte b = 255 - a;
      light(i, 0, b, a);
      delay(10);
      }
    }
}
