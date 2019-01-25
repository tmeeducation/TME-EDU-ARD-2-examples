
/* Requied libraries:
 *  - hd44780 by Bill Perry
 *  - Adafriut_SSD1306
 *  - Adafriut_GFX
 *  - Adafriut_NEoPixel
 */

 /* 
  *  BUTTONS:
  *  UP:      light RED(RGB) LED 
  *  DOWN:    light BLUE(RGB) LED
  *  LEFT:    light BLUE LED
  *  RIGHT:   make some noise (buzzer)
  *  CENTER:  light GREEN(RGB) LED
  *  
  * ADDRESSABLE LEDs (WS2812):
  *   [0] - random color
  *   [1-4] - PCB backlight (BLUE)
  */
  
#include <SoftwareSerial.h>

#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h>

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(0);
//#define LOGO16_GLCD_HEIGHT 16 
//#define LOGO16_GLCD_WIDTH  16 

#include <Adafruit_NeoPixel.h>

#include "Adafruit_MCP23008.h"

#define IR_PIN 3
#include <RC5.h>

const int LCD_ROWS = 2;
const int LCD_COLS = 16;

int LED1 = 13;
int LED3_R = 9;
int LED3_G = 10;
int LED3_B = 11;
int LED_SERIAL = 12;

#define NUMPIXELS 5 // number of WS2812 LEDs in string
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, LED_SERIAL, NEO_GRB + NEO_KHZ800);

Adafruit_MCP23008 mcp;

RC5 rc5(IR_PIN); // IR receiver
byte addr; 
byte cmd;
byte tog;

int SW_LEFT = 4;
int SW_RIGHT = 7;
int SW_UP = 6;
int SW_DOWN = 5;
int SW_ENTER = 8;

int BUZZ = 2;
int IRREC = 3;
int LIGHT = A3;
int TEMP = A2; 
int ROT = A1;
int MIC = A0;

int c1, c2, c3;
int cmax = 31;

/* 7-segment digits map */
uint8_t seg7[11] = {
  B11111100, // 0
  B01100000, // 1
  B11011010, // 2
  B11110010, // 3
  B01100110, // 4
  B10110110, // 5
  B10111110, // 6
  B11100000, // 7
  B11111110, // 8
  B11110110, // 9
  B01100001  // 1. (10)
};


hd44780_I2Cexp lcd(0x20, I2Cexp_MCP23008,7,6,5,4,3,2,1,HIGH);


