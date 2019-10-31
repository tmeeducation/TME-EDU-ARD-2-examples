/*  TME EDUCATION
 *  LogoTmeEdu
 *  v0.2.0
 *  -------------
 *  It is a program showing the TME EDUCATION Logo
 */ 
#define PROJECT_NAME "LogoTmeEdu"
#define VERSION "v0.2.0"

#include "includes.h"
#include "graphics/logoTmeEducation.h"
////////CONSTANTS////////
//In this section, all constants resulting from the prototype board design are set

////////MODIFIERS////////
//In this section there are constants whose modification will affect the operation of our plate

////////DECLARATIONS/////
//This section prepares variables that are responsible for the individual components on the board
hd44780_I2Cexp lcd(0x20, I2Cexp_MCP23008, 7, 6, 5, 4, 3, 2, 1, HIGH);
Adafruit_SSD1306 display(0);

void setup(){
  lcd.begin(16, 2);
  intro(lcd);
  
  display.begin(0x2, 0x3C, false);
  display.clearDisplay();
  display.drawBitmap(0, 0, logoTmeEducation, 128, 64, 1);
  display.display();
}

void loop(){  
}
