// Basic Bluetooth test sketch 5a for the Arduino Mega. 
// AT mode using button switch
// HC-05 with EN pin and button switch
//
//  Pins
//  BT VCC to Arduino 5V out. Disconnect before running the sketch
//  BT GND to Arduino GND
//  BT RX (through a voltage divider) to Arduino TX1 (pin 10)
//  BT TX  to Arduino RX1 (no need voltage divider)   (pin 11)
//
//

/*-----( Import needed libraries )-----*/
#include <SoftwareSerial.h>  

char serialByte = '0';

#define HC_05_RXD_ARDUINO_TXD 10
#define HC_05_TXD_ARDUINO_RXD 11

SoftwareSerial BTSerial(HC_05_TXD_ARDUINO_RXD, HC_05_RXD_ARDUINO_TXD); // RX | TX
 
void setup() 
{ 
    // communication with the host computer
    Serial.begin(9600);  
 
    // communication with the BT module on BTSerial (pins 10/11
    BTSerial.begin(38400);
}
 
 
void loop() 
{
    // listen for communication from the BT module and then write it to the serial monitor
    if ( BTSerial.available() )   {  Serial.write( BTSerial.read() );  }
 
    // listen for user input and send it to the HC-05
   if ( Serial.available() )   {  BTSerial.write( Serial.read() );  }
}

