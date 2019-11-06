/*  TME EDUCATION
 *  Snake
 *  v1.0.0
 *  -------------
 *  A snake game using an display display
 */ 
#define PROJECT_NAME "Snake"
#define VERSION "v1.0.0"

#include "includes.h"
////////CONSTANTS////////
//In this section, all constants resulting from the prototype board design are set
#define KEY_LEFT 4
#define KEY_DOWN 5
#define KEY_UP 6
#define KEY_RIGHT 7 
#define KEY_CENTER 8
#define POTENTIOMETER 1
#define BUZZER 2
#define LED 13

////////MODIFIERS////////
//In this section there are constants whose modification will affect the operation of our plate
#define DISPLAY_HEIGHT 64
#define DISPLAY_WIDTH 128
#define CANVAS_HEIGHT 9
#define CANVAS_WIDTH 18
#define SEGMENT_SIZE 3
#define MARGIN_TOP 11 //max 11
#define MARGIN_LEFT 21 //max 21

////////DECLARATIONS////////
//This section prepares variables that are responsible for the individual components on the board
hd44780_I2Cexp lcd(0x20, I2Cexp_MCP23008, 7, 6, 5, 4, 3, 2, 1, HIGH);
Adafruit_SSD1306 display(DISPLAY_WIDTH, DISPLAY_HEIGHT, &Wire, 4);

uint8_t headX = 4;
uint8_t headY = 4;
uint8_t tailX[31] = {};
uint8_t tailY[31] = {};
uint8_t foodX = 1;
uint8_t foodY = 1;
uint8_t snakeSize = 0;
unsigned long lastTime;
enum {
  left,
  right,
  up,
  down,
} direction, lastDirection;

void setup(){
  lcd.begin(16, 2);
 intro(lcd);

  pinMode(KEY_LEFT, INPUT);
  pinMode(KEY_DOWN, INPUT);
  pinMode(KEY_UP, INPUT);
  pinMode(KEY_RIGHT, INPUT);
  pinMode(KEY_CENTER, INPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(LED, OUTPUT);
  
  display.begin(0x2, 0x3C, false);
  display.setTextColor(1);
  display.setTextSize(2);
  display.clearDisplay();
  drawCanvas();
  createFood();
  display.display();

  lastTime = millis();
}

void loop(){
  if(digitalRead(KEY_LEFT) && lastDirection != right){
    direction = left;
  }
  if(digitalRead(KEY_RIGHT) && lastDirection != left){
    direction = right;
  }
  if(digitalRead(KEY_UP) && lastDirection != down){
    direction = up;
  }
  if(digitalRead(KEY_DOWN) && lastDirection != up){
    direction = down;
  }

  int pot = analogRead(POTENTIOMETER);
  int speedUp = 0;
  if(pot > 950){
    if(snakeSize < 7)
      speedUp += snakeSize * 100;
    else
      speedUp += snakeSize * 25 + 600;    
  }
  if(lastTime + pot - speedUp < millis()){
    lastDirection = direction;
    
    if(direction == left){
      if(headX == 0){
        headX = CANVAS_WIDTH;
      }
      headX--;
    }
    if(direction == right){      
      headX++;
      if(headX == CANVAS_WIDTH){
        headX = 0;
      }
    }
    if(direction == up){
      if(headY == 0){
        headY = CANVAS_HEIGHT;
      }
      headY--;
    }
    if(direction == down){
      headY++;
      if(headY == CANVAS_HEIGHT){
        headY = 0;
      }
    }

    drawSnake();
    lastTime = millis();
  }
}

void drawSnake(){
  drawSegment(tailX[snakeSize], tailY[snakeSize], 0);
  
  for(int i = snakeSize; i > 0; i--){
    if(tailX[i] == headX && tailY[i] == headY && i != snakeSize || snakeSize == 30){
      String endingText = snakeSize == 30 ? "YOU WIN" : "GAME OVER";
      snakeSize = 0;
      display.clearDisplay();      
      display.setCursor(10, 30);      
      display.println(endingText);
      display.display();
      play(0, 120);
      play(1175, 120);
      play(1047, 480);
      delay(4000);
      display.clearDisplay();
      drawCanvas();
      createFood();
    }
    tailX[i] = tailX[i - 1];
    tailY[i] = tailY[i - 1];
  }

  tailX[0] = headX;
  tailY[0] = headY;

  if(headX == foodX && headY == foodY){
    createFood();
    snakeSize++;
  }

  clearScore();
  display.setCursor(0, 0);
  display.println(snakeSize);
  
  drawSegment(headX, headY, 1);
  display.display();
}

void createFood(){
  boolean drawAgain = true;

  drawFood(foodX, foodY, 0);
  drawCanvas();
  beep();
  while(drawAgain){
    drawAgain = false;
    foodX = random(0, CANVAS_WIDTH);
    foodY = random(0, CANVAS_HEIGHT);
    
    for(int i = 0; i < snakeSize; i++){
      if(tailX[i] == foodX && tailY[i] == foodY){
        drawAgain = true;
      }
    }
  }

  drawFood(foodX, foodY, 1);
}

void drawFood(uint8_t x, uint8_t y, uint8_t color){
  display.drawRoundRect(MARGIN_LEFT + 0 + x * SEGMENT_SIZE * 2, // x
                     MARGIN_TOP + 0 + y * SEGMENT_SIZE * 2, // y
                     5, // width
                     5, // height
                     0, // radius
                     color); // color
}

void drawSegment(uint8_t x, uint8_t y, uint8_t color){
  display.fillRoundRect(MARGIN_LEFT + 1 + x * SEGMENT_SIZE * 2, // x
                     MARGIN_TOP + 1 + y * SEGMENT_SIZE * 2, // y
                     3, // width
                     3, // height
                     0, // radius
                     color); // color
}

void drawCanvas(){
  display.drawRoundRect(MARGIN_LEFT, // x
                     MARGIN_TOP, // y
                     CANVAS_WIDTH * SEGMENT_SIZE * 2 - SEGMENT_SIZE + 2, // width
                     CANVAS_HEIGHT * SEGMENT_SIZE * 2 - SEGMENT_SIZE + 2, // height
                     0, // radius
                     1); // color
}

void clearScore(){
  display.fillRoundRect(0, // x
                     0, // y
                     22, // width
                     22, // height
                     0, // radius
                     0); // color
  drawCanvas();
}

void beep(){
  digitalWrite(BUZZER, HIGH);
  digitalWrite(LED, HIGH);
  delay(10);
  digitalWrite(BUZZER, LOW);
  digitalWrite(LED, LOW);
}

void play(int freq, int duration){
  tone(BUZZER, freq, duration);
  delay(duration);
}
