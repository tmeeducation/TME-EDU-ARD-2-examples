/*  TME EDUCATION
 *  LEDBlink
 *  v0.1.0
 *  -------------
 *  In this lesson, we will learn to blink with a diode
 */ 
#define PROJECT_NAME "LEDBlink"
#define VERSION "v0.1.0"

#include "includes.h"
////////CONSTANTS////////
//In this section, all constants resulting from the prototype board design are set
#define LED_1 13

////////MODIFIERS////////
//In this section there are constants whose modification will affect the operation of our plate


////////DECLARATIONS////////
//This section prepares variables that are responsible for the individual components on the board
hd44780_I2Cexp lcd(0x20, I2Cexp_MCP23008, 7, 6, 5, 4, 3, 2, 1, HIGH);

void setup(){
  lcd.begin(16, 2);
  intro(lcd);

  pinMode(LED_1, OUTPUT); //here we tell to program that we want to use our led in future  
}

void loop(){
  digitalWrite(LED_1, HIGH); //Now we turn on our led.
  delay(1000); //If you want to blink the diode, then you must first turn it on, then wait a bit, 
  //and then turn it off and wait again.
  digitalWrite(LED_1, LOW); //Now we turn off our led.
  delay(1000); //If we comment out the delay function, the diode will still be flashing, 
  //but with such a speed that the only thing we notice is its slight dimming.
}
