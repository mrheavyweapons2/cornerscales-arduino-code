/**
 * @file display.hpp
 * @author Jeremiah Nairn
 * @ingroup main/include
 *
 * @brief Contains headers that are used to simplify the use of the LCD displays.
 * Takes pointer information and constantly updates it when needed.
 */

#ifndef DISPLAY_HPP
#define DISPLAY_HPP

//header for the LCD stuff
#include <LiquidCrystal_I2C.h>

/**
 * @class smallDisplay
 * @brief Class that handles all of the main logic regarding the 
 * smaller displays. There are four total, so the goal here is to make it simpler
 * to operate the displays from a class rather than the main program.
 */
class smallDisplay{

};

/**
 * @class masterDisplay
 * @brief Class that handles the logic for the master display the goal here is to pass all
 * the logic as pointers in here, and the class handles the work instead of the main function
 * (to make the main function look simpler, obviously)
 */
class masterDisplay{

};