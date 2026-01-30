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
#include "src/display.hpp"

//declare the radio
RF24 radio(9, 10); //entered as CE pin, CSN pin
const uint64_t address = 0x4E4F444531; // "NODE1" in hex

//make a value to store the weight
double weight = 1.0;

//declare the small lcd object
smallDisplay testDisplay(0x27,"Test Display",&weight, "lbs");

//arduino setup
void setup() {
    Wire.begin();
    //set the serial and declare the scanner active
    Serial.begin(9600);
    Serial.println("Beginning setup");
    //initialize the LCD's
    testDisplay.initializeDisplay();
    Serial.println("Display ready");
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
    radio.setChannel(76);
    radio.setAutoAck(true);
    radio.setRetries(5, 15); // delay, count
    radio.enableDynamicPayloads(); //allow dynamic payloads
    radio.setPALevel(RF24_PA_LOW);
    radio.setDataRate(RF24_250KBPS);
    radio.openReadingPipe(1, address);
    radio.startListening();
    Serial.println("Radio Setup");
}


void loop() {
    //update the test display
    Serial.println("----| loopTick |----");
    Serial.println(radio.available());
    if (radio.available()) {
        float receivedValue;
        radio.read(&receivedValue, sizeof(receivedValue));
        Serial.println(receivedValue);
        weight = (double)receivedValue;
        testDisplay.updateDisplay();
    } else {
        testDisplay.updateDisplay(true, "No Signal");
    }
    //set loop interval to 1 seconds
    delay(1000);
}