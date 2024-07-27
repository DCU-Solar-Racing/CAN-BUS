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

    SERIAL.begin(115200);
    while(!Serial){};

    while (CAN_OK != CAN.begin(CAN_500KBPS)) {             // init can bus : baudrate = 500k
        SERIAL.println("CAN BUS Shield init fail");
        SERIAL.println(" Init CAN BUS Shield again");
        delay(100);
    }
    SERIAL.println("CAN BUS Shield init ok!");
}

unsigned char reg[8] = {6, 4, 6, 4, 0, 0, 0, 9};
unsigned char noreg[8] = {4, 6, 4, 6, 0, 0, 0, 1};
void loop() {

if (digitalRead(8) == HIGH){
    CAN.sendMsgBuf(0x00, 0, 8, reg);
    delay(100);                       // send data per 100ms
    SERIAL.println("Reg Braking ON!");
    }

if (digitalRead(8) == LOW){
    CAN.sendMsgBuf(0x00, 0, 8, noreg);
    delay(100);                       // send data per 100ms
    SERIAL.println("No Reg Braking!");
}

}