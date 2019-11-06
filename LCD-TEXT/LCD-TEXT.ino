/*  TME EDUCATION
 *  LCDText
 *  v0.1.0
 *  -------------
 *  How to print text on LCD display
 */ 
#define PROJECT_NAME "LCDText"
#define VERSION "v0.1.0"

#include "includes.h"
////////CONSTANTS////////
//In this section, all constants resulting from the prototype board design are set

////////MODIFIERS////////
//In this section there are constants whose modification will affect the operation of our plate


////////DECLARATIONS////////
//This section prepares variables that are responsible for the individual components on the board

//The line above told the program how we connect our screen to the board.
hd44780_I2Cexp lcd(0x20, I2Cexp_MCP23008, 7, 6, 5, 4, 3, 2, 1, HIGH);

void setup(){
  //Here we start work with our program. First, we have to give the program what dimensions our display has. 
  //That is, how many characters he can display. if you turn on your board you can see small rectangles on the display. 
  //This is the place for our signs.
  lcd.begin(16, 2);
  
  intro(lcd);

  //Yes. It's so simple. To write something on the display simply enter the name of the display, 
  //and then use the appropriate command to display the text
  lcd.print("Hello TME");

  //Now, guess what happens after you uncomment this code.
//  lcd.setCursor(3, 1);
//  lcd.print("Here we are");

  //Finally, look at the intro.h file. This file is responsible for the text you see immediately after starting the program.
  //I left some useful information for you there.
}

void loop(){
  
}
