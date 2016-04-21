// arduino end
char val; // Data received from the serial port
int ledPin = 13; // Set the pin to digital I/O 13
boolean ledState = LOW; //to toggle our LED
// BMP180 stuff
#include <SFE_BMP180.h>
#include <Wire.h>

// You will need to create an SFE_BMP180 object, here called "pressure":

SFE_BMP180 pressure;

#define ALTITUDE 0.0 // Altitude in meters
/*
Hardware connections:

- (GND) to GND
+ (VDD) to 3.3V

Any Arduino pins labeled:  SDA  SCL
Nano,                       A4   A5
*/

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
 // BMP180
  if (pressure.begin())
    Serial.println("BMP180 init success");
  else
  {
    // Oops, something went wrong, this is usually a connection problem,
    // see the comments at the top of this sketch for the proper connections.

    Serial.println("BMP180 init fail\n\n");
    while(1); // Pause forever.
  }
  //dht11
   dht.begin();
}

void loop()
{
  char status;
  double T,P,p0,a;
  
  if (Serial.available() > 0) { // If data is available to read,
    val = Serial.read(); // read it and store it in val

    if(val == 'Q') //if we get a Q
    {
      // read indicator 
       ledState = !ledState; //flip the ledState
       digitalWrite(ledPin, ledState);
  

  status = pressure.startTemperature();
  if (status != 0)
  {
    // Wait for the measurement to complete:
    delay(status);

    // Retrieve the completed temperature measurement:
    // Note that the measurement is stored in the variable T.
    // Function returns 1 if successful, 0 if failure.

    status = pressure.getTemperature(T);
    if (status != 0)
    {
      // Print out the measurement:
      Serial.print(T,2);
      Serial.print("C ");
   
      // Start a pressure measurement:
      // The parameter is the oversampling setting, from 0 to 3 (highest res, longest wait).
      // If request is successful, the number of ms to wait is returned.
      // If request is unsuccessful, 0 is returned.

      status = pressure.startPressure(3);
      if (status != 0)
      {
        // Wait for the measurement to complete:
        delay(status);

        status = pressure.getPressure(P,T);
        if (status != 0)
        {
          // Print out the measurement:
          Serial.print(P,2);
          Serial.print("mb ");

        
        }
        else Serial.println("error retrieving pressure measurement\n");
      }
      else Serial.println("error starting pressure measurement\n");
    }
    else Serial.println("error retrieving temperature measurement\n");
  }
  else Serial.println("error starting temperature measurement\n");
  
  
 
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
