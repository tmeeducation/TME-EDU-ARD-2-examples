/*  TME EDUCATION
 *  In this program, we'll scratch a little using display display
 *  v0.1.0
 *  -------------
 *  display-Graphics
 */ 
#define PROJECT_NAME "display-Graphics"
#define VERSION "v0.1.0"
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define RESET_BTN 4


#include "includes.h"
////////CONSTANTS////////
//In this section, all constants resulting from the prototype board design are set

////////MODIFIERS////////
//In this section there are constants whose modification will affect the operation of our plate


////////DECLARATIONS////////
//This section prepares variables that are responsible for the individual components on the board
hd44780_I2Cexp lcd(0x20, I2Cexp_MCP23008, 7, 6, 5, 4, 3, 2, 1, HIGH);
Adafruit_SSD1306 display(SCREEN_WIDTH,SCREEN_HEIGHT, &Wire, RESET_BTN);


//Creating programs is mainly finding a way to solve the problem. 
//Fortunately, we have some tools that will allow us to solve them. 
//In this program, I gave you some tools. Try to use them to do two things:
//- Draw a face
//- Make a tic-tac-toe game

void setup(){
  lcd.begin(16, 2);
  intro(lcd);

  //These methods are explained in the "Knob-Oscilloscope" program if you don't remember what they are responsible for.
  display.begin(0x2, 0x3C, false);
  display.clearDisplay();
}


void loop(){
  //A branch() function is performed at the very bottom of the program. 
  //It is a recursive function, that is, one that calls itself.
  branch(64.0);
  display.display();
  delay(1000);
  display.clearDisplay();

  //drawChar(x, y, char, color, background, size) - draw a char
  display.drawChar(20, 0, 'x', 1, 1, 6);
  display.display();
  delay(1000);
  display.clearDisplay();

  //drawCircle(x, y, radius, color) - draw a circle
  display.drawCircle(32, 32, 10, 1);
  display.display();
  delay(1000);
  display.clearDisplay();

  //drawTriangle(x0, y0, x1, y1, x2, y2, color) - draw a triangle
  display.drawTriangle(32, 32, 10, 50, 10, 20, 1);
  display.display();
  delay(1000);
  display.clearDisplay();

  //drawRoundRect(x, y, width, height, radius, color) - draw a rounded rectangle
  display.drawRoundRect(32, 32, 20, 20, 5, 1);
  display.display();
  delay(1000);
  display.clearDisplay();

  //fillRoundRect(x, y, width, height, radius, color) - draw a filled rounded rectangle
  display.fillRoundRect(32, 32, 20, 20, 5, 1);
  display.display();
  delay(1000);
  display.clearDisplay();

  //drawFastVLine(x, y, height, color) - draw a vertical line
  //drawFastHLine(x, y, widht, color) - draw a horizontal line
  display.drawFastVLine(10, 10, 20, 1);
  display.drawFastHLine(10, 10, 20, 1);
  display.display();
  delay(1000);
  display.clearDisplay();
}


//the recursive function is here ;)
void branch(float h){
  h *= 0.66;

  if(h>2){
    //drawLine(x0, y0, x1, y1, color) - draw a line
    display.drawLine(h, h, h*2+10, h+10, 1);
    branch(h);
  }
}
