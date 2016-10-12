# Ethernet3
Ethernet library for Arduino and Ethernetshield2 / WIZ550io / WIZ850io with Wiznet W5500 chip
based on the Ethernet2 library of arduino.org
added some new functionalities
you need to include
    #include <Ethernet3.h> // instead Ethernet.h
    #include <EthernetUdp3.h> // instead EthernetUDP.h for UDP functionality
- new init procedure**!!!**
the init of the Ethernetinterface changed, the ordner is now:
*mac, ip, subnet, gateway, dns* instead *mac, ip, dns, gateway, subnet*
which is more logical
    Ethernet.begin(mac, ip, subnet, gateway, dns)
- multicast support
multicast for udp added
- phy support

- mac address
