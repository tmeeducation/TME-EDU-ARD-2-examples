/*  TME EDUCATION
 *  Paint
 *  v0.0.0
 *  -------------
 *  Description
 */ 
#define PROJECT_NAME "Paint"
#define VERSION "v0.0.0"

#include "includes.h"
////////CONSTANTS////////
//In this section, all constants resulting from the prototype board design are set
#define KEY_LEFT 4
#define KEY_DOWN 5
#define KEY_UP 6
#define KEY_RIGHT 7
#define KEY_CENTER 8
#define POTENTIOMETER 1

////////MODIFIERS////////
//In this section there are constants whose modification will affect the operation of our plate
#define DISPLAY_HEIGHT 64
#define DISPLAY_WIDTH 128

////////DECLARATIONS////////
//This section prepares variables that are responsible for the individual components on the board
hd44780_I2Cexp lcd(0x20, I2Cexp_MCP23008, 7, 6, 5, 4, 3, 2, 1, HIGH);
Adafruit_SSD1306 display(DISPLAY_WIDTH, DISPLAY_HEIGHT, &Wire, 4);
unsigned long screenTime;
unsigned long blinkTime;

//uint8_t bitmapp[1024];

struct xy{
  int x;
  int y;
} cursor;

enum opt{
  SETTINGS = 0,
  DRAW
} option;

enum drawingOpt{
  TOOL = 0,
  SIZE
} drawingOption = TOOL;

enum toolsOpt{
  PEN = 0,
  SPRAY,
  ERASER
} toolType = PEN;

int sizeOfTool = 1;

bool blink = true;

void setup(){
//  Serial.begin(9600);
//  Serial.println("a");
  lcd.begin(16, 2);
  intro(lcd);

  pinMode(KEY_LEFT, INPUT);
  pinMode(KEY_DOWN, INPUT);
  pinMode(KEY_UP, INPUT);
  pinMode(KEY_RIGHT, INPUT);
  pinMode(KEY_CENTER, INPUT);

  display.begin(0x2, 0x3C, false);
  display.clearDisplay();
  display.display();

  cursor.x = 0;
  cursor.y = 0;
//  Serial.println("b");
//  for(int i = 0; i < 1024; i++){
//    bitmapp[i] = 0;
//  }
//  Serial.println("c");
//  Serial.println("SETUP");
//  for(int x = 0; x < 128; x += 5){
//    for(int y = 0; y < 64; y += 5){
//      drawPixelOnBitmap(x, y);
//    }
//  }
//  Serial.println("d");
  
//  display.clearDisplay();
//  display.drawBitmap(0, 0, bitmapp, 128, 64, 1);
//  display.display();
//  drawBitmap(bitmapp);
//  Serial.println("e");
  screenTime = millis();
  blinkTime = millis();

  lcd.clear();
  setupProgramMode();
  setupDrawingOption();
}
/////////////////////////////////////////////////
void loop(){  
  if(screenTime + 20 < millis()){ // SLOW LOOP FOR DRAWING

    // STEROWANIE KURSOREM RYSOWANIA
    if(option == DRAW){
      if(digitalRead(KEY_LEFT)){
        cursor.x--;
        if(cursor.x < 0){
          cursor.x = 0;
        }
      }
      if(digitalRead(KEY_RIGHT)){      
        cursor.x++;
        if(cursor.x > DISPLAY_WIDTH){
          cursor.x = DISPLAY_WIDTH;
        }
      }
      if(digitalRead(KEY_UP)){
        cursor.y--;
        if(cursor.y < 0){
          cursor.y = 0;
        }
      }
      if(digitalRead(KEY_DOWN)){
        cursor.y++;
        if(cursor.y > DISPLAY_HEIGHT){
          cursor.y = DISPLAY_HEIGHT;
        }
      }
    } else if(option == SETTINGS){ // STEROWANIE OPCJAMI RYSOWANIA
      if(digitalRead(KEY_LEFT)){
        drawingOption = (drawingOpt)(drawingOption - 1);
        if(drawingOption < 0)
          drawingOption = (drawingOpt)1;
        delay(200);
      }
      if(digitalRead(KEY_RIGHT)){ 
        drawingOption = (drawingOpt)(drawingOption + 1);
        if(drawingOption > 1)
          drawingOption = (drawingOpt)0;
        delay(200);
      }

      if(digitalRead(KEY_UP)){
        if(drawingOption == TOOL){
          toolType = (toolsOpt)(toolType + 1);
          if(toolType > 2)
            toolType = (toolsOpt)0;
        }else if(drawingOption == SIZE){
          sizeOfTool++;
          if(sizeOfTool > 20)
            sizeOfTool = 20;
        }
        delay(200);
      }
      if(digitalRead(KEY_DOWN)){
        if(drawingOption == TOOL){
          toolType = (toolsOpt)(toolType - 1);
          if(toolType < 0)
            toolType = (toolsOpt)2;
        }else if(drawingOption == SIZE){
          sizeOfTool--;
          if(sizeOfTool < 1)
            sizeOfTool = 1;
        }
        delay(200);
      }

      updateDrawingOption();

    }
    
    // DRAWING DRAWING DRAWING DRAWING DRAWING DRAWING DRAWING DRAWING DRAWING DRAWING DRAWING
    if(digitalRead(KEY_CENTER)){
      if(toolType == PEN){
        pen();
      } else if(toolType == SPRAY){
        spray();
      } else if(toolType == ERASER){
        eraser();
      }
    }
    
    display.display();

    screenTime = millis();    
  }

  // BLINK AND LCD
  if(blinkTime + 500 < millis()){
    if(analogRead(POTENTIOMETER) > 500){
      option = SETTINGS;
      // settings();
    } else {
      option = DRAW;
      // drawing();
    }

    blink = !blink;
    updateProgramMode();

    blinkTime = millis();
  }
}
/////////////////////////////////////////////////////////////////////

