#ifndef RECIEVER_H
#define RECIEVER_H

/**
 * @file reciever.h
 * @author Jeremiah Nairn
 * @ingroup main/src
 *
 * @brief Contains an object for handling the recieving of data from the
 * RF24L01+ module, and its 4 associated pipes.
 */

//include necessary libraries
#include <Arduino.h>
#include "display.h"
#include <RF24.h>

//declare the object
class reciever {
    private:
        RF24& radio; //reference to the RF24 object
        int pipe;
        uint64_t address;
        double& value;
        smallDisplay display;
    
    public:
        //constructor
        reciever(RF24& radio, int pipe,uint64_t address, double& value, smallDisplay display);

        //function to initialize the pipe and display
        void initialize();

        //function to update the reciever (should be in the loop)
        void update();

        //function to get the value of the reciever
        double getValue();
};

#endif
