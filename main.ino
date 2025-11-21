/**
CODINGSTANDARDS:
    -Use camelCase
NOTES:
    -n/a
CONTRIBUTORS:
    -Jeremiah Nairn
    -Nadia Faruqui-Gauto
 */

//neccesary includes
#include "HX711.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//declare the displays
LiquidCrystal_I2C lcd_master(0x27, 20, 4); //master display (placed in the middle)