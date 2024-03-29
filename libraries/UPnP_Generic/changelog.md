## UPnP_Generic Library

[![arduino-library-badge](https://www.ardu-badge.com/badge/UPnP_Generic.svg?)](https://www.ardu-badge.com/UPnP_Generic)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/UPnP_Generic.svg)](https://github.com/khoih-prog/UPnP_Generic/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/UPnP_Generic/blob/master/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/UPnP_Generic.svg)](http://github.com/khoih-prog/UPnP_Generic/issues)

---
---

## Table of Contents

* [Changelog](#changelog)
  * [Releases v3.5.0](#releases-v350)
  * [Releases v3.4.2](#releases-v342)
  * [Releases v3.4.1](#releases-v341)
  * [Major Releases v3.4.0](#major-releases-v340)
  * [Major Releases v3.3.0](#major-releases-v330)
  * [Major Releases v3.2.0](#major-releases-v320)
  * [Releases v3.1.5](#releases-v315)
  * [Releases v3.1.4](#releases-v314)

---
---
       
## Changelog

### Releases v3.5.0

1. Use new [Ethernet_Generic library](https://github.com/khoih-prog/Ethernet_Generic) as default for W5x00.
2. Rewrite to avoid `multiple-definitions` linker error for multiple-file project
3. Add example [multiFileProject_Ethernet](examples/Generic/Ethernet/multiFileProject_Ethernet) and [multiFileProject_WiFiNINA](examples/Generic/WiFiNINA/multiFileProject_WiFiNINA) to demo how to avoid `multiple-definitions` linker error for multiple-file project
4. Add support to SPI1 for RP2040 using [arduino-pico core](https://github.com/earlephilhower/arduino-pico)
5. Add support SPI2 for ESP32
6. Rewrite all the examples to support new features
7. Update `Packages' Patches`

### Releases v3.4.3

1. Add support to Teensy 4.1, using QNEthernet v0.10.0+

### Releases v3.4.2

1. Auto detect ESP32 core version. Fix bug in examples for WT32_ETH01

### Releases v3.4.1

 1. Update `platform.ini` and `library.json` to use original `khoih-prog` instead of `khoih.prog` after PIO fix
 2. Update `Packages' Patches`
 
### Major Releases v3.4.0

 1. Add support to **Portenta_H7**, using either WiFi or Vision-shield Ethernet
 2. Add examples with new features

### Major Releases v3.3.0

 1. Add support to **WT32_ETH01 (ESP32 + LAN8720)** boards
 2. Add examples with new features

### Major Releases v3.2.0

 1. Add support to RP2040-based boards, such as **RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [**Earle Philhower's arduino-pico** core](https://github.com/earlephilhower/arduino-pico).
 2. Add support to RP2040-based boards, such as **Nano_RP2040_Connect, RASPBERRY_PI_PICO, ADAFRUIT_FEATHER_RP2040 and GENERIC_RP2040**, using [**Arduino-mbed RP2040** core](https://github.com/arduino/ArduinoCore-mbed).
 3. Add support to ESP32-S2 and ESP32-C3-based boards, such as **ARDUINO_ESP32S2_DEV, ARDUINO_FEATHERS2, ARDUINO_MICROS2, ARDUINO_METRO_ESP32S2, etc.**
 4. Update examples
 5. Update `Packages' Patches
 6. Fix compiler warnings.
 7. Verify library working with new core ESP8266 v3.0.0
 8. Verify library working with new core ESP32 v1.0.6
 9. Add Version String and Table of Contents

### Releases v3.1.5

1. Fix issue with nRF52 and STM32F/L/H/G/WB/MP1 using ESP8266/ESP32-AT
2. Update Platform.ini to support PlatformIO 5.x owner-based dependency declaration.
3. Enhance examples.


#### Releases v3.1.4

1. Initial coding for Generic boards using many different WiFi/Ethernet modules/shields.
2. Add more examples


