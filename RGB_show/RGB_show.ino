/*  TME EDUCATION
 *  Rgb Show
 *  v0.1.0
 *  -------------
 *  Rgb Show
 */ 
#define PROJECT_NAME "Rgb Show"
#define VERSION "v0.1.0"

#include "includes.h"
////////CONSTANTS////////
//In this section, all constants resulting from the prototype board design are set
#define POTENTIOMETER A1
#define LED_SERIAL 12
#define LED_COUNT 5

////////MODIFIERS////////
//In this section there are constants whose modification will affect the operation of our plate


////////DECLARATIONS////////
//This section prepares variables that are responsible for the individual components on the board
hd44780_I2Cexp lcd(0x20, I2Cexp_MCP23008, 7, 6, 5, 4, 3, 2, 1, HIGH);
Adafruit_NeoPixel ledStrip = Adafruit_NeoPixel(LED_COUNT, LED_SERIAL, NEO_GRB + NEO_KHZ800);
Adafruit_MCP23008 seg;

void setup(){
  lcd.begin(16, 2);
  intro(lcd);

  pinMode(POTENTIOMETER, INPUT);

  lcd.print("       Use");
  lcd.setCursor(0, 1);
  lcd.print("  potentiometer");

  seg.begin(0x4);
  for(int i = 0; i < 8; i++)
    seg.pinMode(i, OUTPUT);

  ledStrip.begin();
  ledStrip.show();
}
int angle = 0;
void loop(){
  angle += 1;
  delay(10);
  if(angle > 360){
    angle = 0;
  }
  setColor(hue(map(analogRead(POTENTIOMETER), 0, 1023, 0, 360)));

  printOnSevenSeg(map(angle, 0, 360, 0, 10));
}

void setColor(uint32_t color){
  
  // for(uint16_t i = 0; i < analogRead(POTENTIOMETER)/256; i++){
  //   if()
  // }
  int pot = (map(analogRead(POTENTIOMETER), 0, 1023, 0, 5));
  ledStrip.setPixelColor(pot, color);
  if(pot == 0){
    setColorForAll(hue(angle));
  }
  ledStrip.show();
}

void setColorForAll(uint32_t color){
  for(uint16_t i = 0; i < ledStrip.numPixels(); i++){
    ledStrip.setPixelColor(i, color);
  }  
  ledStrip.show();
}

uint32_t hue(int angle){
  if(angle > 360)
    angle = 360;
  if(angle < 0)
    angle = 0;

  angle = 360 - angle;

  if(angle <= 60){
    return ledStrip.Color(255, angle * (255.0 / 60.0), 0);
  }else if(angle <= 120){
    return ledStrip.Color(255 - ((angle - 60) * (255.0 / 60.0)), 255, 0);
  }else if(angle <= 180){
    return ledStrip.Color(0, 255, (angle - 120) * (255.0 / 60.0));
  }else if(angle <= 240){
    return ledStrip.Color(0, 255 - ((angle - 180) * (255.0 / 60.0)), 255);
  }else if(angle <= 300){
    return ledStrip.Color((angle - 240) * (255.0 / 60.0), 0, 255);
  }else if(angle <= 360){
    return ledStrip.Color(255, 0, 255 - ((angle - 300) * (255.0 / 60.0)));
  }
}

void printOnSevenSeg(int sign){
  uint8_t data = 0;
  
  switch(sign){
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
      data = B11110010;
      break;
    case 4:
      data = B01100110;
      break;
    case 5:
      data = B10110110;
      break;
    case 6:
      data = B10111110;
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
  for(int i = 0; i < 8; i++)
    seg.digitalWrite(i, bitRead(data, 7 - i));  
}
