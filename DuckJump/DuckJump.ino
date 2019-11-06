/*  TME EDUCATION
 *  FrogJump
 *  v0.0.0
 *  -------------
 *  Description
 */ 
#define PROJECT_NAME "DuckJump"
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
#define RESET_BTN 4

////////MODIFIERS////////
//In this section there are constants whose modification will affect the operation of our plate
#define DISPLAY_HEIGHT 64
#define DISPLAY_WIDTH 128

#define LANE_WIDTH 10

#define LINE_LENGTH 12

#define COLOR_WHITE 1
#define COLOR_BLACK 0


////////DECLARATIONS////////
//This section prepares variables that are responsible for the individual components on the board
hd44780_I2Cexp lcd(0x20, I2Cexp_MCP23008, 7, 6, 5, 4, 3, 2, 1, HIGH);
Adafruit_SSD1306 display(DISPLAY_WIDTH,DISPLAY_HEIGHT, &Wire, RESET_BTN);

const uint8_t loadedPickupBitmap[] PROGMEM = {0x3f,0x80, 0x22,0x9C, 0x42,0xBE, 0xBE,0xFF, 0x82,0x01, 0x82,0x01, 0x7F,0xFF, 0x38,0x1C};
const uint8_t pickupBitmap[] PROGMEM = {0x3f,0x80, 0x22,0x80, 0x42,0x80, 0xBE,0xFF, 0x82,0x01, 0x82,0x01, 0x7F,0xFF, 0x38,0x1C};
const uint8_t sportCarBitmap[] PROGMEM = {0x00,0x00, 0x03,0xE0, 0x02,0x18, 0x7C,0x0C, 0x80,0x02, 0xB8,0x39, 0x6F,0xEF, 0x38,0x38};
const uint8_t sportCar2Bitmap[] PROGMEM = {0x00,0x00, 0x03,0xE0, 0x04,0x98, 0x7F,0x8C, 0xC0,0xC2, 0xB8,0x39, 0x6F,0xEF, 0x38,0x38};
const uint8_t tirBitmap[] PROGMEM = {0x0F,0xFF,0xFF, 0x12,0x00,0x01, 0x12,0x00,0x01, 0xE2,0x00,0x01, 0x82,0x00,0x00, 0x9A,0xC0,0x0D, 0xE7,0x9F,0xF3, 0x18,0x60,0x0C};

const uint8_t playerBitmap[] PROGMEM = {0x18,0x3C,0x3C,0x42,0xBD,0x81,0x81,0x7E};

struct Vector2{
  int x;
  int y;
  int lane;
};

struct Vehicle{
  Vector2 pos;
  uint8_t speed;
  const uint8_t* bitmap;
  uint8_t width;
  uint8_t height;
  boolean active;
};

struct Player{
  Vector2 pos;
  const uint8_t* bitmap;
  uint8_t width;
  uint8_t height;
  uint8_t jumps;
};

int currMapSize = 0;
int currMapPos = 0;

int nextMapSize = 0;
int nextMapPos = 0;

int numOfVehicles = 0;
int vehicleTimer = 0;
int level = 0;

unsigned long lastVehicleSpawnTime = 0;
unsigned long lastPlayerJumpTime = 0;

// struct Vehicle vehicle1[2] = {{{1,2},3,loadedPickupBitmap, 16, 8},{{20,20},3,loadedPickupBitmap, 16, 8}}; // sport car
// struct Vehicle vehicle2 = {{4,5},6,pickupBitmap, 16, 8}; // pickup
// struct Vehicle vehicle3 = {{4,5},6,sportCarBitmap, 16, 8}; // loaded pickup
// struct Vehicle vehicle4 = {{4,5},6,sportCar2Bitmap, 16, 8}; // loaded pickup
// struct Vehicle vehicle5 = ; // TIR

struct Vehicle vehicles[24] = {  
  {{1,2},5,loadedPickupBitmap, 16, 8, false},
  {{1,2},5,loadedPickupBitmap, 16, 8, false},
  {{1,2},5,loadedPickupBitmap, 16, 8, false},
  {{1,2},5,loadedPickupBitmap, 16, 8, false},
  {{1,2},5,loadedPickupBitmap, 16, 8, false},
  {{1,2},5,loadedPickupBitmap, 16, 8, false},
  {{1,2},5,loadedPickupBitmap, 16, 8, false},
  {{1,2},5,loadedPickupBitmap, 16, 8, false},
  {{1,2},5,loadedPickupBitmap, 16, 8, false},

