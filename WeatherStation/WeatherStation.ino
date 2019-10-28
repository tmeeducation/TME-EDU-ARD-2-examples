/*  TME EDUCATION
 *  WheatherStation
 *  v0.3.0
 *  -------------
 *  It is a program showing the possibilities of using 
 *  a prototype board prepared by TME for the purpose 
 *  of creating a weather station
 */ 
#define PROJECT_NAME "WheatherStation"
#define VERSION "v0.3.0"

#include "includes.h"
#include "graphics/WeatherIcons.h"
////////CONSTANTS////////
//In this section, all constants resulting from the prototype board design are set
#define KEY_RIGHT 7
#define KEY_LEFT 4
#define KEY_UP 6
#define KEY_DOWN 5
#define KEY_CENTER 8
#define POTENTIOMETER A1
#define THERMOMETER A2
#define LIGHT_SENSOR A3
#define LED_SERIAL 12
#define LED_COUNT 5

////////MODIFIERS////////
//In this section there are constants whose modification will affect the operation of our plate
#define DELAY_BETWEEN_FRAMES 0.2

////////DECLARATIONS////////
//This section prepares variables that are responsible for the individual components on the board
Adafruit_SSD1306 display(0);
hd44780_I2Cexp lcd(0x20, I2Cexp_MCP23008, 7, 6, 5, 4, 3, 2, 1, HIGH);
Adafruit_MCP23008 seg;
Adafruit_NeoPixel ledStrip = Adafruit_NeoPixel(LED_COUNT, LED_SERIAL, NEO_GRB + NEO_KHZ800);

boolean frame = true;
unsigned long time = 0;
int temp, light;

enum TempScale{
  CELSIUS,
  FAHRENHEIT
} tempScale;

enum Animation{
  CLOUD,
  RAIN,
  STORM,
  SUN
} animation;

void setup(){
  lcd.begin(16, 2);
  intro(lcd);
  
  display.begin(0x2, 0x3C, false);
  display.clearDisplay();
  
  seg.begin(0x4);
  for(int i = 0; i < 8; i++)
    seg.pinMode(i, OUTPUT);

  ledStrip.begin();

  pinMode(THERMOMETER, INPUT);
  pinMode(LIGHT_SENSOR, INPUT);
  pinMode(POTENTIOMETER, INPUT);

  pinMode(KEY_RIGHT , INPUT);
  pinMode(KEY_LEFT , INPUT);
  pinMode(KEY_UP , INPUT);
  pinMode(KEY_DOWN , INPUT);
  pinMode(KEY_CENTER , INPUT);  
}

void loop(){
  for(int led = 1; led < LED_COUNT; led++)
    ledStrip.setPixelColor(led, 50, analogRead(POTENTIOMETER) / 1023.0 * 255, 100);
  ledStrip.show();

  if(digitalRead(KEY_CENTER)){
    delay(500);
    if(tempScale == CELSIUS){
      tempScale = FAHRENHEIT;
    }else{
      tempScale = CELSIUS;
    }
  }
  
  if(tempScale == CELSIUS){
    printOnSevenSeg('c');
    temp = getTemperature(TempScale(CELSIUS));
  }else{
    printOnSevenSeg('f');
    temp = getTemperature(TempScale(FAHRENHEIT));
  }

  light = analogRead(LIGHT_SENSOR) / 1023.0 * 100;  

  animation = readArrowKey();

  if(millis() > time){
    printNextFrame();
    
    time = millis() + (1000 * DELAY_BETWEEN_FRAMES);
    
    lcd.setCursor(0, 0);
    lcd.print("Temperature ");
    lcd.print(temp);
    lcd.print((char)223);
    lcd.print(tempScale == CELSIUS ? "C " : "F ");
    
    lcd.setCursor(0, 1);
    lcd.print("Light       ");
    lcd.print(light);
    lcd.print("% ");
  }
}

void printOnSevenSeg(char sign){
  uint8_t data = 0;
  
  switch(sign){
    case '0':
      data = B11111100;
      break;
    case '1':
      data = B01100000;
      break;
    case '2':
      data = B11011010;
      break;
    case '3':
      data = B11110010;
      break;
    case '4':
      data = B01100110;
      break;
    case '5':
      data = B10110110;
      break;
    case '6':
      data = B10111110;
      break;
    case '7':
      data = B11100000;
      break;
    case '8':
      data = B11111110;
      break;
    case '9':
      data = B11110110;
      break;
    case 'c':
      data = B10011100;
      break;
    case 'f':
      data = B10001110;
      break;
  }
  
  for(int i = 0; i < 8; i++)
    seg.digitalWrite(i, bitRead(data, 7 - i));  
}

void printNextFrame(){  
  display.clearDisplay();

  frame ? display.drawBitmap(32, 0, icons[animation * 2], 64, 64, 1) : display.drawBitmap(32, 0, icons[animation * 2 + 1], 64, 64, 1);

  frame = !frame;  
  display.display();
}

int getTemperature(TempScale tempScale){
  if(tempScale == CELSIUS){
    return analogRead(THERMOMETER) * 0.125 - 22.0;
  }
  if(tempScale == FAHRENHEIT){
    return (analogRead(THERMOMETER) * 0.125 - 22.0) * 9/5 + 32;
  }
}

Animation readArrowKey(){
  if(digitalRead(KEY_RIGHT)){
    return Animation(CLOUD);
  }
  if(digitalRead(KEY_LEFT)){
    return Animation(RAIN);
  }
  if(digitalRead(KEY_UP)){
    return Animation(STORM);
  }
  if(digitalRead(KEY_DOWN)){
    return Animation(SUN);
  }
}
