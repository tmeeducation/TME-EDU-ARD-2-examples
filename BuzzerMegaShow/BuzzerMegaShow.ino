/*  TME EDUCATION
 *  BuzzerMegaShow
 *  v0.1.0
 *  -------------
 *  This program will play everething in RTTTL format
 */ 
#define PROJECT_NAME "BuzzerMegaShow"
#define VERSION "v0.1.0"

#include "includes.h"
////////CONSTANTS////////
//In this section, all constants resulting from the prototype board design are set
#define LED_1 13
#define LED_2 9
#define BUZZER 2
#define KEY_LEFT 4
#define KEY_RIGHT 7
#define KEY_CENTER 8

////////MODIFIERS////////
//In this section there are constants whose modification will affect the operation of our plate

////////DECLARATIONS////////
//This section prepares variables that are responsible for the individual components on the board
hd44780_I2Cexp lcd(0x20, I2Cexp_MCP23008, 7, 6, 5, 4, 3, 2, 1, HIGH);
Adafruit_SSD1306 display(0);
boolean status = false;
uint8_t song = 0;

void setup(){
  lcd.begin(16, 2);
  intro(lcd);

  display.begin(0x2, 0x3C, false);
  display.clearDisplay();

  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  pinMode(KEY_LEFT, INPUT);
  pinMode(KEY_RIGHT, INPUT);
  pinMode(KEY_CENTER, INPUT);

  setPrevious(true);
  setPlay(true);
  setNext(true);
  setPrevious(false);
  setPlay(false);
  setNext(false);
  chooseDescription(song);
}

void loop(){
  if(digitalRead(KEY_LEFT)){
    if(song <= 0)
      song = 7;
    song--;

    setPrevious(true);
    while(digitalRead(KEY_LEFT)){
      
    }
    setPrevious(false);
    chooseDescription(song);    
  }

  if(digitalRead(KEY_RIGHT)){
    if(song >= 6)
      song = -1;
    song++;

    setNext(true);
    while(digitalRead(KEY_RIGHT)){
      
    }
    setNext(false);
    chooseDescription(song);    
  }

  if(digitalRead(KEY_CENTER)){
    setPlay(true);
    while(digitalRead(KEY_RIGHT)){
      
    }    
    chooseSong(song);
    setPlay(false);
  }
}

void chooseDescription(uint8_t song){
  switch(song){
    case 0:
      printText("Indiana Jones");
      break;
    case 1:
      printText("Take on me");
      break;
    case 2:
      printText("Star Wars");
      break;
    case 3:
      printText("Back to the Future");
      break;
    case 4:
      printText("Mission Imposible");
      break;
    case 5:
      printText("Barbie Girl");
      break;
    case 6:
      printText("Pink Panther");
      break;
  }
}

void chooseSong(uint8_t song){
  switch(song){
    case 0:
      song0();
      break;
    case 1:
      song1();
      break;
    case 2:
      song2();
      break;
    case 3:
      song3();
      break;
    case 4:
      song4();
      break;
    case 5:
      song5();
      break;
    case 6:
      song6();
      break;
  }
}

void play(int freq, int duration){
  tone(BUZZER, freq, duration);
  
  if(status){
    digitalWrite(LED_1, LOW);
    digitalWrite(LED_2, HIGH);
  }else{
    digitalWrite(LED_1, HIGH);
    digitalWrite(LED_2, LOW);
  }
  status = !status;
  delay(duration);
}

void printText(String text){
  lcd.clear();
  if(text.length() > 16){
    lcd.print(text.substring(0, text.lastIndexOf(" ")));
    lcd.setCursor(0, 1);
    lcd.print(text.substring(text.lastIndexOf(" ") + 1));
  }else{
    lcd.print(text);
  }
  delay(1000);
}

void setPrevious(boolean fill){
  if(fill){
    display.fillTriangle(39, 18,
                      39, 44,
                      13, 31,
                      1);
                    
    display.fillTriangle(26, 18,
                      26, 44,
                      0, 31,
                      1);
  }else{
    display.fillTriangle(39 - 1, 18 + 1,
                      39 - 1, 44 - 1,
                      13 + 1, 31,
                      0);
                      
    display.fillTriangle(26 - 1, 18 + 1,
                      26 - 1, 44 - 1,
                      0 + 1, 31,
                      0);
  }
  display.display();
}

