/*

 
 */

/* Create a WiFi access point and provide a web server on it. */
/* you will need Arduino IDE for ESP8266 at https://github.com/esp8266/Arduino
to up load into a module containing the ESP8266 wifi chip only tested on ESP 01
the point is to have it as a web gate way to an Arduino collecting data from transducers
*/
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

/* Set these to your desired credentials. */
const char *ssid = "Weather";
const char *password = "";

ESP8266WebServer server(80);

/* Just a little test message.  Go to http://192.168.4.1 in a web browser
 * connected to this access point to see it.
 */
void handleRoot() {
	// simple message
	//server.send(200, "text/html", "<h1>You are connected</h1>");
	//bigger message form advanced webserver example
		char temp[400];
	int sec = millis() / 1000;
	int min = sec / 60;
	int hr = min / 60;

	snprintf ( temp, 400,

"<html>\
  <head>\
    <meta http-equiv='refresh' content='5'/>\
    <title>station</title>\
    <style>\
      body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
    </style>\
  </head>\
  <body>\
    <h1>Hello from ESP8266!</h1>\
   <a href=\"/on\">on</a>\ 
   <a href=\"/off\">off</a>\     
    <p>Uptime: %02d:%02d:%02d</p>\
  </body>\
</html>",

		hr, min % 60, sec % 60
	);
	server.send ( 200, "text/html", temp );
	
}

void setup() {
	delay(1000);
	Serial.begin(115200);
	Serial.println();
	Serial.print("Configuring access point...");
	/* You can remove the password parameter if you want the AP to be open. */
	WiFi.softAP(ssid, password);

	IPAddress myIP = WiFi.softAPIP();
	Serial.print("AP IP address: ");
	Serial.println(myIP);
	server.on("/", handleRoot);
        server.on ( "/on", []() {
		server.send ( 200, "text/plain", "this is on" );
	} );
        server.on ( "/off", []() {
		server.send ( 200, "text/plain", "this is off" );
	} );
	server.begin();
	Serial.println("HTTP server started");
}

void loop() {
	server.handleClient();
}

