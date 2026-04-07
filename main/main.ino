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
#include "src/reciever.h"

//declare the radio
RF24 radio(9, 10); //entered as CE pin, CSN pin

//declare the addresses for the pipes
const uint64_t address1 = 0x4E4F444531; // "NODE1" in hex
const uint64_t address2 = 0x11; // "NODE2" in hex
const uint64_t address3 = 0x12; // "NODE3" in hex
const uint64_t address4 = 0x13; // "NODE4" in hex

//declare weight variables
double weightLF = 0.0;
double weightRF = 0.0;
double weightLR = 0.0;
double weightRR = 0.0;

//declare the small lcd objects
smallDisplay displayLF(0x26,"Left Front",&weightLF, "lbs");
smallDisplay displayRF(0x23,"Right Front",&weightRF, "lbs");
smallDisplay displayLR(0x25,"Left Rear", &weightLR, "lbs");
smallDisplay displayRR(0x22,"Right Rear", &weightRR, "lbs");

//initialize the master display manually
LiquidCrystal_I2C masterDisplay(0x27, 20, 4);


//declare the reciever objects
reciever recieverLF(radio, 0, address1, weightLF, displayLF);
reciever recieverRF(radio, 1, address2, weightRF, displayRF);
reciever recieverLR(radio, 2, address3, weightLR, displayLR);
reciever recieverRR(radio, 3, address4, weightRR, displayRR);

//arduino setup
void setup() {
    //wait 1 second
    delay(1000);
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
    radio.startListening();
    Serial.println("Radio Setup");

    //declare the wire for i2c
    Wire.begin();
    //initialize recievers and displays
    recieverLF.initialize();
    recieverRF.initialize();
    recieverLR.initialize();
    recieverRR.initialize();
    //initialize the master display
    masterDisplay.init();
    masterDisplay.backlight();
    Serial.println("Recievers and Displays Initialized");
}


void loop() {
    //run a lifetick
    Serial.println("---| loopTick |---");
    //update the recievers and displays
    recieverLF.update();
    recieverRF.update();
    recieverLR.update();
    recieverRR.update();
    //manually update the master display
    masterDisplay.clear();
    //print the total weight
    masterDisplay.setCursor(0, 0);
    masterDisplay.print("TW: ");
    masterDisplay.print(weightLF + weightRF + weightLR + weightRR);
    masterDisplay.print(" lbs");
    //print the weight distribution from front to back
    double totalFront = weightLF + weightRF;
    double totalBack = weightLR + weightRR;
    masterDisplay.setCursor(0, 1);
    masterDisplay.print("F: ");
    masterDisplay.print(totalFront, 2);
    masterDisplay.print(", B: ");
    masterDisplay.print(totalBack, 2);
    //print the weight distribution from left to right
    double totalLeft = weightLF + weightLR;
    double totalRight = weightRF + weightRR;
    masterDisplay.setCursor(0, 2);
    masterDisplay.print("L: ");
    masterDisplay.print(totalLeft, 2);
    masterDisplay.print(", R: ");
    masterDisplay.print(totalRight, 2);
    //set loop interval to 1 seconds
    delay(1000);
}