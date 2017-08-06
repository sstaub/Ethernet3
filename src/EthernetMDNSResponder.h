// Port of  WINC1500 MDNS Responder to WIZnet5500.
// Author: Tony DiCola
//         Michael Blank
// This MDNSResponder class implements just enough MDNS functionality to respond
// to name requests, for example 'foo.local'.  This does not implement any other
// MDNS or Bonjour functionality like services, etc.
//
// Copyright (c) 2016 Adafruit Industries.  All right reserved.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

#ifndef ETHERNETMDNSRESPONDER_H
#define ETHERNETMDNSRESPONDER_H

#include "Ethernet3.h"
#include "EthernetUdp3.h"
#include "utility/util.h"

class EthernetMDNSResponder {
public:
  EthernetMDNSResponder();
  ~EthernetMDNSResponder();
  bool begin(const char* _name, uint32_t _ttlSeconds = 3600);
  void poll();

private:
  bool parseRequest();
  void replyToRequest();

private:
  String name;
  uint32_t ttlSeconds;

  int minimumExpectedRequestLength;

  // UDP socket for receiving/sending MDNS data.
  EthernetUDP udpSocket;
};

#endif
