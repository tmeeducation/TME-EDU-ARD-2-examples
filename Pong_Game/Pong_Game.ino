/*  TME EDUCATION
 *  Template
 *  v0.0.0
 *  -------------
 *  Description
 */ 
#define PROJECT_NAME "Template"
#define VERSION "v0.0.0"
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define RESET_BTN 4


#include "includes.h"
////////CONSTANTS////////
//In this section, all constants resulting from the prototype board design are set
#define POTENTIOMETER A1
#define BUZZER 2
////////MODIFIERS////////
//In this section there are constants whose modification will affect the operation of our plate


////////DECLARATIONS////////
//This section prepares variables that are responsible for the individual components on the board
hd44780_I2Cexp lcd(0x20, I2Cexp_MCP23008, 7, 6, 5, 4, 3, 2, 1, HIGH);
Adafruit_SSD1306 display(SCREEN_WIDTH,SCREEN_HEIGHT, &Wire, RESET_BTN);

int xVel = 1;
int yVel = 1;
int speed = 3;
bool up = true;
bool right = true;

int p1points = 0;
int p2points = 0;

struct vector{
  int x;
  int y;
}ball, p1, p2;

void setup(){
  lcd.begin(16, 2);
//  intro(lcd);

  display.begin(0x2, 0x3C, false);
  display.clearDisplay();
  display.display();
  
  pinMode(BUZZER, OUTPUT);
  
  p1.x = 5;
  p1.y = 0;
  
  p2.x = 123;
  p2.y = 0;

  ball.x = 10;
  ball.y = random(20);

  display.setTextColor(1); 
  display.setTextSize(2);
}

void loop(){
  ballPhysics();
  p1Physics();
  p2Physics();
  
  display.clearDisplay();
  drawPlayers();
  drawBall();
  drawPoints();
  display.display();
  
  delay(50);
  speed = p2points + 3;
}


void ballPhysics(){
  if(ball.x <= 0){
    right = true;
    p2points++;
    xVel = -xVel;
  }
  if(ball.x >= 127){
    right = false;
    p1points++;
    xVel = -xVel;
  }
  ///////////
  if(ball.y <= 0){
    yVel = -yVel;
    up = false;    
  }
  if(ball.y >= 63){
    yVel = -yVel;
    up = true;    
  }
////////////

    

//////////////////
  if(ball.x <= 8){
    
    if(ball.y >= p1.y && ball.y < p1.y + 5){
      beep();
      yVel = -1;
      xVel = 1;
    }
    if(ball.y >= p1.y + 5 && ball.y < p1.y + 10){
      beep();
      yVel = 0;
      xVel = 1;
    }
    if(ball.y >= p1.y + 10 && ball.y < p1.y + 15){
      beep();
      yVel = 1;
      xVel = 1;
    }
  }
  if(ball.x >= 120){
    
    if(ball.y >= p2.y && ball.y < p2.y + 5){
      beep();
      yVel = -1;
      xVel = -1;
    }
    if(ball.y >= p2.y + 5 && ball.y < p2.y + 10){
      beep();
      yVel = 0;
      xVel = -1;
    }
    if(ball.y >= p2.y + 10 && ball.y < p2.y + 15){
      beep();
      yVel = 1;
      xVel = -1;
    }
  }

  //////////////
  ball.y += yVel * speed;

    ball.x += xVel * speed;
}

void p1Physics(){
  if(p1.y < ball.y -7){
    p1.y += 2;
  }else{
    p1.y -= 2;
  }
}

void p2Physics(){
  p2.y = map(analogRead(POTENTIOMETER), 0, 1023, 0, 63);
}

void drawPlayers(){
  display.fillRect(p1.x, p1.y, 3, 15, 1);
  display.fillRect(p2.x, p2.y, 3, 15, 1);
}

void drawBall(){
  display.fillCircle(ball.x, ball.y, 3, 1);
}

void drawPoints(){
  display.setCursor(30, 5);
  display.print(p1points);
  display.setCursor(90, 5);
  display.print(p2points);
}

void beep(){
  digitalWrite(BUZZER, HIGH);
  delay(10);
  digitalWrite(BUZZER, LOW);
}
