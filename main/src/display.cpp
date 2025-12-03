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
ledFrame::ledFrame(uint8_t lcdAddress) : lcdAddress(lcdAddress), lcdObject(lcdAddress, 16, 2) {}
//function to initialize the LCD
void ledFrame::initializeDisplay() {
    //initialize the object here instead of in main
    lcdObject.init();
    lcdObject.backlight();
}

//small display stuff

//constructor
smallDisplay::smallDisplay(uint8_t lcdAddress, const char* name, double* value, const char* unit) : 
                            ledFrame(lcdAddress), name(name), value(value), unit(unit) {}
//function to update the display
void smallDisplay::updateDisplay() {
    lcdObject.clear();
    lcdObject.setCursor(0, 0);
    lcdObject.print(name);
    lcdObject.setCursor(0, 1);
    lcdObject.print(*value);
    lcdObject.print(" ");
    lcdObject.print(unit);
}

//master display stuff

//constructor
masterDisplay::masterDisplay(uint8_t lcdAddress) : 
                            ledFrame(lcdAddress) {}