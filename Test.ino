/*  TME EDUCATION
 *  Test
 *  v0.1.0
 *  -------------
 *  Description
 */ 
#define PROJECT_NAME "Test"
#define VERSION "v0.1.0"

#include "includes.h"
////////CONSTANTS////////
//In this section, all constants resulting from the prototype board design are set
#define MICROPHONE    A0
#define POTENTIOMETER A1
#define THERMOMETHER  A2
#define LIGHT_SENSOR  A3

#define BUZZER        2
#define IR_SENSOR     3
#define KEY_LEFT      4
#define KEY_DOWN      5
#define KEY_UP        6
#define KEY_RIGHT     7
#define KEY_CENTER    8
#define LED_RED       9
#define LED_GREEN     10
#define LED_BLUE      11
#define LED_SERIAL    12
#define LED           13

#define HEIGHT        64
#define WIDTH         128
#define LED_COUNT     5
////////MODIFIERS////////
//In this section there are constants whose modification will affect the operation of our plate


////////DECLARATIONS////////
//This section prepares variables that are responsible for the individual components on the board
hd44780_I2Cexp lcd(0x20, I2Cexp_MCP23008, 7, 6, 5, 4, 3, 2, 1, HIGH);
Adafruit_SSD1306 display(0);
Adafruit_MCP23008 seg;
Adafruit_NeoPixel ledStrip = Adafruit_NeoPixel(LED_COUNT, LED_SERIAL, NEO_GRB + NEO_KHZ800);
char osciloscope[WIDTH];
uint8_t pointer = 0;
uint8_t iterator = 0;
uint8_t select = 0;
int testLoop = -1;

void setup(){
  lcd.begin(16, 2);
  intro(lcd);
  
  display.begin(0x2, 0x3C, false);
  display.setTextColor(1);
  display.clearDisplay();  
  for(int i = 0; i < WIDTH; i++)
    osciloscope[i] = HEIGHT;
  
  seg.begin(0x4);
  for(int i = 0; i < 8; i++)
    seg.pinMode(i, OUTPUT);

  ledStrip.begin();
    
  pinMode(BUZZER, OUTPUT);
  pinMode(IR_SENSOR, INPUT);
  pinMode(KEY_LEFT, INPUT);
  pinMode(KEY_DOWN, INPUT);
  pinMode(KEY_UP, INPUT);
  pinMode(KEY_RIGHT, INPUT);
  pinMode(KEY_CENTER, INPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED, OUTPUT);
}

void loop(){
//  if(digitalRead
 // testMicrophone();
 // testPotentiometer();
// testThermomether();
 // testLightSensor();
//  testSegmentDisplay();
//  testBuzzer();
 // testButtons();
  testIRSensor();
}

void testMicrophone(){
  osciloscope[pointer] = HEIGHT - map(analogRead(MICROPHONE), 0, 1023, 0, HEIGHT - 1);
  display.clearDisplay();
  
  pointer++;
  int j = 0;
  for(int i = pointer; i < WIDTH; i++, j++)
    display.drawPixel(j, osciloscope[i], 1);

  for(int i = 0; i < pointer; i++, j++)
    display.drawPixel(j, osciloscope[i], 1);

  int soundLevel = map(analogRead(POTENTIOMETER), 0, 1023, 0, HEIGHT - 1);
  display.setCursor(0, soundLevel - 8);
  display.print("sensitivity"); 
  display.writeFastHLine(0, soundLevel, 128, 1);

  if(osciloscope[pointer - 1] < soundLevel){
    digitalWrite(LED, HEIGHT);
  }else{
    digitalWrite(LED, LOW);
  }

  if(pointer >= WIDTH){
    pointer = 0;
  }
  
  display.display();
}

void testPotentiometer(){
  display.setTextSize(1);
  display.setCursor(25, 15);
  
  display.clearDisplay();
  
  display.print("POTENTIOMETER");  
  
  display.drawRoundRect(5, 25, WIDTH - 10, 25, 8, 1);
  display.fillRoundRect(5, 25, map(analogRead(POTENTIOMETER),0, 1023, 16, WIDTH - 10), 25, 8, 1);
  
  display.display();
}

void testThermomether(){
  display.clearDisplay();
  display.fillCircle(8, 55, 8, 1);

  display.fillRoundRect(4, 2, 9, 56, 4, 0);
  display.drawRoundRect(4, 2, 9, 56, 4, 1);

  int temperature = map(analogRead(THERMOMETHER), 0, 1023, 56, 0);  
  display.fillRoundRect(4, 2 + 56 - temperature, 9, temperature, 4, 1);

  display.setTextSize(3);
  display.setCursor(25, 25);
  display.print(analogRead(THERMOMETHER) * 0.125 - 22.0);

  display.display();
}

