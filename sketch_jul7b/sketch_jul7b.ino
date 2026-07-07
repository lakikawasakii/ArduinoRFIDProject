#include <Servo.h>
#include <MFRC522.h>
#include <SPI.h>

#define NSS_PIN 10
#define RST_PIN 9

Servo servo;

MFRC522 rfid(NSS_PIN, RST_PIN);

const byte NUMBER_OF_ALLOWED_CARDS = 1;

byte sacuvaniUID[NUMBER_OF_ALLOWED_CARDS][4] = {
  {0x3B, 0x77, 0x34, 0x0B}
};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  servo.attach(8);
  servo.write(0);

  while (!Serial);

  SPI.begin();
  rfid.PCD_Init();

  Serial.println("RC522 RFID initalized succesfully");

}

void loop() {
  // put your main code here, to run repeatedly:
  if(!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial() ){
    return;
  }

  Serial.println("Card Detected!");

  Serial.print("UID : ");
  for(byte i = 0; i < rfid.uid.size; i++)
  {
    Serial.print(rfid.uid.uidByte[i] < 0x10 ?  " 0" : " ");
    Serial.print(rfid.uid.uidByte[i], HEX);
  }
  Serial.println();
  byte signal = 0; 
  for(byte i = 0; i < NUMBER_OF_ALLOWED_CARDS; i++) {
    bool trenutnaMecuje = true;
    for(byte j = 0; j < 4; j++) {
      if(rfid.uid.uidByte[j] != sacuvaniUID[i][j]) {
        trenutnaMecuje = false;
        break;
      }
    }
    if(trenutnaMecuje) {
      signal = 1; 
      break;
    }
  }

  if (signal == 1)
  {
    Serial.println("PRISTUP DOZVOLJEN");
    servo.write(180);
    delay(3000);
    servo.write(0);
  }
  else
  {
    Serial.println("PRISTUP ODBIJEN");
  }
  
  Serial.println();

  rfid.PICC_HaltA();
  delay(500);
  servo.write(0);
}
