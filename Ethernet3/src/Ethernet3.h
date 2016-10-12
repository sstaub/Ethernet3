/*
 modified 12 Aug 2013
 by Soohwan Kim (suhwan@wiznet.co.kr)

 - 10 Apr. 2015
 Added support for Arduino Ethernet Shield 2
 by Arduino.org team

 */
#ifndef ethernet3_h
#define ethernet3_h

#include <inttypes.h>
#include "utility/w5500.h"
#include "IPAddress.h"
#include "EthernetClient.h"
#include "EthernetServer.h"
#include "Dhcp.h"



class EthernetClass {
private:
  IPAddress _dnsServerAddress;
  DhcpClass* _dhcp;
public:
  static uint8_t _state[MAX_SOCK_NUM];
  static uint16_t _server_port[MAX_SOCK_NUM];

#if defined(WIZ550io_WITH_MACADDRESS)

  // Initialize function when use the ioShield serise (included WIZ550io)
  // WIZ550io has a MAC address which is written after reset.
  // Default IP, Gateway and subnet address are also writen.
  // so, It needs some initial time. please refer WIZ550io Datasheet in details.
  int begin(void);
  void begin(IPAddress local_ip);
  void begin(IPAddress local_ip, IPAddress subnet);
  void begin(IPAddress local_ip, IPAddress subnet, IPAddress gateway);
  void begin(IPAddress local_ip, IPAddress subnet, IPAddress gateway, IPAddress dns_server);
#else
  // Initialize the Ethernet shield to use the provided MAC address and gain the rest of the
  // configuration through DHCP.
  // Returns 0 if the DHCP configuration failed, and 1 if it succeeded
  int begin(uint8_t *mac_address);
  void begin(uint8_t *mac_address, IPAddress local_ip);
  void begin(uint8_t *mac_address, IPAddress local_ip, IPAddress subnet);
  void begin(uint8_t *mac_address, IPAddress local_ip, IPAddress subnet, IPAddress gateway);
  void begin(uint8_t *mac_address, IPAddress local_ip, IPAddress subnet, IPAddress gateway, IPAddress dns_server);
#endif

  int maintain();

  uint8_t phyState(); // returns the PHYCFGR
  uint8_t link(); // returns the linkstate, 1 = linked, 0 = no link
  const char* linkReport(); // returns the linkstate as a string
  uint8_t speed(); // returns speed in MB/s
  const char* speedReport(); // returns speed as a string
  uint8_t duplex(); // returns duplex mode 0 = no link, 1 = Half Duplex, 2 = Full Duplex
  const char* duplexReport(); // returns duplex mode as a string

  void macAddress(uint8_t mac[]); // get the MAC Address
  const char* macAddressReport(); // returns the the MAC Address as a string
  IPAddress localIP();
  IPAddress subnetMask();
  IPAddress gatewayIP();
  IPAddress dnsServerIP();

  friend class EthernetClient;
  friend class EthernetServer;
};

extern EthernetClass Ethernet;

#endif
