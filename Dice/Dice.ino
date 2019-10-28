/*  TME EDUCATION
 *  Dice
 *  v0.1.0
 *  -------------
 *  Roll a dice
 */ 
#define PROJECT_NAME "Dice"
#define VERSION "v0.1.0"

#include "includes.h"
#include "dice.h"
#include "dice2.h"
#include "dice3.h"
////////CONSTANTS////////
//In this section, all constants resulting from the prototype board design are set
#define KEY_CENTER 8
#define BUZZER 2

////////MODIFIERS////////
//In this section there are constants whose modification will affect the operation of our plate


////////DECLARATIONS////////
//This section prepares variables that are responsible for the individual components on the board
hd44780_I2Cexp lcd(0x20, I2Cexp_MCP23008, 7, 6, 5, 4, 3, 2, 1, HIGH);
Adafruit_SSD1306 display(0);
Adafruit_MCP23008 seg;


void setup(){
  lcd.begin(16, 2);
  intro(lcd);  

  pinMode(KEY_CENTER, INPUT);
  pinMode(BUZZER, OUTPUT);
  
  display.begin(0x2, 0x3C, false);
  display.clearDisplay();
  display.display();

  seg.begin(0x4);
  for(int i = 0; i < 8; i++)
    seg.pinMode(i, OUTPUT);

  lcd.clear();
  lcd.print("Press center");
  lcd.setCursor(0, 1);
  lcd.print("to roll");
}

void loop(){
  if(digitalRead(KEY_CENTER)){
    display.clearDisplay();
    display.drawBitmap(0, 0, bitmap, BMPWIDTH, BMPHEIGHT, 1);
    display.display();
    tone(BUZZER, 100, 10);
    delay(100);

    display.clearDisplay();
    display.drawBitmap(0, 0, bitmap3, BMPWIDTH, BMPHEIGHT, 1);
    display.display();
    tone(BUZZER, 100, 10);
    delay(200);

    display.clearDisplay();
    display.drawBitmap(0, 0, bitmap2, BMPWIDTH, BMPHEIGHT, 1);
    display.display();
    tone(BUZZER, 100, 10);
    delay(300);

    display.clearDisplay();
    display.drawBitmap(0, 0, bitmap, BMPWIDTH, BMPHEIGHT, 1);
    display.display();
    tone(BUZZER, 100, 10);
    delay(400);

    display.clearDisplay();
    display.drawBitmap(0, 0, bitmap3, BMPWIDTH, BMPHEIGHT, 1);
    display.display();
    tone(BUZZER, 100, 10);
    delay(500);

    display.clearDisplay();
    display.drawBitmap(0, 0, bitmap, BMPWIDTH, BMPHEIGHT, 1);
    display.display();
    tone(BUZZER, 100, 10);
    delay(600);

    display.clearDisplay();
    display.drawBitmap(0, 0, bitmap3, BMPWIDTH, BMPHEIGHT, 1);
    display.display();
    tone(BUZZER, 100, 10);
    delay(800);

    display.clearDisplay();
    display.drawBitmap(0, 0, bitmap2, BMPWIDTH, BMPHEIGHT, 1);
    display.display();
    tone(BUZZER, 100, 10);
    delay(1000);

    display.clearDisplay();
    display.drawBitmap(0, 0, bitmap, BMPWIDTH, BMPHEIGHT, 1);
    display.display();
    tone(BUZZER, 100, 10);
    delay(1200);

    display.clearDisplay();
    display.drawBitmap(0, 0, bitmap3, BMPWIDTH, BMPHEIGHT, 1);
    display.display();
    tone(BUZZER, 100, 10);
    delay(1200);

    char val = '0' + random(1,6);
    
    printOnSevenSeg(val);
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
  }
  
  for(int i = 0; i < 8; i++)
    seg.digitalWrite(i, bitRead(data, 7 - i));  
}
