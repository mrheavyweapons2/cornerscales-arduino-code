/**
 * @file main.hpp
 * @author Jeremiah Nairn and Nadia Faruqui-Gauto
 * @ingroup main/include
 *
 * @brief This program is designed to be used with an Arduino Uno R3, and takes
 * information from 4 cornerweights, and outputs said information on 5 LCD displays.
 */

#include <Arduino.h>
#include "src/display.hpp"

//neccesary includes
#include "HX711.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//declare the displays
//LiquidCrystal_I2C lcd_master(0x27, 20, 4); //master display (placed in the middle)

int hello = 1;

//declare the small lcd object
LiquidCrystal_I2C lcdTest(0x27,16,2);
smallDisplay testDisplay(lcdTest,"bleh",hello);

//arduino setup
void setup() {
    Wire.begin();
    //set the serial and declare the scanner active
    Serial.begin(9600);
    //initialize the LCD's
    testDisplay.initializeDisplay();
}


void loop() {
    //code
    hello +=1;
    testDisplay.updateDisplay();
    //set loop interval to 2 seconds
    delay(2000);
}