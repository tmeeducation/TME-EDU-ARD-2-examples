/*  TME EDUCATION
 *  Speaker-Potentiometer
 *  v0.1.0
 *  -------------
 *  In this program you can control the frequency of the beeps. It's almost like a Geiger-Müller sensor.
 */ 
#define PROJECT_NAME "Speaker-Potentio"
#define VERSION "v0.1.0"

#include "includes.h"
////////CONSTANTS////////
//In this section, all constants resulting from the prototype board design are set
#define SPEAKER 2
#define POTENTIOMETER A1

////////MODIFIERS////////
//In this section there are constants whose modification will affect the operation of our plate


////////DECLARATIONS////////
//This section prepares variables that are responsible for the individual components on the board
hd44780_I2Cexp lcd(0x20, I2Cexp_MCP23008, 7, 6, 5, 4, 3, 2, 1, HIGH);

void setup(){
  lcd.begin(16, 2);
  intro(lcd);

  //The built-in loudspeaker has a built-in generator so we can not control its frequency. 
  //On the other hand, its use is as simple as the use of LEDs. See for yourself how the program looks like.
  //Your task: Try to make two faster beeps at each interval.
  pinMode(SPEAKER, OUTPUT);  
}

void loop(){
  delay(analogRead(POTENTIOMETER));
  bip();
}

void bip(){
  digitalWrite(SPEAKER, HIGH);
  delay(10);
  digitalWrite(SPEAKER, LOW);
}