void setPlay(boolean fill){
  if(fill){
    display.fillTriangle(50, 18,
                      50, 44,
                      76, 31,
                      1);
  }else{
    display.fillTriangle(50 + 1, 18 + 1,
                      50 + 1, 44 - 1,
                      76 - 1, 31,
                      0);
  }
  display.display();
}

void setNext(boolean fill){
  if(fill){
    display.fillTriangle(85, 18,
                      85, 44,
                      111, 31,
                      1);
                    
    display.fillTriangle(99, 18,
                      99, 44,
                      125, 31,
                      1);
  }else{
    display.fillTriangle(85 + 1, 18 + 1,
                      85 + 1, 44 - 1,
                      111 - 1, 31,
                      0);
                      
    display.fillTriangle(99 + 1, 18 + 1,
                      99 + 1, 44 - 1,
                      125 - 1, 31,
                      0);
  }
  display.display();
}

void song0(){ // Indiana Jone
//  play(659, 240);
//  play(0, 120);
//  play(698, 120);
//  play(784, 120);
//  play(0, 120);
//  play(1047, 960);
//  play(0, 180);
//  play(587, 240);
//  play(0, 120);
//  play(659, 120);
//  play(698, 960);
//  play(0, 360);
//  play(784, 240);
//  play(0, 120);
//  play(880, 120);
//  play(987, 120);
//  play(0, 120);
//  play(1397, 960);
//  play(0, 240);
//  play(880, 240);
//  play(0, 120);
//  play(987, 120);
//  play(1047, 480);
//  play(1175, 480);
//  play(1319, 480);
//  play(659, 240);
//  play(0, 120);
//  play(698, 120);
//  play(784, 120);
//  play(0, 120);
//  play(1047, 960);
//  play(0, 240);
//  play(1175, 240);
//  play(0, 120);
//  play(1319, 120);
//  play(1397, 1440);
//  play(784, 240);
//  play(0, 120);
//  play(784, 120);
//  play(1319, 360);
//  play(0, 120);
//  play(1175, 240);
//  play(0, 120);
//  play(784, 120);
//  play(1319, 360);
//  play(0, 120);
//  play(1175, 240);
//  play(0, 120);
//  play(784, 120);
//  play(1397, 360);
//  play(0, 120);
//  play(1319, 240);
  play(0, 120);
  play(1175, 120);
  play(1047, 480);
}

void song1(){ // Take on me
  play(740, 187);
  play(740, 187);
  play(740, 187);
  play(587, 187);
  play(0, 187);
  play(493, 187);
  play(0, 187);
  play(659, 187);
  play(0, 187);
  play(659, 187);
  play(0, 187);
  play(659, 187);
  play(830, 187);
  play(830, 187);
  play(880, 187);
  play(987, 187);
  play(880, 187);
  play(880, 187);
  play(880, 187);
  play(659, 187);
  play(0, 187);
  play(587, 187);
  play(0, 187);
  play(740, 187);
  play(0, 187);
  play(740, 187);
  play(0, 187);
  play(740, 187);
  play(659, 187);
  play(659, 187);
  play(740, 187);
  play(659, 187);
  play(740, 187);
  play(740, 187);
  play(740, 187);
  play(587, 187);
  play(0, 187);
  play(493, 187);
  play(0, 187);
  play(659, 187);
  play(0, 187);
  play(659, 187);
  play(0, 187);
  play(659, 187);
  play(830, 187);
  play(830, 187);
  play(880, 187);
  play(987, 187);
  play(880, 187);
  play(880, 187);
  play(880, 187);
  play(659, 187);
  play(0, 187);
  play(587, 187);
  play(0, 187);
  play(740, 187);
  play(0, 187);
  play(740, 187);
  play(0, 187);
  play(740, 187);
  play(659, 187);
  play(659, 187);
}

void song2(){ // Star Wars
  play(0, 166);
  play(740, 166);
  play(740, 166);
  play(740, 166);
  play(987, 999);
  play(1480, 999);
  play(1319, 166);
  play(1245, 166);
  play(1109, 166);
  play(1976, 999);
  play(1480, 499);
  play(1319, 166);
  play(1245, 166);
  play(1109, 166);
  play(1976, 999);
  play(1480, 499);
  play(1319, 166);
  play(1245, 166);
  play(1319, 166);
  play(1109, 999);
  play(740, 166);
  play(740, 166);
  play(740, 166);
  play(987, 999);
  play(1480, 999);
  play(1319, 166);
  play(1245, 166);
  play(1109, 166);
  play(1976, 999);
  play(1480, 499);
  play(1319, 166);
  play(1245, 166);
  play(1109, 166);
  play(1976, 999);
  play(1480, 499);
  play(1319, 166);
  play(1245, 166);
  play(1319, 166);
  play(1109, 666);
}

