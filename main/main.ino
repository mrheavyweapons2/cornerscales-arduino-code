/**
 * @file main.ino
 * @author Jeremiah Nairn and Nadia Faruqui-Gauto
 * @ingroup main/include
 *
 * @brief This program is designed to be used with an Arduino Uno R3, and takes
 * information from 4 cornerweights, and outputs said information on 5 LCD displays.
 */

//neccesary includes
#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h> //display library
#include <SPI.h>
#include <RF24.h> //radio library

//include headers
#include "src/display.h"

//declare the radio
RF24 radio(9, 10); //entered as CE pin, CSN pin

//declare the addresses for the pipes
const uint64_t address1 = 0x4E4F444531; // "NODE1" in hex
const uint64_t address2 = 0x4E4F444532; // "NODE2" in hex
const uint64_t address3 = 0x4E4F444533; // "NODE3" in hex
const uint64_t address4 = 0x4E4F444534; // "NODE4" in hex


//declare the small lcd object
smallDisplay displayLF(0x27,"Left Front",&weight, "lbs");

//declare the reciever objects
reciever recieverLF(radio, address1, displayLF);

//arduino setup
void setup() {
    Wire.begin();
    //set the serial and declare the scanner active
    Serial.begin(9600);
    Serial.println("Beginning setup");
    //making sure the CSN pin is configured correctly
    pinMode(10, OUTPUT);
    digitalWrite(10, HIGH);
    //setup the radio
    radio.begin();
    //check if the radio is connected
    if (!radio.isChipConnected()) {
        Serial.println("NRF24 NOT DETECTED");
        while (1);
    }
    //configure the radio
    radio.setChannel(76);
    radio.setAutoAck(true);
    radio.setRetries(5, 15); // delay, count
    radio.enableDynamicPayloads(); //allow dynamic payloads
    radio.setPALevel(RF24_PA_LOW);
    radio.setDataRate(RF24_250KBPS);
    radio.openReadingPipe(1, address);
    radio.startListening();
    Serial.println("Radio Setup");

    //initialize recievers and displays
    recieverLF.initialize();
    Serial.println("Recievers and Displays Initialized");
}


void loop() {
    //update the recievers and displays
    recieverLF.update();
    //set loop interval to 1 seconds
    delay(1000);
}