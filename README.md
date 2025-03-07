# NFC Tag Reader & Writer using PN532

This project allows you to **read, clean, format, and write data** to **Mifare Classic NFC tags** using the **PN532 module**.  
It works with **Arduino-compatible** devices and uses **I2C** for communication.

## Features
- **Read NFC tags** (Mifare Classic) and display their contents
- **Clean and format NFC tags** for NDEF compatibility
- **Write a URL** (or other NDEF messages) to an NFC tag
- **Works with iPhone & Android** NFC readers

## Requirements
- **Arduino board** (Uno, Mega, etc.)
- **PN532 NFC Module**
- **Mifare Classic NFC Tag**
- **PlatformIO / Arduino IDE**

## Installation
1. Clone this repository:
   ```sh
   git clone https://github.com/FilipRokita/arduino-nfc
   ```
2. Open the project in **PlatformIO** or **Arduino IDE**.
3. Install dependencies:
   - **Adafruit_PN532** library
   - **NDEF library** (for handling NDEF messages)
4. Connect your **PN532 module** via **I2C**:
   - `VCC` → `5V`
   - `GND` → `GND`
   - `SDA` → `A4`
   - `SCL` → `A5`

## Usage
### **1️⃣ Writing to NFC Tag**
- Set `writeMode = true;` in the code.
- Upload the sketch to your Arduino.
- Open Serial Monitor (**115200 baud**).
- Place an NFC tag near the reader.
- It will:
  - Clean the tag.
  - Format it (if needed).
  - Write a predefined **URL** to the tag.

### **2️⃣ Reading an NFC Tag**
- Set `writeMode = false;`
- Upload and open Serial Monitor.
- Place a tag near the reader.
- The program will display the tag’s **UID**, type, and stored NDEF records.

## Troubleshooting
- **If formatting fails**, the tag may be locked or require a specific authentication key.
- **If reading fails**, check wiring and make sure the tag is supported (**Mifare Classic**).
- **Not working on iPhone?**  
  Ensure the tag is **formatted for NDEF** and contains **a valid NDEF record**.

## License
This project is **open-source** under the **MIT License**.
