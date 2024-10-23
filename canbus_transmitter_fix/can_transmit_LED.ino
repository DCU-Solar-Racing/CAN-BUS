#include <SPI.h>
#include "mcp2515_can.h"

#ifdef ARDUINO_SAMD_VARIANT_COMPLIANCE
    #define SERIAL SerialUSB
#else
    #define SERIAL Serial
#endif


const int SPI_CS_PIN = 9;
mcp2515_can CAN(SPI_CS_PIN); // Set CS pin

void setup() {
  pinMode(8,INPUT);
  pinMode (0, INPUT); 
}

unsigned char mainon[8] = {0, 0, 0, 0, 0, 0, 0, 3}; 
unsigned char gear[8] = {6, 4, 6, 4, 0, 0, 0, 9};

void loop() {

if (digitalRead(8) == HIGH){
    CAN.sendMsgBuf(0x00, 0, 8, mainon);
    delay(100);                       // send data per 100ms
    }



if (digitalRead(0) == HIGH){
    CAN.sendMsgBuf(0x00, 0, 8, gear);
    delay(100);                       // send data per 100ms

}


}