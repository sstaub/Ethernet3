/*
 MDNS Web Server  (based on WiFiMDNSWebServer)

 A simple web server that shows the value of the analog input pins,
 and exposes itself on the MDNS name 'webserver3.local'.

 On Linux (like Ubuntu 15.04) or OSX you can access the web page
 on the device in a browser at 'http://webserver3.local/'.

 On Windows you'll first need to install the Bonjour Printer Services
 from:
   https://support.apple.com/kb/dl999?locale=en_US
 Then you can access the device in a browser at 'http://ethernet3.local/'.


 Circuit:
 * Ethernet Shield2 (with WIZnet5500)
 * Analog inputs attached to pins A0 through A5 (optional)

 created 13 July 2010
 by dlf (Metodo2 srl)
 modified 31 May 2012
 by Tom Igoe
 modified 27 January 2016
 by Tony DiCola
 modified 06 August 2017
 by Michael Blank

*/

#include <SPI.h>
#include <Ethernet3.h>
#include <EthernetMDNSResponder.h>

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
//IPAddress ip(192, 168, 1, 177);

char mdnsName[] = "webserver3"; // the MDNS name that the board will respond to
// Note that the actual MDNS name will have '.local' after
// the name above, so "webserver3" will be accessible on
// the MDNS name "webserver3.local".

// Create a MDNS responder to listen and respond to MDNS name requests.
EthernetMDNSResponder mdnsResponder;


EthernetServer server(80);

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  
  Ethernet.begin(mac);   // use DHCP
  server.begin();

  // print your shield's IP address:
  IPAddress ip = Ethernet.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // Setup the MDNS responder to listen to the configured name.

  if (!mdnsResponder.begin(mdnsName)) {
    Serial.println("Failed to start MDNS responder!");
    while(1);
  }

  

  Serial.print("Server listening at http://");
  Serial.print(mdnsName);
  Serial.println(".local/");
}


void loop() {
  // Call the update() function on the MDNS responder every loop iteration to
  // make sure it can detect and respond to name requests.
  mdnsResponder.poll();

  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          // output the value of each analog input pin
          for (int analogChannel = 0; analogChannel < 6; analogChannel++) {
            int sensorReading = analogRead(analogChannel);
            client.print("analog input ");
            client.print(analogChannel);
            client.print(" is ");
            client.print(sensorReading);
            client.println("<br />");
          }
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);

    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}


