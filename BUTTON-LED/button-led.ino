/*  TME EDUCATION
 *  Buttons-LED
 *  v0.1.0
 *  -------------
 *  In this program, we will combine the skill of operating the led strip with the buttons located on the TME board
 */ 
#define PROJECT_NAME "Buttons-LED"
#define VERSION "v0.1.0"

#include "includes.h"
////////CONSTANTS////////
//In this section, all constants resulting from the prototype board design are set
#define KEY_UP 6
#define KEY_DOWN 5
#define KEY_LEFT 4
#define KEY_RIGHT 7
#define KEY_CENTER 8
////////MODIFIERS////////
//In this section there are constants whose modification will affect the operation of our plate


////////DECLARATIONS////////
//This section prepares variables that are responsible for the individual components on the board
hd44780_I2Cexp lcd(0x20, I2Cexp_MCP23008, 7, 6, 5, 4, 3, 2, 1, HIGH);
Adafruit_NeoPixel ledStrip = Adafruit_NeoPixel(5, 12, NEO_GRB + NEO_KHZ800);

//We want the program to enable us to turn off the LEDs, 
//change their color and brightness, therefore we declare below three variables
boolean show = true; // on/off
int value = 100;     // brightness
int color = 100;     // color

void setup(){
  Serial.begin(9600);
  lcd.begin(16, 2);
  intro(lcd);

  //The buttons are connected to the appropriate pins defined above in the "CONSTANTS" section. 
  //If the button is pressed, the signal comes to the Arduino, so we have to pass on to our program 
  //at first that we should treat the pins as inputs. We do this using the pinMode() method
  pinMode(KEY_RIGHT , INPUT);
  pinMode(KEY_LEFT , INPUT);
  pinMode(KEY_UP , INPUT);
  pinMode(KEY_DOWN , INPUT);
  pinMode(KEY_CENTER , INPUT);

  ledStrip.begin();
}

void loop(){
  delay(10);
  //To read whether a given button is pressed, read the value of a given pin using the digitalRea() method. 
  //After pressing one of the buttons, the appropriate value from the three previously declared variables changes.

  ////////////////////////////////////////////////////  ON / OFF
  if(digitalRead(KEY_CENTER)){
    show = !show;
    //check what happens if you delete the line with a delay method below.
    //The explanation can be found in the file "explaination.png", which is located in the folder with the project
    delay(500);
  }
  ////////////////////////////////////////////////////  BRIGHTNESS ++
  if(digitalRead(KEY_UP) && value < 255){
    value++;
  }
  ////////////////////////////////////////////////////  BRIGHTNESS --
  if(digitalRead(KEY_DOWN) && value > 0){
    value--;
  }
  ////////////////////////////////////////////////////  COLOR ++
  if(digitalRead(KEY_LEFT) && color < 255 ){
    color++;
  }
  ////////////////////////////////////////////////////  COLOR --
  if(digitalRead(KEY_RIGHT) && color > 0){
    color--;
  }

  //At the very end of the loop, after changing the value of any of the variables, we set the diode parameters to current. 
  //You may have noticed that to turn off the diode, I used a method that reduces its brightness to zero.  
  for (int i = 0; i < 5 ; i++){
  ledStrip.setPixelColor(i, 50, color, 100);
  ledStrip.setBrightness(value);
  if(!show){
    ledStrip.setBrightness(0);
  }
  ledStrip.show();
}







