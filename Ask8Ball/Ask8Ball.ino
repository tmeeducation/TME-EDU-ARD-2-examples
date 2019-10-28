/*  TME EDUCATION
 *  8Ball
 *  v0.1.1
 *  -------------
 *  Using this program you can ask for everything.
 */ 
#define PROJECT_NAME "8Ball"
#define VERSION "v0.1.1"

#include "includes.h"
#include "8ball.h"
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

void setup(){
  lcd.begin(16, 2);
  intro(lcd);
  pinMode(KEY_CENTER, INPUT);
  pinMode(BUZZER, OUTPUT);
  
  display.begin(0x2, 0x3C, false);
  display.clearDisplay();
  display.display();

  lcd.clear();
  lcd.print("  Press center");
  lcd.setCursor(0, 1);
  lcd.print("     to ask");

  display.setTextColor(1); 
  display.setTextSize(2);

  randomSeed(analogRead(0));
}

void loop(){
  if(digitalRead(KEY_CENTER)){
    display.clearDisplay();
    display.fillRect(0, 0, 128, 64, 1);
    display.drawBitmap(30 + random(0, 30), -15 + random(0, 30), bitmap, BMPWIDTH, BMPHEIGHT, 0);
    display.display();
    tone(BUZZER, 100, 10);
    delay(100);

    display.clearDisplay();
    display.fillRect(0, 0, 128, 64, 1);
    display.drawBitmap(30 + random(0, 30), -15 + random(0, 30), bitmap, BMPWIDTH, BMPHEIGHT, 0);
    display.display();
    tone(BUZZER, 100, 10);
    delay(200);

    display.clearDisplay();
    display.fillRect(0, 0, 128, 64, 1);
    display.drawBitmap(30 + random(0, 30), -15 + random(0, 30), bitmap, BMPWIDTH, BMPHEIGHT, 0);
    display.display();
    tone(BUZZER, 100, 10);
    delay(300);

    display.clearDisplay();
    display.fillRect(0, 0, 128, 64, 1);    
    display.drawBitmap(30 + random(0, 30), -15 + random(0, 30), bitmap, BMPWIDTH, BMPHEIGHT, 0);
    display.display();
    tone(BUZZER, 100, 10);
    delay(400);

    display.clearDisplay();
    display.fillRect(0, 0, 128, 64, 1);
    display.drawBitmap(30 + random(0, 30), -15 + random(0, 30), bitmap, BMPWIDTH, BMPHEIGHT, 0);
    display.display();
    tone(BUZZER, 100, 10);
    delay(600);

    display.clearDisplay();
    display.fillRect(0, 0, 128, 64, 1);
    display.drawBitmap(30 + random(0, 30), -15 + random(0, 30), bitmap, BMPWIDTH, BMPHEIGHT, 0);
    display.display();
    tone(BUZZER, 100, 10);
    delay(800);

    display.clearDisplay();
    display.fillRect(0, 0, 128, 64, 1);
    display.drawBitmap(30 + random(0, 30), -15 + random(0, 30), bitmap, BMPWIDTH, BMPHEIGHT, 0);
    display.display();
    tone(BUZZER, 100, 10);
    delay(1000);

    display.clearDisplay();
    display.fillRect(0, 0, 128, 64, 1);
    display.drawBitmap(30 + random(0, 30), -15 + random(0, 30), bitmap, BMPWIDTH, BMPHEIGHT, 0);
    display.display();
    tone(BUZZER, 100, 10);
    delay(1000);

    display.clearDisplay();
    display.fillRect(0, 0, 128, 64, 1);
    display.drawBitmap(30, 0, bitmap, BMPWIDTH, BMPHEIGHT, 0);
    display.display();
    tone(BUZZER, 100, 10);
    delay(1500);

    display.clearDisplay();
    display.setCursor(0, 0);
    switch(random(1, 10)){
      case 1: display.print("Without   a doubt."); break;
      case 2: display.print("As I      see it,   Yes."); break;
      case 3: display.print("Don't     count on  it."); break;
      case 4: display.print("Reply hazy try again."); break;
      case 5: display.print("Signs     point to  yes."); break;
      case 6: display.print("Yes       definitely."); break;
      case 7: display.print("Ask again."); break;
      case 8: display.print("My reply  is no."); break;
      case 9: display.print("You may   rely on   it."); break;
    }
    display.display();
  }
}
