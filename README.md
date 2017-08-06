# Ethernet3 v1.4
Ethernet library for Arduino and Ethernetshield2 / WIZ550io / WIZ850io / USR-ES1 with Wiznet W5500 chip
based on the Ethernet2 library of arduino.org

I added many new functionalities.

You need to include

    #include <Ethernet3.h> // instead Ethernet.h
    #include <EthernetUdp3.h> // instead EthernetUdp.h for UDP functionality
    
## New init procedure **!!!**

The init of the Ethernetinterface changed, the ordner is now:

	Ethernet.begin(mac, ip, subnet, gateway, dns);

This is more logical.

    
## Multicast support

Multicast for udp added. You need to set the Multicast IP address and port to listen.

***example***

    EthernetUdp udp
    upd.beginMulticast(multicastIP, port);

An Unicast blocking function is added to set and get the flag in a UDP socket.

	void setUnicastBlock(bool block);
	bool getUnicastBlock();

***example***

	EthernetUDP udp;
	udp.setUnicastBlock(true);
	
	// to restore the value to standard
	
	udp.setUnicastBlock(false);
	udp.setUnicastBlock();

## MDNS Responder 

The MDNS responder can listen and respond to MDNS name requests, for example a 
webserver can be accessible via the MDNS name "webserver3.local".

***example***

	char mdnsName[] = "webserver3"; 
	EthernetMDNSResponder mdnsResponder;

Setup the MDNS responder to listen to the configured name (.local will be 
appended).

***example***

	mdnsResponder.begin(mdnsName)

Call the update() function on the MDNS responder every loop iteration to
make sure it can detect and respond to name requests.
  
***example***

	mdnsResponder.poll();

	
## PHY support

Added some function to read the PHYCFGR in Ethernet3.

    uint8_t phyState(); // returns the PHYCFGR
    uint8_t link(); // returns the linkstate, 1 = linked, 0 = no link
    const char* linkReport(); // returns the linkstate as a string
    uint8_t speed(); // returns speed in MB/s
    const char* speedReport(); // returns speed as a string
    uint8_t duplex(); // returns duplex mode 0 = no link, 1 = Half Duplex, 2 = Full Duplex
    const char* duplexReport(); // returns duplex mode as a string

***example***

    Serial.println(Ethernet.linkReport()); 

## MAC address

Added some function to read the MAC address in Ethernet3, this is helpfull when you use Wiznet boards like WIZ550io with build in MAC address.

    void macAddress(uint8_t mac[]); // get the MAC Address
    const char* macAddressReport(); // returns the the MAC Address as a string

***example***

    uint8_t mac[6]; // array for mac address
    Ethernet.macAddress(mac);

## Socket RAM-Size

You can de- or increase the RAM-Size for the sockets, this must be done before Ethernet.begin(...)

The possible socketnumbers are:

    Ethernet.init(1); -> 1 Socket with 16k RX/TX buffer
    Ethernet.init(2); -> 2 Socket with 8k RX/TX buffer
    Ethernet.init(4); -> 4 Socket with 4k RX/TX buffer
    Ethernet.init(); -> 8 Socket with 2k RX/TX buffer

Be carefull with the MAX_SOCK_NUM in w5500.h , it cannot changed dynamicly.

***example***

    Ethernet.init(4); // reduce to 4 Socket, each with 4k RX/TX buffer
    Ethernet.begin();
    
## RST and CS pin settings

You can set the CS and (Hardware) RST (e.g. WIZ550io or USR-ES1), this must be done before Ethernet.begin(...)

Standard is Pin 10 for CS and Pin 9 for RST

    Ethernet.setCsPin(3); // set Pin 3 for CS
    Ethernet.setRstPin(4); // set Pin 4 for RST

***example***

    Ethernet.setRstPin(); // set Pin 9 for RST
    Ethernet.begin();

## Hard- and Software Reset

Two new functions to make resets, Softreset can done only after Ethernet.begin(...)

For Hardware Reset you need to set the Pin number.

    Ethernet.softreset(); // performs a software reset
    Ethernet.hardreset(); // performs a hardware reset

***example***

    Ethernet.setRstPin(); // set Pin 9 for RST
    Ethernet.begin();
    Ethernet.hardreset();

## Additional TCP settings in Ethernet

There are two function to set and get the retransmission timeout and retry count, this helps to solve problem with TCP connections with unexpected very long timeouts.  Beware the the timeout value multiplier is 100us!

	void Ethernet.setRtTimeOut(uint16_t timeout);
	uint16_t Ethernet.getRtTimeOut();
	void Ethernet.setRtCount(uint8_t count);
	uint8_t Ethernet.getRtCount();

***example***
	
	Ethernet.setRtTimeOut(500); // timeout 50ms
	Ethernet.setRtCount(2);
	
	// to restore the value to standard
	
	Ethernet.setRtTimeOut();
	Ethernet.setRtCount();

## Additional settings in EthernetClient

### ACK feature

A 'No Delayed ACK' function is added to set and get the flag in a TCP socket.

	void setNoDelayedACK(bool ack);
	bool getNoDelayedACK();

***example***

	EthernetClient tcp;
	tcp.setNoDelayedACK(true);
	
	// to restore the value to standard
	
	tcp.setNoDelayedACK(false);
	tcp.setNoDelayedACK();

### remoteIP and remoteMAC adresses

Two new functions for getting the IP and MAC address of a remote host.

	void remoteIP(uint8_t *ip);
	void remoteMAC(uint8_t *mac);
	
## Additional settings in EthernetUDP

### Broadcast feature in EthernetUDP

A Broadcast blocking function is added to set and get the flag in a UDP socket.

	void setBroadcastBlock(bool block);
	bool getBroadcastBlock();

***example***

	EthernetUDP udp;
	udp.setBroadcastBlock(true);
	
	// to restore the value to standard
	
	udp.setBroadcastBlock(false);
	udp.setBroadcastBlock();
	
### remoteIP and remoteMAC adresses

Two new functions for getting the IP and MAC address of a remote host.

	void remoteIP(uint8_t *ip);
	void remoteMAC(uint8_t *mac);
