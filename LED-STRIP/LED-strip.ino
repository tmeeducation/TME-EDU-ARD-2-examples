/*  TME EDUCATION
 *  LEDStrip
 *  v0.1.0
 *  -------------
 *  In this program you will learn how to use an LED strip built into the TME board
 */ 
#define PROJECT_NAME "LEDStrip"
#define VERSION "v0.1.0"

#include "includes.h"
////////CONSTANTS////////
//In this section, all constants resulting from the prototype board design are set
#define LED_SERIAL 12
#define LED_COUNT 5

////////MODIFIERS////////
//In this section there are constants whose modification will affect the operation of our plate


////////DECLARATIONS////////
//This section prepares variables that are responsible for the individual components on the board
hd44780_I2Cexp lcd(0x20, I2Cexp_MCP23008, 7, 6, 5, 4, 3, 2, 1, HIGH);
//On the board we also have diodes connected to each other in a strip.
//Below, we define an object that will store information about these LEDs. For its creation, 
//we need information about the number of LEDs and where the first one is connected.
Adafruit_NeoPixel ledStrip = Adafruit_NeoPixel(LED_COUNT, LED_SERIAL, NEO_GRB + NEO_KHZ800);

void setup(){
  lcd.begin(16, 2);
  intro(lcd);

  //Here we start work with diodes
  ledStrip.begin();

  //Now we can start working with diodes. In the setPixelColor method we give as parameters the first number of LEDs, 
  //and then the color values in the order of red, green, blue. We choose color values from 0 to 255.
  //TIP: Arguments for the setPixelColor function: setPixelColor(pixelNumber, red, green, blue);
  for(int i = 0; i < LED_COUNT; i++)
    ledStrip.setPixelColor(0, 5, 10, 20);
  
  //the show method starts the set color
  ledStrip.show();
  delay(1000);

  //the setBrightness method sets the brightness of the diode. By default, it has a value of 255. 
  //So giving 100 automatically reduce the brightness. We can do the same by choosing correspondingly smaller values 
  //in the setPixelColor method
  ledStrip.setBrightness(100);
  ledStrip.show();
  delay(1000);  
}

//It's your job to fix my error and run all the LEDs. A small change is needed. You can do it :)

void loop(){
  
}
