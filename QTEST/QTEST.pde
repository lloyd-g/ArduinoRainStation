/**

 */


import processing.serial.*;

Serial myPort;      // The serial port
int whichKey = -1;  // Variable to hold keystoke values
int inByte = -1;    // Incoming serial data
String inBuffer = "";

void setup() {
  size(400, 300);
  // create a font with the third font available to the system:
  PFont myFont = createFont(PFont.list()[2], 14);
  textFont(myFont);

  // List all the available serial ports:
  printArray(Serial.list());

  // is my  ARDUINO USBtty0, so I open Serial.list()[32].
  // Open whatever port is the one you're using. list is show in console
  String portName = Serial.list()[32];
  myPort = new Serial(this, portName, 115200);
  
}

void draw() {
  background(0);
 

  text(inBuffer, 10, 130);
  text("Last Sent: " + whichKey, 10, 10);
}

void serialEvent(Serial myPort) {
  //inByte = myPort.read();
   if(myPort.available() > 0) {
    inBuffer = myPort.readStringUntil(10);  
    if (inBuffer != null) {
      print(inBuffer);
    }
  }

}

void keyPressed() {
  // Send the keystroke out:
  myPort.write(key);
  whichKey = key;
}