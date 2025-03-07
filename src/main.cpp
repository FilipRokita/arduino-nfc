#include <Arduino.h>
#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>

PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc(pn532_i2c);

// Set this to true for write mode, false for read mode
bool writeMode = true;

void setup() {
    Serial.begin(115200);
    Serial.println("Initializing NFC module...");
    nfc.begin();
}

// Function to clean the NFC tag
bool cleanTag() {
    Serial.println("Cleaning tag...");
    bool cleaned = nfc.clean();
    if (cleaned) {
        Serial.println("Tag cleaned successfully.");
    } else {
        Serial.println("Failed to clean the tag. The tag might be empty or not writable.");
    }
    return cleaned;
}

// Function to format the NFC tag to NDEF
bool formatTag() {
    Serial.println("Formatting tag to NDEF...");
    bool formatted = nfc.format();
    if (formatted) {
        Serial.println("Tag formatted successfully to NDEF format.");
    } else {
        Serial.println("Failed to format the tag. The tag may not support NDEF.");
    }
    return formatted;
}

// Function to write a URL to the NFC tag
bool writeTag() {
    Serial.println("Writing URL to tag...");
    NdefMessage message;
    message.addUriRecord("https://google.com/"); // Change this URL to your desired link
    
    bool written = nfc.write(message);
    if (written) {
        Serial.println("Write successful! Try reading it with your phone.");
    } else {
        Serial.println("Write failed. Ensure the tag supports writing.");
    }
    return written;
}

// Function to read an NFC tag
void readTag() {
    Serial.println("Waiting for an NFC tag to read...");
    
    if (nfc.tagPresent()) {
        NfcTag tag = nfc.read();
        Serial.println("NFC Tag detected!");
        Serial.print("Tag Type: ");
        Serial.println(tag.getTagType());
        Serial.print("UID: ");
        Serial.println(tag.getUidString());

        if (tag.hasNdefMessage()) {
            Serial.println("NDEF Message found:");
            NdefMessage message = tag.getNdefMessage();
            for (int i = 0; i < message.getRecordCount(); i++) {
                NdefRecord record = message.getRecord(i);
                Serial.print("Record ");
                Serial.print(i + 1);
                Serial.print(": ");
                
                int payloadLength = record.getPayloadLength();
                uint8_t payload[payloadLength];
                record.getPayload(payload);
                Serial.write(payload, payloadLength);
                Serial.println();
            }
        } else {
            Serial.println("No NDEF Message found on this tag.");
        }
    } else {
        Serial.println("No NFC tag present.");
    }
}

void loop() {
    Serial.println(); // Print a new line for better readability
    Serial.println("Place an NFC tag to read or write.");
    
    if (nfc.tagPresent()) {
        Serial.println("Tag detected!");
        
        if (writeMode) {
            // Execute cleaning, formatting, and writing in sequence
            if (cleanTag() && formatTag()) {
                writeTag();
            }
        } else {
            // Read tag instead of writing
            readTag();
        }
    }
    
    delay(5000); // Wait 5 seconds before the next scan attempt
}