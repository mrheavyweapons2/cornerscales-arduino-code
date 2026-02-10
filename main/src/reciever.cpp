/**
 * @file reciever.cpp
 * @author Jeremiah Nairn
 * @ingroup main/src
 *
 * @brief Implementation file for reciever.h, go there if you are looking for
 * information regarding the functionality of the code here
 */

//include the main header file
#include "reciever.h"

reciever::reciever(RF24& radio, uint64_t address, smallDisplay display)
    : radio(radio), address(address), display(display), value(0.0) {}

//function to initialize the pipe and display
void reciever::initialize() {
    radio.openReadingPipe(1, address);
    display.initializeDisplay();
}

//function to update the reciever (should be in the loop)
void reciever::update() {
    if (radio.available()) {
        radio.read(&value, sizeof(value));
        display.updateDisplay(value);
    } else display.updateDisplay(true, "No Signal");
}

double reciever::getValue() {
    return value;
}