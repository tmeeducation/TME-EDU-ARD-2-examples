 /*  TME EDUCATION
 *  Knob-Oscilloscope
 *  v0.1.0
 *  -------------
 *  In this program, we will create our own oscilloscope showing the voltage level on one of the arduino inputs.
 *  It is also the first program in which we will use the display display.
 */ 
#define PROJECT_NAME "Knob-Oscillo"
#define VERSION "v0.1.0"

#include "includes.h"
////////CONSTANTS////////
//In this section, all constants resulting from the prototype board design are set
#define POTENTIOMETER A1
#define HEIGHT 64
#define WIDTH 128
////////MODIFIERS////////
//In this section there are constants whose modification will affect the operation of our plate


////////DECLARATIONS////////
//This section prepares variables that are responsible for the individual components on the board
hd44780_I2Cexp lcd(0x20, I2Cexp_MCP23008, 7, 6, 5, 4, 3, 2, 1, HIGH);
//Creating a variable responsible for the display display.
Adafruit_SSD1306 display(0);

//We want our oscilloscope to have a history of voltage. 
//To enable this, we have created an array that stores the previous values. 
//As you can see, it's a character type. This is necessary due to memory restrictions imposed by Arduino. 
//And for this task, we are quite sufficient for char instead of int.
char level[WIDTH];

void setup(){
  Serial.begin(9600);
  lcd.begin(16, 2);
  intro(lcd);

  //the begin() method allows us to start working with the display. Its parameters should always be the same.
  display.begin(0x2, 0x3C, false);
  //clearDisplay () in turn cleans the entire display screen
  display.clearDisplay();

  
  for(int i = 0; i < WIDTH; i++)
    level[i] = 0;  
}

void loop(){
  //At this point, we move all the pixels one position. 
  //Unfortunately, this is not an optimal solution. 
  //If the display had a much wider width then we would have to rewrite much more information. 
  //Below you have an example of how you can do it differently.
  //(Commented section with loop)
  for(int i = 0; i < WIDTH - 1; i++)
    level[i] = level[i+1];

  level[WIDTH - 1] = map(analogRead(POTENTIOMETER), 1023,0, 0, HEIGHT - 1);
  display.clearDisplay();

  //In the following loop the drawPixel() method called to the display object
  //allows you to display the pixel in the right place - drawPixel(x, y, color)
  for(int i = 0; i < WIDTH; i++)
    display.drawPixel(i, level[i], 1);
    
  display.display();
}



//int pointer = 0;
//void loop(){
//  level[pointer] = map(analogRead(POTENTIOMETER), 0, 1023, 0, HEIGHT - 1);
//  display.clearDisplay();
//  
//  pointer++;
//  int j = 0;
//  for(int i = pointer; i < WIDTH; i++, j++)
//    display.drawPixel(j, level[i], 1);
//
//  for(int i = 0; i < pointer; i++, j++)
//    display.drawPixel(j, level[i], 1);
//    
//  if(pointer >= WIDTH){
//    pointer = 0;
//  }
//  display.display();
//}