  {{4,5},4,pickupBitmap, 16, 8, false},
  {{4,5},4,pickupBitmap, 16, 8, false},
  {{4,5},4,pickupBitmap, 16, 8, false},
  {{4,5},4,pickupBitmap, 16, 8, false},
  {{4,5},4,pickupBitmap, 16, 8, false},
  {{4,5},4,pickupBitmap, 16, 8, false},
  
  {{4,5},2,sportCarBitmap, 16, 8, false},
  {{4,5},2,sportCarBitmap, 16, 8, false},
  {{4,5},2,sportCarBitmap, 16, 8, false},
  {{4,5},2,sportCarBitmap, 16, 8, false},

  {{4,5},1,sportCar2Bitmap, 16, 8, false},
  {{4,5},1,sportCar2Bitmap, 16, 8, false},

  {{7,8},7,tirBitmap, 24, 8, false},
  {{7,8},7,tirBitmap, 24, 8, false},
  {{7,8},7,tirBitmap, 24, 8, false}
};

struct Player player = {{60,56},playerBitmap,8,8, 0};

void setup(){
  // Serial.begin(9600);
  randomSeed(analogRead(0));
  lcd.begin(16, 2);
  intro(lcd);

  display.begin(0x2, 0x3C, false);
  display.clearDisplay();
  display.display();
  pinMode(BUZZER, OUTPUT);
  
  // display.drawBitmap(vehicle1[0].pos.x, vehicle1[0].pos.y, vehicle1[0].bitmap, vehicle1[0].width, vehicle1[0].height, COLOR_WHITE);
  // display.drawBitmap(vehicle1[1].pos.x, vehicle1[1].pos.y, vehicle1[1].bitmap, vehicle1[1].width, vehicle1[1].height, COLOR_WHITE);

  // drawStreet(0,4);
  // display.display();
  // delay(1000);
  // display.clearDisplay();
  // display.drawBitmap(player.pos.x, player.pos.y, player.bitmap, player.width, player.height, COLOR_WHITE);
  // display.display();
  // delay(1000);
}
// generujemy mapę, przechodzimy dany poziom (max 5 pasów ruchu), gdy przejdziemy, to kaczka z mapą zjeżdża w dół, aż nie znajdzie się w pozycji wyjściowej,
// wcześniej generujemy nową mapę, losową ilość pasów ruchów, i ustawiamy jej pozycje na tej podstawie.
void loop(){
  lcd.clear();
  lcd.print("level:");
  lcd.print(level);
  // for(int y = -100; y < DISPLAY_HEIGHT; y++){
  //   display.clearDisplay();
  //   display.drawFastHLine(0, 0, DISPLAY_WIDTH, COLOR_WHITE);
  //   display.drawFastHLine(0, DISPLAY_HEIGHT - 1, DISPLAY_WIDTH, COLOR_WHITE);

  //   drawStreet(y, 4);
  //   display.display();
  // }
  
  ///////////////////// ZAŁADOWANIE ETAPU
  // lcd.clear();
  // lcd.print("level: ");
  // lcd.print(level);
  // GENEROWANIE ROZMIARU AKTUALNEJ MAPY
  currMapSize = random(1, 6);

  // GENEROWANIE ROZMIARU NASTĘPNEJ MAPY
  nextMapSize = random(1, 6);

  // GENEROWANIE POZYCJI AKTUALNEJ MAPY
  currMapPos = 0 - ((LANE_WIDTH + 1) * currMapSize + 1 + player.height);

  // GENEROWANIE POZYCJI NASTĘPNEJ MAPY
  nextMapPos = 0 - ((LANE_WIDTH + 1) * nextMapSize + 1 + player.height);

  // DANIE GRACZOWI ODPOWIEDNIEJ ILOSCI KROKÓW
  player.jumps = currMapSize + 1;

  // DANIE GRACZOWI ODPOWIEDNIEGO NUMERU LINII
  player.pos.lane = currMapSize;

  // AKTUALIZACJA POZYCJI GRACZA
  player.pos.x = 60;
  player.pos.y = 56;

  ////////////////////////// ANIMACJA POJAWIANIA SIĘ MAPY
  // GENEROWANIE POJAZDÓW 
  for(int i = 0; i < 4; i++){
    while(true){
        int currVehicleNum = random(0, 24);

        if(vehicles[currVehicleNum].active != true){
          vehicles[currVehicleNum].pos.x = DISPLAY_WIDTH;
          
          // WYBIERANIE TORU DLA POJAZDÓW
          int currVehicleLane = random(0, currMapSize);
          vehicles[currVehicleNum].pos.y = currMapPos + currVehicleLane * (LANE_WIDTH + 1) + 2;
          // vehicles[currVehicleNum].pos.y -= DISPLAY_HEIGHT;
          vehicles[currVehicleNum].pos.lane = currVehicleLane;

          vehicles[currVehicleNum].active = true;
          break;
        }
      }

    for(int j = 0; j < 2; j++)
    for(int k = 0; k < 24; k++){
      if(vehicles[k].active == true){
        vehicles[k].pos.x-=vehicles[k].speed*4;
      }
    }
  }
  // ZJAZD W DÓŁ MAPY
  for(int i = 0; i < DISPLAY_HEIGHT; i++){   
    display.clearDisplay();
    drawStreet(currMapPos++, currMapSize);
    display.drawBitmap(player.pos.x, player.pos.y, player.bitmap, player.width, player.height, COLOR_WHITE);    

    // RYSOWANIE SAMOCHODÓW
    for(int i = 0; i < 24; i++){
      if(vehicles[i].active == true){
        display.drawBitmap(vehicles[i].pos.x, vehicles[i].pos.y++, vehicles[i].bitmap, vehicles[i].width, vehicles[i].height, COLOR_WHITE);
      }
    }
    display.display();
  }
  ////////////////////////// ANIMACJA POJAWIANIA SIĘ MAPY ^^
  display.clearDisplay();

  // NARYSOWANIE AKTUALNEJ MAPY
  drawStreet(currMapPos, currMapSize);

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  ////////////////////////////////////////////////////////////////////////////////////////////////////////////



  
  // NARYSOWANIE GRACZA
  display.drawBitmap(player.pos.x, player.pos.y, player.bitmap, player.width, player.height, COLOR_WHITE);

  lastVehicleSpawnTime = 0;
  ///////////////////// ROZGRYWKA
  while(player.jumps > 0){
    // GENEROWANIE POJAZDU CO OKRESLONY CZAS
    if(lastVehicleSpawnTime < millis()){
      // GENEROWANIE LOSOWEGO POJAZDU
      while(true){
        int currVehicleNum = random(0, 24);

        if(vehicles[currVehicleNum].active != true){
          vehicles[currVehicleNum].pos.x = DISPLAY_WIDTH;
          
          // WYBIERANIE TORU DLA POJAZDÓW
          int currVehicleLane = random(0, currMapSize);
          vehicles[currVehicleNum].pos.y = currMapPos + currVehicleLane * (LANE_WIDTH + 1) + 2;
          vehicles[currVehicleNum].pos.lane = currVehicleLane;

          vehicles[currVehicleNum].active = true;
          break;
        }
      }
      // OBLICZENIE CZASU KOLEJNEGO GENEROWANIA POJAZDU
      lastVehicleSpawnTime = millis() + (1000 / currMapSize * (20 - level));
    }

    // USUWANIE POJAZDÓW POZA MAPĄ
    for(int i = 0; i < 24; i++){
      if(vehicles[i].pos.x < 0 - vehicles[i].width){
        vehicles[i].active = false;
      }
    }

    // PRZESUWANIE POJAZDÓW
    for(int i = 0; i < 24; i++){
      if(vehicles[i].active == true && vehicleTimer % vehicles[i].speed == 0){
        vehicles[i].pos.x--;
      }
    }

    // WYMAZYWANIE POJAZDÓW
    for(int i = 0; i < 24; i++){
      if(vehicles[i].active == true){
        display.fillRect(vehicles[i].pos.x + 1, vehicles[i].pos.y, vehicles[i].width, vehicles[i].height, COLOR_BLACK);
      }
    }

    // RYSOWANIE POJAZDÓW
    for(int i = 0; i < 24; i++){
      if(vehicles[i].active == true){
        display.drawBitmap(vehicles[i].pos.x, vehicles[i].pos.y, vehicles[i].bitmap, vehicles[i].width, vehicles[i].height, COLOR_WHITE);
      }
    }

    //SPRAWDZENIE AKTYWNOSCI GRACZA
    if(digitalRead(KEY_CENTER) && lastPlayerJumpTime < millis()){
      beep();
      // WYMAZANIE GRACZA
      display.fillRect(player.pos.x, player.pos.y, player.width, player.height, COLOR_BLACK);

      // SKOK GRACZA
      player.pos.y -= LANE_WIDTH + 1;
      player.jumps--;
      if(player.jumps == 0)
        level++;
      player.pos.lane--;

      // RYSOWANIE GRACZA
      display.drawBitmap(player.pos.x, player.pos.y, player.bitmap, player.width, player.height, COLOR_WHITE);

      // AKTUALIZACJA CZASU SKOKU
      lastPlayerJumpTime = millis() + 300;
    }

    // SPRAWDZENIE KOLIZJI
    for(int i = 0; i < 24; i++){
      if(vehicles[i].active == true && vehicles[i].pos.lane == player.pos.lane){
        int dist = abs(player.pos.x - vehicles[i].pos.x);

        if(player.pos.x - vehicles[i].pos.x < 0 && dist < player.width || player.pos.x - vehicles[i].pos.x >= 0 && dist < vehicles[i].width){
          player.jumps = 0;
          display.clearDisplay();
          display.setCursor(10, 20);
          display.setTextSize(2);
          display.setTextColor(COLOR_WHITE);
          display.print("GAME OVER");
          display.display();
          for(int i = 0; i < 24; i++){
            vehicles[i].active = false;
          }
          delay(5000);
          level = 0;
        }
      }
    }

    // AKTUALIZOWANIE TIMERA
    vehicleTimer++;
    // if(vehicleTimer > 8)
    //   vehicleTimer = 0;

    // DRUKOWANIE WSZYSTKIEGO
    display.display();
  }

  //WCZYTANIE NOWEGO LEVELA
  if(level != 0){
    //PRZESUWANIE MAPY W DÓŁ
    for(;currMapPos < DISPLAY_HEIGHT; currMapPos++){
      // RYSOWANIE ULICY
      display.clearDisplay();
      drawStreet(currMapPos, currMapSize);

      // RYSOWANIE SAMOCHODÓW
      for(int i = 0; i < 24; i++){
        if(vehicles[i].active == true){
          display.drawBitmap(vehicles[i].pos.x, vehicles[i].pos.y++, vehicles[i].bitmap, vehicles[i].width, vehicles[i].height, COLOR_WHITE);
        }
      }

      // RYSOWANIE GRACZA
      display.drawBitmap(player.pos.x, player.pos.y++, player.bitmap, player.width, player.height, COLOR_WHITE);

      display.display();
    }
  }  
}