void setup() {

  Serial.begin(9600); 

  /* initialize WS2812 LED string*/
  pixels.begin();
  
  c1 = random(cmax);
  c2 = random(cmax);
  c3 = random(cmax);

  /* PCB backlight */
  for(int k=1;k<NUMPIXELS;k++){
    pixels.setPixelColor(k, pixels.Color(0,0,100));
    pixels.show();
  }

  /* initialize expander for 7-seg display */
  mcp.begin(0x4); // offset above 0x20 (lowest address)
  mcp.pinMode(0, OUTPUT);
  mcp.pinMode(1, OUTPUT);
  mcp.pinMode(2, OUTPUT);
  mcp.pinMode(3, OUTPUT);
  mcp.pinMode(4, OUTPUT);
  mcp.pinMode(5, OUTPUT);
  mcp.pinMode(6, OUTPUT);
  mcp.pinMode(7, OUTPUT);
  
  pinMode(LED1, OUTPUT);
  pinMode(LED3_R, OUTPUT);
  pinMode(LED3_G, OUTPUT);
  pinMode(LED3_B, OUTPUT);
  pinMode(BUZZ, OUTPUT);

  pinMode(SW_LEFT , INPUT);
  pinMode(SW_RIGHT , INPUT);
  pinMode(SW_UP , INPUT);
  pinMode(SW_DOWN , INPUT);

  pinMode(LIGHT, INPUT);
  pinMode(TEMP, INPUT);
  pinMode(ROT, INPUT);
  pinMode(IRREC, OUTPUT);


  digitalWrite(LED1, LOW);
  digitalWrite(LED3_R, LOW);
  digitalWrite(LED3_G, LOW);
  digitalWrite(LED3_B, LOW);

  if( lcd.begin(LCD_COLS, LCD_ROWS)){
  }

  lcd.print("   tme.eu ");
//  lcd.setCursor(0, 1);
//  lcd.print("Electronic components ");

  /* OLED TEST */
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C, false);
  delay(2000);
  display.clearDisplay();
  display.setTextColor(WHITE);

  /* draw UI on OLED */
  display.clearDisplay();
  display.setCursor(0,1);
  display.println("POTENTIOMETER:");
  display.setCursor(0,16);
  display.println("LIGHT SENSOR:");
  display.setCursor(0,31);
  display.println("MICROPHONE:");
  display.setCursor(0,46);
  display.println("TEMP. SENSOR:");

  display.drawRect(0, 10+15*0-1, 128, 5, 1);
  display.drawRect(0, 10+15*1-1, 128, 5, 1);
  display.drawRect(0, 10+15*2-1, 128, 5, 1);
  display.drawRect(0, 10+15*3-1, 128, 5, 1);
  display.display();    
}
void loop() {

  int ctemp;
  int crot;
  int clight;

  delay(500);

  /* light LED after button press */
  while(1) {
    for (int i=0; i<1; i++) {
      if(digitalRead(SW_LEFT))
        digitalWrite(LED1, HIGH);
      else 
        digitalWrite(LED1, LOW);
  
      if(digitalRead(SW_UP))
        digitalWrite(LED3_R, HIGH);
      else
        digitalWrite(LED3_R, LOW);
  
      if(digitalRead(SW_ENTER))
        digitalWrite(LED3_G, HIGH);
      else 
        digitalWrite(LED3_G, LOW);
  
      if(digitalRead(SW_DOWN))
        digitalWrite(LED3_B, HIGH);
      else 
        digitalWrite(LED3_B, LOW);
  
      if(digitalRead(SW_RIGHT))
        digitalWrite(BUZZ, HIGH);
      else 
        digitalWrite(BUZZ, LOW);
      delay(50);
    }

    crot =   (int)(((float)analogRead(ROT)/1023.0)*100.0);      // read potentiometer value
    clight = (int)(((float)analogRead(LIGHT)/1023.0)*100.0);    // read light sensor value
    ctemp = (int)(analogRead(TEMP)*0.125 - 22.0);               // read temperature sensor value

    Serial.print("R: "); Serial.print(crot);
    Serial.print("%, L: "); Serial.print(clight);
    Serial.print("%, T: "); Serial.print(ctemp);Serial.print("*C\n");

//    /* LCD */
      lcd.clear();
      lcd.print("R: "); lcd.print(crot); lcd.print("%");
      lcd.setCursor(8, 0);
      lcd.print("L: "); lcd.print(clight); lcd.print("%");
      lcd.setCursor(0, 1);
      lcd.print("T: "); lcd.print(ctemp); lcd.print((char)223); lcd.print("C");

    /* OLED */
    int proc;    
    proc = (int)(analogRead(ROT)/1024.0*100.0);
    draw_bar(1, proc, 1);
    proc = (int)(analogRead(LIGHT)/1024.0*100.0);
    draw_bar(2, proc, 1);
    proc = (int)(analogRead(MIC)/1024.0*100.0);
    draw_bar(3, proc, 1);
    proc = (int)(analogRead(TEMP)/1024.0*100.0);
    draw_bar(4, proc, 1);
    display.display();

    
    /* show first digit of potentiometer value on 7-segment display */
    int temp = (int)((float)analogRead(ROT)/102.3);
    for (int j=0; j<8; j++) 
      mcp.digitalWrite(j, (bool)bitRead(seg7[temp], 7-j));
    

    /* WS2812 */
    pixels.setPixelColor(0, pixels.Color(c1,c2,c3));
    pixels.show();
    // set random color
    if ((random(2) && (c1 < (cmax-1))) || (c1 == 0)) c1+=1; else c1-=1;
    if ((random(2) && (c2 < (cmax-1))) || (c2 == 0)) c2+=1; else c2-=1;
    if ((random(2) && (c3 < (cmax-1))) || (c3 == 0)) c3+=1; else c3-=1;

    if (rc5.read(&tog, &addr, &cmd))
      {
        Serial.print("A:");
        Serial.print(addr);
        Serial.print(" K:");
        Serial.print(cmd);
        Serial.print(" T:");
        Serial.println(tog);
        Serial.print("\n");
      }

  } 
}

// display bar
void draw_bar(int line, int p, int col) {
  uint8_t color = 1;
  int split = (int)((display.width()-2) * p/100.0);
  display.fillRect(1, 10+15*(line-1), split, 3, 1);
  display.fillRect(split+1, 10+15*(line-1), display.width()-2-split, 3, 0);
}


