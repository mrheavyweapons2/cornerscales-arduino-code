/**
 * @file display.cpp
 * @author Jeremiah Nairn
 * @ingroup main/src
 *
 * @brief Implementation file for display.hpp, go there if you are looking for
 * information regarding the functionality of the code here
 */

//main header file
#include "display.hpp"
//header for the actual LCD stuff
#include <LiquidCrystal_I2C.h>

//LED frame stuff

//constructor
ledFrame::ledFrame(LiquidCrystal_I2C& lcd) : lcdObject(lcd) {}
//function to initialize the LCD
void ledFrame::initializeDisplay() {
    //initialize the object here instead of in main
    lcdObject.init();
    lcdObject.backlight();
}

//small display stuff

//constructor
smallDisplay::smallDisplay(LiquidCrystal_I2C& lcd, char* name, double* value) : 
                            ledFrame(lcd), name(name), value(value) {}
//function to update the display
void smallDisplay::updateDisplay() {
    //code
}

//master display stuff

//constructor
masterDisplay::masterDisplay(LiquidCrystal_I2C& lcd) : 
                            ledFrame(lcd) {}