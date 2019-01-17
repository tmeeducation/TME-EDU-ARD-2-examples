/*  TME EDUCATION
 *  Knob-LED
 *  v0.1.0
 *  -------------
 *  In this program you will learn how to operate the potentiometer built into the board. 
 *  Thanks to it, we can significantly expand our programs with a quite intuitive controller.
 */ 
#define PROJECT_NAME "Knob-LED"
#define VERSION "v0.1.0"

#include "includes.h"
////////CONSTANTS////////
//In this section, all constants resulting from the prototype board design are set
#define KEY_LEFT 4
#define KEY_RIGHT 7
#define POTENTIOMETER 1
////////MODIFIERS////////
//In this section there are constants whose modification will affect the operation of our plate


////////DECLARATIONS////////
//This section prepares variables that are responsible for the individual components on the board
hd44780_I2Cexp lcd(0x20, I2Cexp_MCP23008, 7, 6, 5, 4, 3, 2, 1, HIGH);
Adafruit_NeoPixel ledStrip = Adafruit_NeoPixel(5, 12, NEO_GRB + NEO_KHZ800);

boolean show = true;
//int value = 100;
int red = 100;
int green = 100;
int blue = 100;

//The creation visible below is an enum variable, thanks to which we can select only the values placed in it. 
//Here are r, g and b. 
//This variable is called "col" and its default value is "r"
enum Col{
  r,
  g,
  b
}col = r; //This variable is called "col" and its default value is "r"

void setup(){
  Serial.begin(9600);
  lcd.begin(16, 2);
  intro(lcd);

  pinMode(KEY_LEFT , INPUT);
  pinMode(KEY_RIGHT , INPUT);

  ledStrip.begin();  
  lcd.print("Left to start");
}

void loop(){
  //An important skill of the programmer is to understand what the program is doing. 
  //Try it before running it. For an explanation of how the program works, see the "how.txt" file. 
  //Look at it later and check if you have understood the code correctly without running it.
  delay(50);

  if(digitalRead(KEY_LEFT)){    
    if(col == g)
      col = r;
    else if(col == b)
      col = g;
    printColorDesc(col);
    delay(500);
  }
  if(digitalRead(KEY_RIGHT)){
    if(col == r)
      col = g;
    else if(col == g)
      col = b;
    printColorDesc(col);
    delay(500);
  }  

  if(col == r){
    red = analogRead(POTENTIOMETER) / 4; 
  }else if(col == g){
    green = analogRead(POTENTIOMETER) / 4;
  }else{
    blue = analogRead(POTENTIOMETER) / 4;
  }
  
  ledStrip.setPixelColor(0, red, green, blue);
  ledStrip.show();
}

//This method is responsible for displaying a message informing us of the currently changed color
void printColorDesc(Col col){
  lcd.clear();
  lcd.print("now you change: ");
  lcd.setCursor(0, 1);
  Serial.print(col);
  if(col == r){
    lcd.print("red");
  }
  if(col == g){
    lcd.print("green");
  }
  if(col == b){
    lcd.print("blue");
  }
}







