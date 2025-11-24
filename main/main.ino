/**
 * @file main.hpp
 * @author Jeremiah Nairn and Nadia Faruqui-Gauto
 * @ingroup main/include
 *
 * @brief This program is designed to be used with an Arduino Uno R3, and takes
 * information from 4 cornerweights, and outputs said information on 5 LCD displays.
 */


//neccesary includes
#include "HX711.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "include/display.h"

//declare the displays
//LiquidCrystal_I2C lcd_master(0x27, 20, 4); //master display (placed in the middle)
LiquidCrystal_I2C lcd_master(0x27,16,2); //smaller display


//arduino setup
void setup() {
    Wire.begin();
    //set the serial and declare the scanner active
    Serial.begin(9600);
    //initialize the LCD's
    lcd_master.init();
    lcd_master.backlight();
}

int hello = 1;
void loop() {
    //code
    hello +=1;
    lcd_master.setCursor(1,0);
    lcd_master.print(hello);
    //set loop interval to 2 seconds
    delay(2000);
    lcd_master.clear();
}