/////////////////////////////////////////////// STREET 
void drawStreet(int y, int lines){  //y może być dowolne. Nawet na minusie
  if(y >= DISPLAY_HEIGHT)
    return;

  if(y >= 0)
    display.drawFastHLine(0, y, DISPLAY_WIDTH, COLOR_WHITE);

  for(int yy = y + LANE_WIDTH + 1; yy < DISPLAY_HEIGHT && lines > 0; yy += LANE_WIDTH + 1, lines--){
    if(yy > 0)
      if(lines != 1)
        drawDottedLine(yy);
      else
        display.drawFastHLine(0, yy, DISPLAY_WIDTH, COLOR_WHITE);
  }
}

void drawDottedLine(int y){
  for(int x = 0; x < DISPLAY_WIDTH; x += LINE_LENGTH * 2){
    if(x > DISPLAY_WIDTH - LINE_LENGTH){
      display.drawFastHLine(x, y, DISPLAY_WIDTH - x, COLOR_WHITE);
    } else {
      display.drawFastHLine(x, y, LINE_LENGTH, COLOR_WHITE);
    }
  }
}
/////////////////////////////////////////////// STREET ^^


void beep(){
  digitalWrite(BUZZER, HIGH);
  delay(10);
  digitalWrite(BUZZER, LOW);
}
