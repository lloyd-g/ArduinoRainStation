// arduino end
char val; // Data received from the serial port
int ledPin = 13; // Set the pin to digital I/O 13
boolean ledState = LOW; //to toggle our LED

// DHT11 stuff
#include "DHT.h"
#define DHTPIN A0    // what pin we're connected to
#define DHTTYPE DHT11   // DHT 11 
// Connect pin 1 (on the left) of the sensor to +5V
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor
DHT dht(DHTPIN, DHTTYPE);

void setup() 
{
  pinMode(ledPin, OUTPUT); // Set pin as OUTPUT
  //initialize serial communications at a 115200 baud rate
  Serial.begin(115200);
//dht11
   dht.begin();
}

void loop()
{
  if (Serial.available() > 0) { // If data is available to read,
    val = Serial.read(); // read it and store it in val

    if(val == 'Q') //if we get a Q
    {
       ledState = !ledState; //flip the ledState
       digitalWrite(ledPin, ledState);
 
       // Reading temperature or humidity takes about 250 milliseconds!
       // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
       float h = dht.readHumidity();
       float t = dht.readTemperature();
       // check if returns are valid, if they are NaN (not a number) then something went wrong!
       if (isnan(t) || isnan(h)) {
     		Serial.println("Failed to read");
       } else {
     		Serial.print(h);
    		Serial.print("RH"); 
    		Serial.print(" "); 
    		Serial.print(t);
    		Serial.println("C");
       }
    }
 }
}
