# RFID UID Brute Force & UID Changer

This Arduino project uses the MFRC522 RFID reader module to:
- Attempt authentication on each block of a MIFARE Classic 1K card using a known-key dictionary
- Identify which blocks are accessible
- (On magic cards) overwrite the card's UID with a custom value

> ⚠️ **Disclaimer**: This project is for educational and personal testing purposes only. Do not use it for unauthorized access or modification of secure systems.

## 🔧 Hardware Requirements
- Arduino Uno (or compatible board)
- MFRC522 RFID module
- MIFARE Classic 1K card or magic UID-writable card (Gen 1A)
- Jumper wires

## 🧪 Features
- Dictionary-based key authentication (6 common default keys)
- Status messages for success/failure per block
- Supports both regular and UID-writable cards
- Serial output for debugging and verification

## 🚀 Getting Started
1. Connect your MFRC522 to your Arduino as per standard SPI wiring.
2. Upload one of the sketches via the Arduino IDE.
3. Open the Serial Monitor at 9600 baud.
4. Scan a card and follow on-screen prompts.

## 🛡 Security Note
MIFARE Classic cards are considered insecure for sensitive applications. This tool demonstrates why strong encryption (like AES in DESFire cards) is important.

## ✍️ Author
Akın – Computer Engineer & cybersecurity enthusiast

![image](https://github.com/user-attachments/assets/98ffd8da-947a-4ad9-b1de-4e432921dade)
