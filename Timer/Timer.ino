/*  TME EDUCATION
 *  Timer
 *  v0.1.0
 *  -------------
 *  Description
 */ 
#define PROJECT_NAME "Timer"
#define VERSION "v0.1.0"

#include "includes.h"
#include "graphics/logoTmeEducation.h"
////////CONSTANTS////////
//In this section, all constants resulting from the prototype board design are set
#define KEY_CENTER 8
#define BUZZER 2
#define LED 13

////////MODIFIERS////////
//In this section there are constants whose modification will affect the operation of our plate


////////DECLARATIONS////////
//This section prepares variables that are responsible for the individual components on the board
hd44780_I2Cexp lcd(0x20, I2Cexp_MCP23008, 7, 6, 5, 4, 3, 2, 1, HIGH);
Adafruit_SSD1306 display(0);
int min, sec, milis;
unsigned long startTime;
boolean stoper = false, s1 = false, s2 = false;
int sMin1, sSec1, sMilis1, sMin2, sSec2, sMilis2;

void setup(){
  lcd.begin(16, 2);
  intro(lcd);

  display.begin(0x2, 0x3C, false);
  display.setTextColor(1);

  pinMode(KEY_CENTER, INPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(LED, OUTPUT);
  display.clearDisplay();
  display.drawBitmap(0, 0, logoTmeEducation, 128, 64, 1);
  display.display();
  lcd.print("press center");
  lcd.setCursor (0,1);
  lcd.print (" button to start");

}

void loop(){
  if(stoper)
    display.clearDisplay();
    
  calculateTime();

  if(digitalRead(KEY_CENTER)){
    beep();
    if(stoper == false){
      stoper = true;
      s1 = false;
      s2 = false;
      startStoper();
    }else if(s1 == false){
      s1 = true;
      sMin1 = min;
      sSec1 = sec;
      sMilis1 = milis;
    } else if( s2 == false){
      s2 = true;
      sMin2 = min;
      sSec2 = sec;
      sMilis2 = milis;
    } else {
      stoper = false;
      drawTime();
    }
    while(digitalRead(KEY_CENTER))
      delay(100);
  }
  
  if(stoper)
    drawTime();
    
  drawSubtimes();


    
  display.display();
  delay(10);
}

void drawTime(){
  drawMin();
  drawSec();
  drawMilis();
}

void drawMin(){
  display.setCursor(25, 0);
  display.setTextSize(3);
  if(min < 10)
    display.print("0");
  display.print(min);
  if(sec%2 == 0)
    display.print(":");
}

void drawSec(){
  display.setCursor(78, 0);
  display.setTextSize(3);
  if(sec < 10)
    display.print("0");
  display.print(sec);
}

void drawMilis(){
  display.setCursor(116, 7);
  display.setTextSize(2);
  display.print(milis);
}

void calculateTime(){
  milis = (millis() - startTime) % 1000 / 100;
  sec = (millis() - startTime) / 1000 % 60;
  min = (millis() - startTime) / 1000 / 60 % 60;
}

void startStoper(){
  startTime = millis();
}

void drawSubtimes(){
  if(s1)
    drawFirstSubtime();
  if(s2)
    drawSecondSubtime();
}

void drawFirstSubtime(){
  display.setCursor(0, 25);
  display.setTextSize(2);

  display.print("loop-");
  
  if(sMin1 < 10)
    display.print("0");
  display.print(sMin1);
  display.print(":");

  if(sSec1 < 10)
    display.print("0");
  display.print(sSec1);

  display.setCursor(120, 32);
  display.setTextSize(1);
  display.print(sMilis1);
}

void drawSecondSubtime(){
  display.setCursor(0, 45);
  display.setTextSize(2);

  display.print("loop-");
  
  if(sMin2 < 10)
    display.print("0");
  display.print(sMin2);
  display.print(":");

  if(sSec2 < 10)
    display.print("0");
  display.print(sSec2);

  display.setCursor(120, 52);
  display.setTextSize(1);
  display.print(sMilis2);
}

void beep(){
  digitalWrite(BUZZER, HIGH);
  digitalWrite(LED, HIGH);
  delay(10);
  digitalWrite(BUZZER, LOW);
  digitalWrite(LED, LOW);
}
