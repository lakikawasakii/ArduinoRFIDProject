#include <MFRC522.h>
#include <SPI.h>

#define RST_PIN 9
#define NSS_PIN 10

MFRC522 rfid(NSS_PIN, RST_PIN);

const byte NUMBER_OF_ALLOWED_CARDS = 1;

byte sacuvaniUID[NUMBER_OF_ALLOWED_CARDS][4] = {
  {0xEA, 0x11, 0x81, 0x15}/*,
  {0x3B, 0x77, 0x34, 0x0B}*/
};

void setup() {
  Serial.begin(9600);
  while (!Serial);

  SPI.begin();
  rfid.PCD_Init();

  Serial.println("RC522 RFID initalized succesfully");

}

void loop() {
  
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
  byte signal = 1;
  for(byte i = 0; i < NUMBER_OF_ALLOWED_CARDS; i++)
  {
    for(byte j = 0; j < 4; j++)
    {
      if(rfid.uid.uidByte[j] != sacuvaniUID[i][j])
      {
        signal = 0;
        break;
      }
    }
  }

  if (signal == 1)
  {
    Serial.println("PRISTUP DOZVOLJEN");
  }
  else
  {
    Serial.println("PRISTUP ODBIJEN");
  }

  Serial.println();

  rfid.PICC_HaltA();

}
