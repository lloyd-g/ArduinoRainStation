/*
serves data from arduino as HTTP front end
 
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
const char *ssid = "Data";
const char *password = "";

ESP8266WebServer server(80);
int inByte = 0;         // incoming serial byte
String inData;
int P2State = 0; 
int P0State = 0;
int P12State = 0;
int P13State = 0;
int P14State = 0;
int P15State = 0;
int P16State = 0;
int sensorPin = A0;    // select the input pin
int sensorValue = 0;  // variable to store the value coming from the sensor
/* Just a little test message.  Go to http://192.168.4.1 in a web browser
 * connected to this access point to see it.
 */
void handleRoot() {
	char temp[400];
	P2State = digitalRead(2);
	P0State = digitalRead(0);
	P12State = digitalRead(12);
	P13State = digitalRead(13);
	P14State = digitalRead(14);
	P15State = digitalRead(15);
	P16State = digitalRead(16);
  sensorValue = analogRead(sensorPin);
  // RQ sent to Arduino to ask for data.
	Serial.print("Q");
	// add test to respont to Arduino data.
	inData="";
	while (Serial.available() == 0);
int h=Serial.available();  // data length
// read to string byte at time
for (int i=0;i<h;i++){
              inData += (char)Serial.read();
          }

	// and put on page
	snprintf ( temp, 400,

"<html>\
  <head>\
    <meta http-equiv='refresh' content='10'/>\
    <title>station</title>\
  </head>\
  <body>\
    <h1>Data area</h1>\
    <h2>P2: %02d</h2>\
    <h2>P0: %02d</h2>\
    <h2>P12: %02d</h2>\
    <h2>P13: %02d</h2>\
    <h2>P14: %02d</h2>\
    <h2>P15: %02d</h2>\
    <h2>P16: %02d</h2>\
<h2>sensor: %04d</h2>\
<h2>data: %s</h2>\
  </body>\
</html>", 
P2State, P0State, P12State, P13State, P14State, P15State, P16State, sensorValue, inData

			
	);
	server.send ( 200, "text/html", temp );
	
}

void bouncepage() {
	char temp[400];
	snprintf ( temp, 400,

"<html><head><meta http-equiv='refresh' content=\"0;url=/ \"/><title>station</title>\ 
  </head>\
  <body>\
    <h1>OK!</h1>\
   <a href=\"/\">bach</a>\       
  </body>\
</html>"
);
	server.send ( 200, "text/html", temp );
}


void setup() {
    // prepare GPIO2
  pinMode(2, OUTPUT);
  digitalWrite(2, 0);
	delay(1000);
	Serial.begin(115200);
	Serial.println();
	Serial.print("CONFIG.");
	/* You can remove the password parameter if you want the AP to be open. */
	WiFi.softAP(ssid, password);

	IPAddress myIP = WiFi.softAPIP();
	Serial.print("AP IP address: ");
	Serial.println(myIP);
	server.on("/", handleRoot);
	server.begin();
	Serial.println("HTTP server started");
}

void loop() {
	server.handleClient();
}


