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

reciever::reciever(RF24& radio, int pipe, uint64_t address, double& value, smallDisplay& display)
    : radio(radio), pipe(pipe), address(address), value(value), display(display) {}

//function to initialize the pipe and display
void reciever::initialize() {
    radio.openReadingPipe(pipe, address);
    display.initializeDisplay();
}

//function to update the reciever (should be in the loop)
void reciever::update() {
    //read the value
    float receivedValue = 0;
    radio.read(&receivedValue, sizeof(receivedValue));
    //update the value and display
    value = receivedValue;
    display.updateDisplay();
}

double reciever::getValue() const {return value;}