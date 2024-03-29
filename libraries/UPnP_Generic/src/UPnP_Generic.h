/****************************************************************************************************************************
  UPnP_Generic.h
  
  For all Generic boards such as ESP8266, ESP32, WT32_ETH01, SAMD21/SAMD51, nRF52, STM32F/L/H/G/WB/MP1,Teensy, Portenta_H7
  with WiFiNINA, ESP8266/ESP32 WiFi, ESP8266/ESP32-AT, W5x00, ENC28J60, Native-Ethernet, Portenta Ethernet/WiFi
  
  DDNS_Generic is a library to automatically add port mappings to router using UPnP SSDP
  (Simple Service Discovery Protocol) in order to provide access to the local Web Services from the Internet.
  
  Based on and modified from Ofek Pearl's TinyUPnP Library (https://github.com/ofekp/TinyUPnP)
  Built by Khoi Hoang https://github.com/khoih-prog/UPnP_Generic
  Licensed under GPL-3.0 license
  
  Version: 3.5.0
  
  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  3.1.4  K Hoang      23/09/2020 Initial coding for Generic boards using many WiFi/Ethernet modules/shields.
  3.1.5  K Hoang      28/09/2020 Fix issue with nRF52 and STM32F/L/H/G/WB/MP1 using ESP8266/ESP32-AT
  3.2.0  K Hoang      11/06/2021 Add support to RP2040-based boards using ESP-AT, WiFiNINA, W5x00 / ENC28J60
  3.3.0  K Hoang      16/07/2021 Add support to WT32_ETH01 (ESP32 + LAN8720)
  3.4.0  K Hoang      16/09/2021 Add support to Portenta_H7, using either WiFi or Vision-shield Ethernet
  3.4.1  K Hoang      12/10/2021 Update `platform.ini` and `library.json`
  3.4.2  K Hoang      01/12/2021 Auto detect ESP32 core version. Fix bug in examples for WT32_ETH01
  3.4.3  K Hoang      01/12/2021 Add support to Teensy 4.1, using QNEthernet
  3.5.0  K Hoang      13/04/2021 Use Ethernet_Generic library as default. Support SPI1/SPI2 for RP2040/ESP32
 *****************************************************************************************************************************/

#ifndef UPnP_Generic_h
#define UPnP_Generic_h

#include "UPnP_Generic_Debug.h"

/////////////////////////////////////////////////////////////////////

#define UPNP_GENERIC_VERSION             "UPnP_Generic v3.5.0"

#define UPNP_GENERIC_VERSION_MAJOR       3
#define UPNP_GENERIC_VERSION_MINOR       5
#define UPNP_GENERIC_VERSION_PATCH       0

#define UPNP_GENERIC_VERSION_INT        3005000

/////////////////////////////////////////////////////////////////////

#include "UPnP_Generic.hpp"
#include "UPnP_Generic_Impl.h"

#endif    // UPnP_Generic_h