void testLightSensor(){
  display.clearDisplay();

  display.fillCircle(0, 0, 15, 1);

  for(double i = 0; i < PI/2.0 * 0.001 * analogRead(LIGHT_SENSOR); i+=0.07){
    display.drawLine((int)(sin(i)*20), (int)(cos(i)*20), (int)(sin(i) * 50 * 0.001 * analogRead(LIGHT_SENSOR)), (int)(cos(i) * 50 * 0.001 * analogRead(LIGHT_SENSOR)), 1);
  }

  display.setTextSize(2);
  display.setCursor(65, 40);
  display.print(map(analogRead(LIGHT_SENSOR), 0, 1023, 0, 100));
  display.print("%");

  ledStrip.setPixelColor(0, 255, 255, 255);
  ledStrip.setBrightness(map(analogRead(LIGHT_SENSOR), 0, 1023, 0, 255));
  ledStrip.show();

  display.display();
}

void testSegmentDisplay(){
  uint8_t data = 0;

  switch(iterator){
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
    case 10:
      data = B11101110;
      break;
    case 11:
      data = B00111110;
      break;
    case 12:
      data = B10011100;
      break;
    case 13:
      data = B01111010;
      break;
    case 14:
      data = B10011110;
      break;
    case 15:
      data = B10001110;
      break;
  }

  for(int i = 0; i < 8; i++)
    seg.digitalWrite(i, bitRead(data, 7 - i));

  iterator++;
  if(iterator > 15)
    iterator = 0;
    
  delay (250);
}

void testBuzzer(){
  display.clearDisplay();

  if(iterator % 2 == 0){
    display.drawCircle(35, 30, 20, 1);
    display.fillRoundRect(0, 0, 48, HEIGHT, 0, 0);
    display.drawCircle(35, 30, 15, 1);
    display.fillRoundRect(0, 0, 44, HEIGHT, 0, 0);
    display.drawCircle(35, 30, 10, 1);
    display.fillRoundRect(0, 0, 39, HEIGHT, 0, 0);

    digitalWrite(BUZZER, true);
  }
  
  display.drawTriangle(10, 30, 35, 10, 35, 50, 1);
  display.fillRoundRect(10, 20, 10, 20, 0, 0);
  display.drawRoundRect(10, 20, 10, 20, 0, 1);

  display.display();

  iterator++;
  delay(100);
  digitalWrite(BUZZER, false);
}

void testButtons(){
  if(analogRead(POTENTIOMETER) != testLoop){
    lcd.clear();
    lcd.print("turn knob right");
    lcd.setCursor(0, 1);
    lcd.print("to switch test");
    testLoop = analogRead(POTENTIOMETER);
  }
  
  while(analogRead(POTENTIOMETER) > 5){
    display.clearDisplay();
    
    display.drawTriangle(32, 31, 42, 21, 42, 41, 1);
    display.drawTriangle(94, 31, 84, 21, 84, 41, 1);
    display.drawTriangle(63, 0, 53, 10, 73, 10, 1);
    display.drawTriangle(63, 62, 53, 52, 73, 52, 1);
    display.drawCircle(63, 31, 10, 1);
    
    if(digitalRead(KEY_LEFT)){
      display.fillTriangle(32, 31, 42, 21, 42, 41, 1);    
    }
    if(digitalRead(KEY_RIGHT)){
      display.fillTriangle(94, 31, 84, 21, 84, 41, 1);
    }
    if(digitalRead(KEY_UP)){
      display.fillTriangle(63, 0, 53, 10, 73, 10, 1);
    }
    if(digitalRead(KEY_DOWN)){
      display.fillTriangle(63, 62, 53, 52, 73, 52, 1);
    }
    if(digitalRead(KEY_CENTER)){
      display.fillCircle(63, 31, 10, 1);
    }
    display.display();
  }
}

void testIRSensor(){
  display.drawCircle(85, 31, 20, 1);
  display.fillRoundRect(75, 0, 30, 64, 0, 0);
  display.drawCircle(85, 31, 15, 1);
  display.fillRoundRect(80, 0, 30, 64, 0, 0);
  display.drawCircle(85, 31, 10, 1);
  display.fillRoundRect(85, 0, 30, 64, 0, 0);

  if(digitalRead(IR_SENSOR)){
    display.fillCircle(40, 31, 8, 1);
    digitalWrite(LED, HIGH);
  }else{
     display.fillCircle(40, 31, 8, 0);
    display.drawCircle(40, 31, 8, 1);
    digitalWrite(LED, LOW);
   
  }
  display.fillRoundRect(0, 0, 40, 64, 0, 0);
  
  display.drawFastVLine(40, 3, 57, 1);
  
  display.display();
}

void testLed(){
  
}

void testdisplay(){
  
}
