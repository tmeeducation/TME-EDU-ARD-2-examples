/*  TME EDUCATION
 *  DemoLED
 *  v0.1.2
 *  -------------
 *  It is a program showing the possibilities of using 
 *  a prototype board prepared by TME for the purpose 
 *  of creating a weather station
 */ 
#define PROJECT_NAME "DemoLED"
#define VERSION "v0.1.2"

#include "includes.h"
////////CONSTANTS////////
//In this section, all constants resulting from the prototype board design are set
#define KEY_RIGHT 7
#define KEY_LEFT 4
#define KEY_UP 6
#define KEY_DOWN 5
#define KEY_CENTER 8
#define POTENTIOMETER A1
#define MICROPHONE A0
#define LED_SERIAL 12
#define LED_COUNT 5

////////MODIFIERS////////
//In this section there are constants whose modification will affect the operation of our board
#define SPEED 1
#define BLINKS 10

////////DECLARATIONS////////
//This section prepares variables that are responsible for the individual components on the board
hd44780_I2Cexp lcd(0x20, I2Cexp_MCP23008, 7, 6, 5, 4, 3, 2, 1, HIGH);
Adafruit_NeoPixel ledStrip = Adafruit_NeoPixel(LED_COUNT, LED_SERIAL, NEO_GRB + NEO_KHZ800);
Adafruit_MCP23008 seg;
int showType = 0;
int oldShowType = -1;
uint32_t i = 0;

void setup(){
  Serial.begin(9600);
  lcd.begin(16, 2);
  intro(lcd);
  
  pinMode(POTENTIOMETER, INPUT);
  pinMode(KEY_RIGHT , INPUT);
  pinMode(KEY_LEFT , INPUT);

  seg.begin(0x4);
  for(int i = 0; i < 8; i++)
    seg.pinMode(i, OUTPUT);
  
  ledStrip.begin();
  ledStrip.show();
}

void loop(){
  if(digitalRead(KEY_RIGHT)){
    showType++;
    if(showType > 8)
      showType = 0;
    delay(500);
  }    
  if(digitalRead(KEY_LEFT)){
    showType--;
    if(showType < 0)
      showType = 8;
          
    delay(500);
  }

  if(showType != oldShowType || isLooped(showType)){
    if(showType != oldShowType){
      chooseDescription(showType);
    }
    playShow(showType);
    oldShowType = showType;
  }

  i++;
}

boolean isLooped(int showType){
  int result[] = {1, 1, 1, 0, 0, 0, 1, 1, 1};
  return result[showType];  
}

void playShow(int showType){
  float vol = analogRead(POTENTIOMETER) / 1023.0;
  
  switch(showType){
    case 0:
      setColor(ledStrip.Color(255 * vol, 0, 0));
      break;
    case 1:
      setColor(ledStrip.Color(0, 255 * vol, 0));
      break;
    case 2:
      setColor(ledStrip.Color(0, 0, 255 * vol));
      break;
    case 3:
      blink(ledStrip.Color(255, 0, 0));
      break;
    case 4:
      blink(ledStrip.Color(0, 255, 0));
      break;
    case 5:
      blink(ledStrip.Color(0, 0, 255));
      break;
    case 6:
      setColor(hue(i / 16 % 360));
      break;
    case 7:
      setColor(hue(map(analogRead(POTENTIOMETER), 0, 1023, 0, 360)));
      break;
    case 8:
      if(analogRead(MICROPHONE) > 400){
        setColor(hue(map(analogRead(POTENTIOMETER), 0, 1023, 0, 360)));
        delay(50);
        setColor(ledStrip.Color(0, 0, 0));
      }
      break;
  }
}

void chooseDescription(int description){
  switch(description){
    case 0:
      writeDescription("move","potentiometer");
      break;
    case 1:
      writeDescription("move","potentiometer");
      break;
    case 2:
      writeDescription("move","potentiometer");
      break;
    case 3:
      writeDescription("move knob","and wait");
      break;
    case 4:
      writeDescription("move knob","and wait");
      break;
    case 5:
      writeDescription("move knob","and wait");
      break;
    case 6:
      writeDescription("","");
      break;
    case 7:
      writeDescription("move","potentiometer");
      break;  
    case 8:
      writeDescription("hit microphone","and move knob");
      break;        
  }
}

void writeDescription(String first, String second){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(first);
  lcd.setCursor(0, 1);
  lcd.print(second);
}

void setColor(uint32_t color){
  for(uint16_t i = 0; i < ledStrip.numPixels(); i++){
    ledStrip.setPixelColor(i, color);
  }  
  ledStrip.show();
}

void blink(uint32_t color){
  for(int i = 0; i < BLINKS; i++){
    printOnSevenSeg(BLINKS - i - 1);
    setColor(color);
    delay(analogRead(POTENTIOMETER));
    setColor(ledStrip.Color(0, 0, 0));
    delay(analogRead(POTENTIOMETER));
  }
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
