/**
 * KnightLab_SDConfig.cpp
 *
 * Written by Scott B. Bradley (@scott2b) for Knight Lab
 *
 * Read a config file from an Adalogger SD card. Configs are single-space-delimited
 * key/value pairs, one per line. Be sure your config is in the right format,
 * there is nothing really here in terms of checking your format.
 *
 * This is a read-once approach. The first instance found for a given key will
 * be the config used.
 *
 * Usage:
 * readSDConfig(char *configFileName) // Read the config from file on SD card
 * getConfig(char *key)               // Get the value for key. Can return NULL
 *
 * Adalogger notes:
 * SD card attached to SPI bus as follows:
 *     MOSI - pin 11
 *     MISO - pin 12
 *     CLK - pin 13
 *     CS - pin 4
 */
#include "KnightLab_SDConfig.h"
#define CHIP_SELECT_PIN 10 // Feather 32u4 and M0
#define RFM95_CS 8 // Must be pulled HIGH on M0 LoRa Feather
#define VERBOSE true

static File _configFile;

void _readSDConfig(char *configFileName) {
    Serial.print("Reading SD card ..");
    if (!SD.begin(CHIP_SELECT_PIN)) {
        Serial.println(" .. SD card init failed!");
        return;
    }
    Serial.println(" .. done");
    Serial.print("Reading Config File: "); Serial.print(configFileName);
    Serial.println("..");
    _configFile = SD.open(configFileName);
    if (_configFile) {
        uint8_t MAX = 30;
        char key[MAX], val[MAX];
        char* keyPtr;
        char* valPtr;
        while (_configFile.available()) {
            memset(key, 0, MAX);
            memset(val, 0, MAX);
            keyPtr = key;
            valPtr = val;
            for (char c=_configFile.read(); c != ' '; c=_configFile.read()) {
                *keyPtr = c;
                keyPtr++;
            }
            if (VERBOSE)
                Serial.print(key);
            for (char c=_configFile.read(); c != '\n' && c != EOF; c=_configFile.read()) {
                *valPtr = c;
                valPtr++;
            }
            if (VERBOSE)
                Serial.print(" "); Serial.println(val);
            addConfig(key, val);
        }
        Serial.println(".. done");
        _configFile.close();
    } else {
        Serial.print("Error opening "); Serial.println(configFileName);
    }
    digitalWrite(RFM95_CS, LOW);
}

void readSDConfig(char *configFileName) {
    digitalWrite(RFM95_CS, HIGH);
    _readSDConfig(configFileName);
    digitalWrite(RFM95_CS, LOW);
}
