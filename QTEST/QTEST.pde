/**

 */


import processing.serial.*;

Serial myPort;      // The serial port
int whichKey = -1;  // Variable to hold keystoke values
int inByte = -1;    // Incoming serial data

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
 

  text("Last Received: " + inBuffer, 10, 130);
  text("Last Sent: " + whichKey, 10, 100);
}

void serialEvent(Serial myPort) {
  //inByte = myPort.read();
   while (myPort.available() > 0) {
    String inBuffer = myPort.readString();   
    if (inBuffer != null) {
      println(inBuffer);
    }
  }

}

void keyPressed() {
  // Send the keystroke out:
  myPort.write(key);
  whichKey = key;
}
