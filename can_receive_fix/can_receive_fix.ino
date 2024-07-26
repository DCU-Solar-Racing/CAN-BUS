#include <SPI.h>
#include "mcp2515_can.h"

/*SAMD core*/
#ifdef ARDUINO_SAMD_VARIANT_COMPLIANCE
    #define SERIAL SerialUSB
#else
    #define SERIAL Serial
#endif

const int SPI_CS_PIN = 9;
mcp2515_can CAN(SPI_CS_PIN); // Set CS pin

void setup() {
    SERIAL.begin(115200);
    while (!Serial) {};

    while (CAN_OK != CAN.begin(CAN_500KBPS)) { // Init CAN bus: baudrate = 500k
        SERIAL.println("CAN BUS Shield init fail");
        SERIAL.println(" Init CAN BUS Shield again");
        delay(100);
    }
    SERIAL.println("CAN BUS Shield init ok!");
}

void loop() {
    unsigned char len = 0;
    unsigned char buf[8];

    if (CAN_MSGAVAIL == CAN.checkReceive()) { // Check if data is available
        CAN.readMsgBuf(&len, buf); // Read data: len = data length, buf = data byte(s)
        unsigned long canId = CAN.getCanId(); // Get CAN ID

        SERIAL.print("CAN ID: ");
        SERIAL.println(canId, HEX);
        SERIAL.print("Data: ");
        
        for (int i = 0; i < len; i++) { // Print each byte of the data
            SERIAL.print(buf[i], HEX);
            SERIAL.print(" ");
        }
        SERIAL.println();
    }
    delay(1000); // Add a delay to avoid flooding the serial output
}

