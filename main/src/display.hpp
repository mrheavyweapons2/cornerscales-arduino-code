#ifndef DISPLAY_HPP
#define DISPLAY_HPP

/**
 * @file display.hpp
 * @author Jeremiah Nairn
 * @ingroup main/include
 *
 * @brief Contains headers that are used to simplify the use of the LCD displays.
 * Takes pointer information and constantly updates it when needed.
 */

//header for the LCD stuff and others
#include <LiquidCrystal_I2C.h>

/**
 * @class ledFrame
 * @brief Small superclass that contains variables and maybe
 * functions (if we really need that) that are the same between
 * both classes
 */

class ledFrame {
protected:
    LiquidCrystal_I2C& lcdObject;

    ledFrame(LiquidCrystal_I2C& lcd);

public:
    //function to initialize the display
    void initializeDisplay();
};


/**
 * @class smallDisplay
 * @brief Class that handles all of the main logic regarding the 
 * smaller displays. There are four total, so the goal here is to make it simpler
 * to operate the displays from a class rather than the main program.
 */
class smallDisplay : public ledFrame {
private:
    //private pointers that store the name and value of the display
    char* name;
    double* value;
public:
    //function to update the display (should be put in the loop)
    void updateDisplay();
    //constructor
    smallDisplay(LiquidCrystal_I2C& lcd, char* name, double* value);
};

/**
 * @class masterDisplay
 * @brief Class that handles the logic for the master display the goal here is to pass all
 * the logic as pointers in here, and the class handles the work instead of the main function
 * (to make the main function look simpler, obviously)
 */
class masterDisplay : public ledFrame {
public:
    //constructor
    masterDisplay(LiquidCrystal_I2C& lcd);
};

#endif //DISPLAY_HPP