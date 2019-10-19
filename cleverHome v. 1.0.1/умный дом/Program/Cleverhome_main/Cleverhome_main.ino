#include <SPI.h>
#include <MFRC522.h> // библиотека "RFID".
#define SS_PIN 53
#define RST_PIN 5
#define R1_RED 4
#define R1_GREEN 10
#define R1_BLUE 11
#define R2_RED 13
#define R2_GREEN 3
#define R2_BLUE 2
#define R3_RED 6
#define R3_GREEN 9
#define R3_BLUE 12
#define DOOR 48
#define DOOR_LIGHT 49
//-----------------------------------------------SETTINGS-----------------------------------------
bool debugMode = 1;
//------------------------------------------------SETUP-------------------------------------------
MFRC522 mfrc522(SS_PIN, RST_PIN);
unsigned long uidDec, uidDecTemp;  // для храниения номера метки в десятичном формате
unsigned int serI;
String ser;
bool isSignal = true;
bool signalAct = false;
bool Activated = false;
bool firstItr = true;
void setup() {
  Serial.begin(9600);
  if(debugMode){
    Serial.println("----------------------------DEBUG MODE--------------------------------");
    Serial.println("WARNING: In this mode signalisation can be disactivate in Serial!");
    Serial.println("If you waant to disactivate DEBUG MODE, you need change it in Settings.");
  }else{
    Serial.println("---------------------------NORMAL MODE--------------------------------");
  }
  SPI.begin();  //  инициализация SPI / Init SPI bus.
  mfrc522.PCD_Init();     // инициализация MFRC522 / Init MFRC522 card.
  pinMode(R1_RED, OUTPUT);
  pinMode(R1_GREEN, OUTPUT);
  pinMode(R1_BLUE, OUTPUT);
  pinMode(R2_RED, OUTPUT);
  pinMode(R2_GREEN, OUTPUT);
  pinMode(R2_BLUE, OUTPUT);
  pinMode(R3_RED, OUTPUT);
  pinMode(R3_GREEN, OUTPUT);
  pinMode(R3_BLUE, OUTPUT);
  pinMode(DOOR_LIGHT, OUTPUT);
  pinMode(DOOR, INPUT);

}
void loop() {
  if(Serial.available()){
    while(Serial.available()){
    ser = ser + Serial.read();
    }
    serI = ser.toInt();
    Serial.println(serI);
    if(serI == 35714){
        isSignal = false;
        Activated = false;
        firstItr = true;
        Serial.println("OK!");
        Serial.println(ser);
    }else if(serI == 8306){
      isSignal = true;
      Serial.println("OK!");
      Serial.println(ser);
    }
    ser = "";
    serI = 0;
  }
  digitalWrite(DOOR_LIGHT, isSignal);
  if(isSignal && digitalRead(DOOR) || Activated){
      if(firstItr){
      Activated = true;
      firstItr = false;
      }
      light(1, 255, 0, 0);
      light(2, 255, 0, 0);
      light(3, 255, 0, 0);
      delay(100);
      light(1, 0, 0, 0);
      light(2, 0, 0, 0);
      light(3, 0, 0, 0);
      delay(100);
  }
  // Поиск новой метки
  if (mfrc522.PICC_IsNewCardPresent()) {
  // Выбор метки
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  uidDec = 0;
  // Выдача серийного номера метки.
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    uidDecTemp = mfrc522.uid.uidByte[i];
    uidDec = uidDec * 256 + uidDecTemp;
  }
  Serial.println("Card UID: ");
  Serial.println(uidDec); // Выводим UID метки в консоль.
  if (uidDec == 699254869) // Сравниваем Uid метки, если он равен заданому то серва открывает.
    {
     isSignal = !isSignal;
    }
    delay(500);
  } 
}

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
