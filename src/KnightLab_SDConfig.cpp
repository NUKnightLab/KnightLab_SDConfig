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
#define MAX_LEN 100
static SdFat SD;

static File _configFile;

int _readSDConfig(char *configFileName) {
    Serial.print("Reading SD card ..");
    if (!SD.begin(CHIP_SELECT_PIN)) {
        Serial.println(" .. SD card init failed!");
        return 1;
    }
    Serial.println(" .. done");
    Serial.print("Reading Config File: "); Serial.print(configFileName);
    Serial.println("..");
    _configFile = SD.open(configFileName);
    if (_configFile) {
        char key[MAX_LEN], val[MAX_LEN];
        char* keyPtr;
        char* valPtr;
        int size = _configFile.size();
        Serial.print("Config file size: ");
        Serial.println(size);
        while (_configFile.available()) {
            memset(key, 0, MAX_LEN);
            memset(val, 0, MAX_LEN);
            keyPtr = key;
            valPtr = val;
            for (char c=_configFile.read(); c != ' ' && c != '\n'; c=_configFile.read()) {
                *keyPtr = c;
                keyPtr++;
                //for debugging
                /*
                int ASCII = c - '0';
                Serial.print("key ASCII: ");
                Serial.print(ASCII);
                Serial.print('|'); */
            }
            if (strlen(key) == 0) {
              //Serial.println("Key is null");
              continue;
            }
            if (VERBOSE)
                Serial.print(key);
            int count = 0;
            char valC;
            for (valC=_configFile.read(); valC != '\n' && valC != '\r' && (_configFile.position() < size); valC=_configFile.read()) {
                *valPtr = valC;
                valPtr++;
                count++;
                /*
                int ASCII = valC - '0';
                Serial.print(ASCII);
                Serial.print('|'); */
            }
            if (valC != '\n' && valC != '\r' && valC != ' '){
              *valPtr = valC;
              valPtr++;
              count++;
              /*
              int ASCII = valC - '0';
              Serial.print(ASCII); */
            }

            if (VERBOSE)
                Serial.print(" "); Serial.println(val);
            addConfig(key, val);
        }
        Serial.println(".. done");
        _configFile.close();
        return 0;
    } else {
        Serial.print("Error opening "); Serial.println(configFileName);
        return 1;
    }
}

int readSDConfig(char *configFileName) {
    digitalWrite(RFM95_CS, HIGH);
    int status = _readSDConfig(configFileName);
    digitalWrite(RFM95_CS, LOW);
    return status;
}
