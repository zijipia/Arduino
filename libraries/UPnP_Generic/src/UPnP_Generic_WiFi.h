/****************************************************************************************************************************
  UPnP_Generic_WiFi.h
  
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

#ifndef UPnP_Generic_WiFi_h
#define UPnP_Generic_WiFi_h

#if defined(ESP8266)
  #include <ESP8266WiFi.h>
  #include <WiFiUdp.h>
  #include <WiFiClient.h>
#elif defined(ESP32)
  #include <WiFi.h>
  #include <WiFiUdp.h>
  #include <WiFiClient.h>
#elif USE_WIFININA
  #include <WiFiNINA_Generic.h>
  #include <WiFiUdp_Generic.h>
#endif

#include <Arduino.h>

#include <limits.h>

#define UPNP_DEBUG

#define UPNP_SSDP_PORT                    1900
#define TCP_CONNECTION_TIMEOUT_MS         6000
#define INTERNET_GATEWAY_DEVICE           "urn:schemas-upnp-org:device:InternetGatewayDevice:1"
#define PORT_MAPPING_INVALID_INDEX        "<errorDescription>SpecifiedArrayIndexInvalid</errorDescription>"
#define PORT_MAPPING_INVALID_ACTION       "<errorDescription>Invalid Action</errorDescription>"

#define RULE_PROTOCOL_TCP                 "TCP"
#define RULE_PROTOCOL_UDP                 "UDP"

// after 6 tries of updatePortMappings we will execute the more extensive addPortMapping
#define MAX_NUM_OF_UPDATES_WITH_NO_EFFECT 6

// reduce max UDP packet size to conserve memory (by default UDP_TX_PACKET_MAX_SIZE=8192)

#ifdef UDP_TX_PACKET_MAX_SIZE
  #undef UDP_TX_PACKET_MAX_SIZE
#endif

#define UDP_TX_PACKET_MAX_SIZE            1000 

#define UDP_TX_RESPONSE_MAX_SIZE          8192

const String UPNP_SERVICE_TYPE_1          = "urn:schemas-upnp-org:service:WANPPPConnection:";
const String UPNP_SERVICE_TYPE_2          = "urn:schemas-upnp-org:service:WANIPConnection:";
const String UPNP_SERVICE_TYPE_TAG_NAME   = "serviceType";
const String UPNP_SERVICE_TYPE_TAG_START  = "<serviceType>";
const String UPNP_SERVICE_TYPE_TAG_END    = "</serviceType>";

// TODO: idealy the SOAP actions should be verified as supported by the IGD before they are used
//      a struct can be created for each action and filled when the XML descriptor file is read
/*const String SOAPActions [] =
  {
    "AddPortMapping",
    "GetSpecificPortMappingEntry",
    "DeletePortMapping",
    "GetGenericPortMappingEntry",
    "GetExternalIPAddress"
  };*/

/*
  #define SOAP_ERROR_TAG "errorDescription";
  const String SOAPErrors [] =
  {
    "SpecifiedArrayIndexInvalid",
    "Invalid Action"
  };*/

/*
  enum soapActionResult
  {
  // TODO
  }*/

typedef struct _SOAPAction
{
  const char *name;
} SOAPAction;

typedef void (*callback_function)();

typedef struct _gatewayInfo
{
  // router info
  IPAddress host;
  int       port;                 // this port is used when getting router capabilities and xml files
  String    path;                 // this is the path that is used to retrieve router information from xml files

  // info for actions
  int       actionPort;           // this port is used when performing SOAP API actions
  String    actionPath;           // this is the path used to perform SOAP API actions
  String    serviceTypeName;      // i.e "WANPPPConnection:1" or "WANIPConnection:1"
} gatewayInfo;

typedef struct _upnpRule
{
  int       index;
  String    devFriendlyName;
  IPAddress internalAddr;
  int       internalPort;
  int       externalPort;
  String    protocol;
  int       leaseDuration;
} upnpRule;

typedef struct _upnpRuleNode
{
  _upnpRule       *upnpRule;
  _upnpRuleNode   *next;
} upnpRuleNode;

enum portMappingResult
{
  PORT_MAP_SUCCESS,           // port mapping was added
  ALREADY_MAPPED,             // the port mapping is already found in the IGD
  EMPTY_PORT_MAPPING_CONFIG,
  NETWORK_ERROR,
  TIMEOUT,
  NOP                         // the check is delayed
};

/////////////////////////////////////////////////////////////////////

class UPnP
{
  public:
    UPnP(unsigned long timeoutMs);
    ~UPnP();

    // when the ruleIP is set to the current device IP, the IP of the rule will change if the device changes its IP
    // this makes sure the traffic will be directed to the device even if the IP chnages
    void                addPortMappingConfig(IPAddress ruleIP /* can be NULL */, int rulePort, String ruleProtocol, int ruleLeaseDuration, String ruleFriendlyName);
    portMappingResult   commitPortMappings();
    portMappingResult   updatePortMappings(unsigned long intervalMs, callback_function fallback = NULL /* optional */);
    bool                printAllPortMappings();
    void                printPortMappingConfig();  // prints all the port mappings that were added using `addPortMappingConfig`
    bool                testConnectivity(unsigned long startTime = 0);

  private:
    bool        connectUDP();
    void        broadcastMSearch();
    bool        waitForUnicastResponseToMSearch(gatewayInfo *deviceInfo, IPAddress gatewayIP);
    bool        getGatewayInfo(gatewayInfo *deviceInfo, long startTime);
    bool        isGatewayInfoValid(gatewayInfo *deviceInfo);
    void        clearGatewayInfo(gatewayInfo *deviceInfo);
    bool        connectToIGD(IPAddress host, int port);
    bool        getIGDEventURLs(gatewayInfo *deviceInfo);
    bool        addPortMappingEntry(gatewayInfo *deviceInfo, upnpRule *rule_ptr);
    bool        verifyPortMapping(gatewayInfo *deviceInfo, upnpRule *rule_ptr);
    bool        deletePortMapping(gatewayInfo *deviceInfo, upnpRule *rule_ptr);
    bool        applyActionOnSpecificPortMapping(SOAPAction *soapAction, gatewayInfo *deviceInfo, upnpRule *rule_ptr);
    void        removeAllPortMappingsFromIGD();
    //char*       ipAddressToCharArr(IPAddress ipAddress);  // ?? not sure this is needed
    void        upnpRuleToString(upnpRule *rule_ptr);
    String      getSpacesString(int num);
    IPAddress   getHost(String url);
    int         getPort(String url);
    String      getPath(String url);
    String      getTagContent(const String &line, String tagName);

    /* members */
    upnpRuleNode*   _headRuleNode;
    unsigned long   _lastUpdateTime;
    unsigned long   _timeoutMs;  // 0 for blocking operation

    WiFiUDP         _udpClient;
    WiFiClient      _UPnPClient;

    gatewayInfo     _gwInfo;
    unsigned long   _consequtiveFails;
};

#endif    // UPnP_Generic_WiFi_h
