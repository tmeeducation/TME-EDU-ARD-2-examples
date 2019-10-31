/*  TME EDUCATION
 *  LightSensor-Lcd
 *  v0.1.0
 *  -------------
 *  In this program, we will start the light sensor. Maybe you have a flashlight at hand? :)
 */ 
#define PROJECT_NAME "LightSensor-Lcd"
#define VERSION "v0.1.0"

#include "includes.h"
////////CONSTANTS////////
//In this section, all constants resulting from the prototype board design are set
#define LIGHT_SENSOR A3

////////MODIFIERS////////
//In this section there are constants whose modification will affect the operation of our plate


////////DECLARATIONS////////
//This section prepares variables that are responsible for the individual components on the board
hd44780_I2Cexp lcd(0x20, I2Cexp_MCP23008, 7, 6, 5, 4, 3, 2, 1, HIGH);

void setup(){
  Serial.begin(9600);
  lcd.begin(16, 2);
  intro(lcd);

  //I think you already know how to handle this sensor. 
  //You will see the effect of its operation on the serial monitor. 
  //You can start it by pressing Ctrl + Shift + M. 
  //Change the program so that it shows the intensity of light also on the LCD display.
  pinMode(LIGHT_SENSOR, INPUT);
}

void loop(){
  int light = analogRead(LIGHT_SENSOR) / 1023.0 * 100;
  
  Serial.print(light);
  Serial.println("%");
  lcd.setCursor (0,0);
  lcd.print (light);
  lcd.print ("%");
  delay (100);
  
}
