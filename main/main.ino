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
#include "HX711.h"
HX711 scale;
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//include headers
#include "src/display.hpp"

//declare specific wires
#define DT_PIN_FR 9
#define SCK_PIN_FR 8


//declare the displays

double weight = 1.0;

//declare the small lcd object
smallDisplay testDisplay(0x27,"Test Display",&weight, "lbs");

//arduino setup
void setup() {
    Serial.println("Beginning setup");
    Wire.begin();
    //set the serial and declare the scanner active
    Serial.begin(9600);
    //initialize the LCD's
    testDisplay.initializeDisplay();
    Serial.println("Display ready");
    //setup the scales
    scale.begin(DT_PIN_FR, SCK_PIN_FR);
    scale.set_scale(2280.0); //calibrate the scale
    scale.tare(); //reset zero point
    Serial.println("HX711 ready");
}


void loop() {
    //hx711 test code
    if (scale.is_ready()) {
        long raw = scale.read();
        weight = scale.get_units(10);//average of 10 readings

    } else {
        Serial.println("HX711 not ready");
    }
    //update the test display
    testDisplay.updateDisplay();
    //set loop interval to .2 seconds
    delay(200);
}