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

const unsigned char expectedBuf[8] = {6, 4, 6, 4, 0, 0, 0, 9};

void setup() {
    pinMode(10, OUTPUT);

    // Remove or comment out the following line to prevent waiting for Serial Monitor
    SERIAL.begin(115200);

    // Initialize CAN bus at 500kbps
    while (CAN_OK != CAN.begin(CAN_500KBPS)) {
        // Use delay instead of SERIAL messages for debugging without Serial Monitor
        delay(100);
    }
}

void loop() {
    unsigned char len = 0;
    unsigned char buf[8];

    if (CAN_MSGAVAIL == CAN.checkReceive()) { // Check if data is available
        CAN.readMsgBuf(&len, buf); // Read data: len = data length, buf = data byte(s)
        unsigned long canId = CAN.getCanId(); // Get CAN ID

        // Optional debugging statements (can be removed if not using Serial Monitor)
        //SERIAL.print("CAN ID: ");
        //SERIAL.println(canId, HEX);
        //SERIAL.print("Data: ");
        //for (int i = 0; i < len; i++) { // Print each byte of the data
        //     SERIAL.print(buf[i], HEX);
        //     SERIAL.print(" ");
        //}
        //SERIAL.println();

        // Check if the received message matches the expected buffer
        bool match = true;
        if (len == 8) {
            for (int i = 0; i < 8; i++) {
                if (buf[i] != expectedBuf[i]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                // Blink the LED if the message matches
                digitalWrite(10, HIGH);  // turn the LED on (HIGH is the voltage level)
                delay(100);              // wait for 100 milliseconds
                digitalWrite(10, LOW);   // turn the LED off by making the voltage LOW
                delay(100); 
            }
        }
    }
}



