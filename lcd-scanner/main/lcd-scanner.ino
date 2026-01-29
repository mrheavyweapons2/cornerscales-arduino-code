//includes
#include <Wire.h>

void setup() {
    Wire.begin();
    //set the serial and declare the scanner active
    Serial.begin(9600);
    Serial.println("\nScanner Active");
}

void loop() {
    //declare variables
    byte error, address; //devices error and address
    int Devices; //the amount of devices connected
    //tell the user its testing
    Serial.println("Scanning...");
    Devices = 0;
    for(address = 1; address < 127; address++ ) {
        Wire.beginTransmission(address);
        error = Wire.endTransmission();
        //if there is no error, that is the correct address
        if (error == 0) {
            Serial.print("I2C device found at address 0x");
            if (address<16)
            Serial.print("0");
            Serial.print(address,HEX);
            Serial.println("  !");
            Devices++;
        //if there is an error, let the user know
        } else if (error==4) {
            Serial.print("Unknown error at address 0x");
            if (address<16)
            Serial.print("0");
            Serial.println(address,HEX);
        }
    }
    //alert the user if there is no I2C devices
    if (Devices == 0) Serial.println("No I2C devices found\n");
    else Serial.println("done\n");
    //wait 5 seconds
    delay(5000);          
}