void song3(){ // Back to the Future
  play(784, 450);
  play(0, 75);
  play(523, 450);
  play(0, 75);
  play(740, 900);
  play(0, 75);
  play(784, 112);
  play(0, 75);
  play(880, 112);
  play(0, 75);
  play(784, 150);
  play(0, 75);
  play(659, 150);
  play(0, 75);
  play(523, 150);
  play(0, 75);
  play(740, 300);
  play(0, 75);
  play(784, 112);
  play(0, 75);
  play(880, 112);
  play(0, 75);
  play(784, 225);
  play(0, 75);
  play(587, 225);
  play(0, 75);
  play(784, 225);
  play(0, 75);
  play(1175, 225);
  play(0, 75);
  play(1175, 450);
  play(0, 75);
  play(1109, 300);
  play(0, 75);
  play(987, 112);
  play(0, 75);
  play(1109, 112);
  play(0, 75);
  play(1175, 900);
}

void song4(){ // Mission Imposible
  play(1175, 78);
  play(1245, 78);
  play(1175, 78);
  play(1245, 78);
  play(1175, 78);
  play(1245, 78);
  play(1175, 78);
  play(1245, 78);
  play(1175, 78);
  play(1175, 78);
  play(1245, 78);
  play(1319, 78);
  play(1397, 78);
  play(1480, 78);
  play(1568, 78);
  play(1568, 157);
  play(0, 315);
  play(1568, 157);
  play(0, 315);
  play(1865, 157);
  play(0, 157);
  play(2093, 157);
  play(0, 157);
  play(1568, 157);
  play(0, 315);
  play(1568, 157);
  play(0, 315);
  play(1397, 157);
  play(0, 157);
  play(1480, 157);
  play(0, 157);
  play(1568, 157);
  play(0, 315);
  play(1568, 157);
  play(0, 315);
  play(1865, 157);
  play(0, 157);
  play(2093, 157);
  play(0, 157);
  play(1568, 157);
  play(0, 315);
  play(1568, 157);
  play(0, 315);
  play(1397, 157);
  play(0, 157);
  play(1480, 157);
  play(0, 157);
  play(1865, 157);
  play(1568, 157);
  play(1175, 1262);
  play(0, 78);
  play(1865, 157);
  play(1568, 157);
  play(1109, 1262);
  play(0, 78);
  play(1865, 157);
  play(1568, 157);
  play(1047, 1262);
  play(932, 157);
  play(1047, 315);
  play(0, 1262);
  play(0, 78);
  play(932, 157);
  play(784, 157);
  play(1480, 1262);
  play(0, 78);
  play(932, 157);
  play(784, 157);
  play(1397, 1262);
  play(0, 78);
  play(932, 157);
  play(784, 157);
  play(1319, 1262);
  play(1245, 157);
  play(1175, 315);
}

void song5(){ // Barbie Girl
  play(830, 240);
  play(659, 240);
  play(830, 240);
  play(1109, 240);
  play(880, 480);
  play(0, 480);
  play(740, 240);
  play(622, 240);
  play(740, 240);
  play(987, 240);
  play(830, 480);
  play(740, 240);
  play(659, 240);
  play(0, 480);
  play(659, 240);
  play(554, 240);
  play(740, 480);
  play(554, 480);
  play(0, 480);
  play(740, 240);
  play(659, 240);
  play(830, 480);
  play(740, 480);
}

void song6(){ // Pink Panther
  play(587, 187);
  play(659, 187);
  play(0, 750);
  play(698, 187);
  play(784, 187);
  play(0, 750);
  play(587, 187);
  play(659, 187);
  play(0, 93);
  play(698, 187);
  play(784, 187);
  play(0, 93);
  play(1047, 187);
  play(987, 187);
  play(0, 93);
  play(587, 187);
  play(659, 187);
  play(0, 93);
  play(987, 187);
  play(880, 750);
  play(0, 750);
  play(880, 93);
  play(784, 93);
  play(659, 93);
  play(587, 93);
  play(659, 750);
}
