# KnightLab_SDConfig

A library for reading a simple config file from the SD card of an Adalogger

Config format is single-space-delimited key-value pairs. One per line. There is
no format or integrity checking. Probably potential for buffer overflows if not
careful. Use at your own risk.

## To use:
  - include `<KnightLab_SDConfig.h>`
  - `readSDConfig(FILENAME)` to read the config file
  - `getConfig(KEY)` to get the config

This library has been extracted from the Knight Lab Sensor Grid project. Design is
pretty specific to the needs of that project, but has no Sensor Grid dependencies.
If you find it useful, let us know.