void setupDrawingOption(){
  
}

void updateDrawingOption(){
  lcd.setCursor(1, 1);
  if(toolType == PEN){
    lcd.print(" PEN  ");
  } else if(toolType == SPRAY){
    lcd.print("SPRAY ");
  } else if(toolType == ERASER){
    lcd.print("ERASER");
  }

  lcd.setCursor(13, 1);
  if(sizeOfTool < 10)
    lcd.print("0");
  lcd.print(sizeOfTool); 

  if(drawingOption == TOOL){
    lcd.setCursor(12, 1);
    lcd.print(" ");
    lcd.setCursor(15, 1);
    lcd.print(" ");

    lcd.setCursor(0, 1);
    drawBlink('>');
    
    lcd.setCursor(7, 1);
    drawBlink('<');
    
  } else if(drawingOption == SIZE){
    lcd.setCursor(0, 1);
    lcd.print(" ");
    lcd.setCursor(7, 1);
    lcd.print(" ");

    lcd.setCursor(12, 1);
    drawBlink('>');       

    lcd.setCursor(15, 1);
    drawBlink('<');
  }
}

void setupProgramMode(){
  lcd.setCursor(1, 0);
  lcd.print("settings");

  lcd.setCursor(11, 0);
  lcd.print("draw");
}

void updateProgramMode(){
  lcd.setCursor(0, 1);
  lcd.print(" ");
  lcd.setCursor(7, 1);
  lcd.print(" ");
  lcd.setCursor(12, 1);
  lcd.print(" ");
  lcd.setCursor(15, 1);
  lcd.print(" ");

  lcd.setCursor(10, 00);
  lcd.print(" ");
  lcd.setCursor(15, 0);
  lcd.print(" ");
  lcd.setCursor(0, 0);
  lcd.print(" ");
  lcd.setCursor(9, 0);
  lcd.print(" ");

  if(option == SETTINGS){
    lcd.setCursor(0, 0);
    drawBlink('>');

    lcd.setCursor(9, 0);
    drawBlink('<');
  } else if(option == DRAW){
    lcd.setCursor(10, 00);
    drawBlink('>');

    lcd.setCursor(15, 0);
    drawBlink('<');
  }
}

void drawBlink(char character){
  if(blink){
    lcd.print(character);
  } else {
    lcd.print(" ");
  }
}

void pen(){
  display.fillCircle(cursor.x, cursor.y, sizeOfTool, 1);
}

void spray(){
  display.drawPixel(cursor.x + random(sizeOfTool) - sizeOfTool / 2, cursor.y + random(sizeOfTool) - sizeOfTool / 2, 1);
  display.drawPixel(cursor.x + random(sizeOfTool) - sizeOfTool / 2, cursor.y + random(sizeOfTool) - sizeOfTool / 2, 1);
  display.drawPixel(cursor.x + random(sizeOfTool) - sizeOfTool / 2, cursor.y + random(sizeOfTool) - sizeOfTool / 2, 1);
  display.drawPixel(cursor.x + random(sizeOfTool) - sizeOfTool / 2, cursor.y + random(sizeOfTool) - sizeOfTool / 2, 1);
}

void eraser(){
  display.fillRect(cursor.x - sizeOfTool, cursor.y - sizeOfTool, sizeOfTool * 2, sizeOfTool * 2, 0);
}
