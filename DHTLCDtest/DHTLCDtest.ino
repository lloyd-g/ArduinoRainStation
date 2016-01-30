/*
 LiquidCrystal Library - Hobbytronics
 was used as a start point
 see this tutorial
 http://www.hobbytronics.co.uk/arduino-tutorial10-lcd
 
 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the 
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.
 
 This sketch prints "Hobbytronics" to the LCD
 and shows the time.
 This sketch is based on the Arduino sample sketch at 
 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 but with modifications  to the LCD contrast to make it 
 adjustable via software
 
  The circuit:
 * LCD RS pin to digital pin 7
 * LCD Enable pin to digital pin 6
 * LCD R/W pin to Ground 
 * LCD VO pin (pin 3) to PWM pin 9
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 
 */
#include "DHT.h"

#define DHTPIN A0    // what pin we're connected to

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11 
//#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

DHT dht(DHTPIN, DHTTYPE);

// include the library code:
#include <LiquidCrystal.h>
 
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
 
void setup() {
  // declare pin 9 to be an output:
  pinMode(9, OUTPUT);  
  analogWrite(9, 45); // had to change for my module from 50 to 90  
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  //lcd.print("test count");
   dht.begin();
}
 
void loop() {
   // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // check if returns are valid, if they are NaN (not a number) then something went wrong!
  if (isnan(t) || isnan(h)) {
    lcd.setCursor(0, 0); //top line
    lcd.println("Failed to read");
  } else {
    lcd.setCursor(0, 0); //top line need to fit 16 char
    lcd.print(h);
    lcd.print("RH"); 
    lcd.print(" "); 
    lcd.print(t);
    lcd.println("C");
  }
 
}

