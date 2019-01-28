/*  TME EDUCATION
 *  7Seg-Microphone
 *  v0.1.0
 *  -------------
 *  In this program we will count the tapping on the microphone on the 7-segment display.
 */ 
#define PROJECT_NAME "7Seg-Mic"
#define VERSION "v0.1.0"

#include "includes.h"
////////CONSTANTS////////
//In this section, all constants resulting from the prototype board design are set
#define MICROPHONE 0


////////MODIFIERS////////
//In this section there are constants whose modification will affect the operation of our plate
#define SENSITIVITY 50 //using the previous program "10_Speaker-Potentiometer" 
                       //Select the appropriate value of the microphone sensitivity.

////////DECLARATIONS////////
//This section prepares variables that are responsible for the individual components on the board
hd44780_I2Cexp lcd(0x20, I2Cexp_MCP23008, 7, 6, 5, 4, 3, 2, 1, HIGH);
Adafruit_MCP23008 seg;
int i = 0;

void setup(){
  lcd.begin(16, 2);
  intro(lcd);

  //we give the address of the display.
  seg.begin(0x4);

  //From now on, we're dealing with it the same as with diodes.
  for(int i = 0; i < 8; i++)
    seg.pinMode(i, OUTPUT);
  
  count(0);
}

void loop(){
  if(analogRead(MICROPHONE) > SENSITIVITY){
    i++;
    if(i > 9){
      i = 0;
    }
    
    count(i);
    delay(500);
  }
}

void count(int digit){  
  uint8_t data = 0; //uint8_t - an unsigned 8-bit integer

  //The manner of influencing the values of the respective bits on the display has been explained
  //in the graphics attached to the project.

  //switch-case allows us to choose the way the program works depending on the value we give to it
  //As you can see, a few numbers do not display correctly. Can you correct them?
  switch(digit){
    case 0:
      data = B11111100;
      break;
    case 1:
      data = B01100000;
      break;
    case 2:
      data = B11011010;
      break;
    case 3:
      data = B01110011;
      break;
    case 4:
      data = B01100110;
      break;
    case 5:
      data = B10100100;
      break;
    case 6:
      data = B11011110;
      break;
    case 7:
      data = B11100000;
      break;
    case 8:
      data = B11111110;
      break;
    case 9:
      data = B11110110;
      break;
  }

  //The bitRead() method allows us to read a specific bit from a variable. bitRead(variable, bitNumber)
  for(int i = 0; i < 8; i++)
    seg.digitalWrite(i, bitRead(data, 7 - i));
}

