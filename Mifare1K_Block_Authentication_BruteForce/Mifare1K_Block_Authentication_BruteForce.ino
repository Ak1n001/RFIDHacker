#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9
#define SS_PIN 10

MFRC522 rfid(SS_PIN, RST_PIN);

// List of known keys to try
byte knownKeys[][6] = {
  {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},
  {0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5},
  {0xD3, 0xF7, 0xD3, 0xF7, 0xD3, 0xF7},
  {0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
  {0x4D, 0x3A, 0x99, 0xC3, 0x51, 0xDD},
  {0x1A, 0x98, 0x2C, 0x7E, 0x45, 0x9A}
};

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  Serial.println("Scan a MIFARE Classic card to try keys on all blocks...");
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    return;
  }

  for (byte block = 0; block < 64; block++) {
    bool success = false;

    for (byte k = 0; k < sizeof(knownKeys) / 6; k++) {
      MFRC522::MIFARE_Key key;
      memcpy(&key.keyByte, knownKeys[k], 6);

      MFRC522::StatusCode status = rfid.PCD_Authenticate(
        MFRC522::PICC_CMD_MF_AUTH_KEY_A,
        block,
        &key,
        &(rfid.uid)
      );

      if (status == MFRC522::STATUS_OK) {
        Serial.print("✅ Block ");
        Serial.print(block);
        Serial.print(" authenticated with key: ");
        for (byte i = 0; i < 6; i++) {
          Serial.print(key.keyByte[i], HEX);
          Serial.print(" ");
        }
        Serial.println();
        success = true;
        break;
      }
    }

    if (!success) {
      Serial.print("❌ Block ");
      Serial.print(block);
      Serial.println(" authentication failed with known keys.");
    }
  }

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
  delay(2000);  // Wait before next scan
}