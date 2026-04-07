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
#include "HX711.h" //cornerweight sensor library
HX711 scale;
#include <SPI.h>
#include <RF24.h> //radio library

//declare the radio
RF24 radio(9, 10);
const uint64_t address = 0x12; // "NODE3" in hex

//declare wires for the cornerweight
#define DT_PIN_FR 7
#define SCK_PIN_FR 8

//make a value to store the weight
float weight = 1.0f;

//calibration value
const double CALBVALUE = -9120.0;
const double WEIGHTOFFSET = 1.75;

//arduino setup
void setup() {
    //set the serial and declare the scanner active
    Serial.begin(9600);
    Serial.println("Beginning setup");
    //setup the scales
    scale.begin(DT_PIN_FR, SCK_PIN_FR);
    scale.set_scale(CALBVALUE); //calibrate the scale
    scale.tare(); //reset zero point
    Serial.println("HX711 ready");
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
    radio.openWritingPipe(address);
    radio.stopListening();
    Serial.println("Radio Initialized");
}

void loop() {
    Serial.println("----| loopTick |----");
    //hx711 test code
    if (scale.is_ready()) {
        long raw = scale.read();
        weight = (scale.get_units(10))-WEIGHTOFFSET;//average of 10 readings
        Serial.println(weight);
    } else {
        Serial.println("HX711 not ready");
    }
    //send the weight via radio
    bool success = radio.write(&weight, sizeof(weight));
    if (success) {
        Serial.println("Sent");
    } else {
        Serial.println("Send failed");
    }
    //set loop interval to .3 seconds
    delay(300);
}