/*  TME EDUCATION
 *  Thermometer-Lcd
 *  v0.1.0
 *  -------------
 *  In this program we will use the built-in thermometer to show the ambient temperature.
 */ 
#define PROJECT_NAME "Thermometer-Lcd"
#define VERSION "v0.1.0"

#include "includes.h"
////////CONSTANTS////////
//In this section, all constants resulting from the prototype board design are set
#define THERMOMETER A2

////////MODIFIERS////////
//In this section there are constants whose modification will affect the operation of our plate


////////DECLARATIONS////////
//This section prepares variables that are responsible for the individual components on the board
hd44780_I2Cexp lcd(0x20, I2Cexp_MCP23008, 7, 6, 5, 4, 3, 2, 1, HIGH);

void setup(){
  lcd.begin(16, 2);
  intro(lcd);

  //The thermometer as the loudspeaker is an analog device. 
  //The read value should be scaled to the known value given in degrees Celsius or Fahrenheit.
  pinMode(THERMOMETER, INPUT);
}

void loop(){
  lcd.setCursor(0,0);
  lcd.print(analogRead(THERMOMETER) * 0.125 - 22.0);
  delay(500);  
}
