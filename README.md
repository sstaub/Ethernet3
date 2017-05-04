# Ethernet3
Ethernet library for Arduino and Ethernetshield2 / WIZ550io / WIZ850io / USR-ES1 with Wiznet W5500 chip
based on the Ethernet2 library of arduino.org

added some new functionalities

you need to include

    #include <Ethernet3.h> // instead Ethernet.h
    #include <EthernetUdp3.h> // instead EthernetUdp.h for UDP functionality
    
## New init procedure **!!!**

the init of the Ethernetinterface changed, the ordner is now:

*mac, ip, subnet, gateway, dns* instead *mac, ip, dns, gateway, subnet*,
which is more logical

    Ethernet.begin(mac, ip, subnet, gateway, dns);
    
## Multicast support

multicast for udp added

    EthernetUdp udp
    upd.beginMulticast(multicastIP, port);

## PHY support

added some function to read the PHYCFGR in Ethernet3

    uint8_t phyState(); // returns the PHYCFGR
    uint8_t link(); // returns the linkstate, 1 = linked, 0 = no link
    const char* linkReport(); // returns the linkstate as a string
    uint8_t speed(); // returns speed in MB/s
    const char* speedReport(); // returns speed as a string
    uint8_t duplex(); // returns duplex mode 0 = no link, 1 = Half Duplex, 2 = Full Duplex
    const char* duplexReport(); // returns duplex mode as a string

example

    Serial.println(Ethernet.linkReport()); 

## MAC address

added some function to read the MAC address in Ethernet3, this is helpfull when you use Wiznet boards like WIZ550io with build in MAC address

    void macAddress(uint8_t mac[]); // get the MAC Address
    const char* macAddressReport(); // returns the the MAC Address as a string

example

    uint8_t mac[6]; // array for mac address
    Ethernet.macAddress(mac);

## Socketnumbers

you can decrease the socketnumbers to get more free RAM space, this must be done before Ethernet.begin(...)

the possible socketnumbers are

    Ethernet.init(1); -> 1 Socket with 16k RX/TX buffer
    Ethernet.init(2); -> 2 Socket with 8k RX/TX buffer
    Ethernet.init(4); -> 4 Socket with 4k RX/TX buffer
    Ethernet.init(); -> 8 Socket with 2k RX/TX buffer

be carefull with the MAX_SOCK_NUM in w5500.h , it cannot changed dynamicly 

example

    Ethernet.init(4); // reduce to 4 Socket, each with 4k RX/TX buffer
    Ethernet.begin();
    
## RST and CS pin settings

you can set the CS and (Hardware) RST (e.g. WIZ550io or USR-ES1), this must be done before Ethernet.begin(...)

standard is Pin 10 for CS and Pin 9 for RST

    Ethernet.setCsPin(3); // set Pin 3 for CS
    Ethernet.setRstPin(4); // set Pin 4 for RST

example

    Ethernet.setRstPin(); // set Pin 9 for RST
    Ethernet.begin();

## Hard- and Software Reset

two new functions to make resets, Softreset can done only after Ethernet.begin(...)

for Hardware Reset you need to set the Pin number

    Ethernet.softreset(); // performs a software reset
    Ethernet.hardreset(); // performs a hardware reset

example

    Ethernet.setRstPin(); // set Pin 9 for RST
    Ethernet.begin();
    Ethernet.hardreset();

