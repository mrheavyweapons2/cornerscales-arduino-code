/**
 * @file main.ino
 * @author Jeremiah Nairn
 * @ingroup main/include
 *
 * @brief This program is designed to be used with an Arduino Uno R3, and takes
 * information from 4 cornerweights, and outputs said information on 5 LCD displays.
 */


//neccesary non-project header includes
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

const uint64_t base = 0x4E4F444500; // "NODE\0"

//declare the addresses for the pipes
const uint64_t address1 = base | 0x01;
const uint64_t address2 = base | 0x02;
const uint64_t address3 = base | 0x03; 
const uint64_t address4 = base | 0x04; 

//declare weight variables
double weightLF = 0.0;
double weightRF = 0.0;
double weightLR = 0.0;
double weightRR = 0.0;

//declare the pipes
const int pipe0 = 0;
const int pipe1 = 1;
const int pipe2 = 2;
const int pipe3 = 3;

//declare the small lcd objects
smallDisplay displayLF(0x26,"Left Front",&weightLF, "lbs");
smallDisplay displayRF(0x23,"Right Front",&weightRF, "lbs");
smallDisplay displayLR(0x25,"Left Rear", &weightLR, "lbs");
smallDisplay displayRR(0x22,"Right Rear", &weightRR, "lbs");

//initialize the master display manually
LiquidCrystal_I2C masterDisplay(0x27, 20, 4);


//declare the reciever objects
reciever recieverLF(radio, pipe0, address1, weightLF, displayLF);
reciever recieverRF(radio, pipe1, address2, weightRF, displayRF);
reciever recieverLR(radio, pipe2, address3, weightLR, displayLR);
reciever recieverRR(radio, pipe3, address4, weightRR, displayRR);

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
    //looptick
    Serial.println("---| loopTick |---");
    //get the pipenumber and find the recieved value
    uint8_t pipeNum;
    float receivedValue = 0;
    // read all pending packets
    while (radio.available(&pipeNum)) {
        radio.read(&receivedValue, sizeof(receivedValue));
        //run through a switch statement to look for the packets
        switch (pipeNum) {
            case pipe0: weightLF = receivedValue; break;
            case pipe1: weightRF = receivedValue; break;
            case pipe2: weightLR = receivedValue; break;
            case pipe3: weightRR = receivedValue; break;
        }
    }
    // update all displays
    displayLF.updateDisplay();
    displayRF.updateDisplay();
    displayLR.updateDisplay();
    displayRR.updateDisplay();

    
    // update master display
    masterDisplay.clear();
    masterDisplay.setCursor(0, 0);
    masterDisplay.print("TW: ");
    masterDisplay.print(weightLF + weightRF + weightLR + weightRR);
    masterDisplay.print(" lbs");

    double totalFront = weightLF + weightRF;
    double totalBack = weightLR + weightRR;
    masterDisplay.setCursor(0, 1);
    masterDisplay.print("F: ");
    masterDisplay.print(totalFront, 2);
    masterDisplay.print(", B: ");
    masterDisplay.print(totalBack, 2);

    double totalLeft = weightLF + weightLR;
    double totalRight = weightRF + weightRR;
    masterDisplay.setCursor(0, 2);
    masterDisplay.print("L: ");
    masterDisplay.print(totalLeft, 2);
    masterDisplay.print(", R: ");
    masterDisplay.print(totalRight, 2);

    delay(500);
}