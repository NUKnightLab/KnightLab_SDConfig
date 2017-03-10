# KnightLab_SDConfig

A library for reading a simple config file from the SD card of an Adalogger

Config format is single-space-delimited key-value pairs. One per line. There is
no format or integrity checking.

Max length for keys or values is 30 characters

Note: pulls pin 8 HIGH during read, specifically for use with Feather M0 LoRa

## To use:
  - include `<KnightLab_SDConfig.h>`
  - `readSDConfig(FILENAME)` to read the config file
  - `getConfig(KEY)` to get the config

Requires SdFat which you can get here: https://github.com/greiman/SdFat

This library has been extracted from the Knight Lab Sensor Grid project. Design is
pretty specific to the needs of that project, but has no Sensor Grid dependencies.
If you find it useful, let us know.
