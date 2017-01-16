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

#define HC_05_TXD_ARDUINO_RXD 10
#define HC_05_RXD_ARDUINO_TXD 11

#define MIN_RELAY_PIN 2
#define MAX_RELAY_PIN 7

SoftwareSerial BTSerial(HC_05_TXD_ARDUINO_RXD, HC_05_RXD_ARDUINO_TXD); // RX | TX
 
int relayLock;

void setup() 
{ 
    // communication with the host computer
    // debug mode
    //Serial.begin(9600);  

    // initialize to unlocked
    relayLock=0;
    
    pinMode(13, OUTPUT);
 
    // initialize pins for relay
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
    
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);

    // communication with the BT module on BTSerial (pins 10/11
    BTSerial.begin(38400);
}
 
 
void loop() 
{
    int i;
    char c;
    
    // listen for communication from the BT module and then write it to the serial monitor
    if ( BTSerial.available() > 0)   {  
        if (relayLock == 0) {
            relayLock = 1;        
            digitalWrite(13, HIGH);
            c = BTSerial.read(); 
            if  (c == '1') {
              for (i = MIN_RELAY_PIN; i <= MAX_RELAY_PIN; i++) {
                digitalWrite(i, HIGH);
                delay(400);
                digitalWrite(i + 1, HIGH);
                delay(100);
                digitalWrite(i, LOW);
              }              
            } else if (c == '2') {
              for (i = MIN_RELAY_PIN; i <= MAX_RELAY_PIN; i++) {
                digitalWrite(i, HIGH);
                delay(250);
                digitalWrite(i, LOW);
              }
              for (i = MAX_RELAY_PIN; i >= MIN_RELAY_PIN; i--) {
                digitalWrite(i, HIGH);
                delay(500);
                digitalWrite(i, LOW);
              }              
            }
            digitalWrite(13, LOW);
            relayLock = 0;
        }
    }
}

