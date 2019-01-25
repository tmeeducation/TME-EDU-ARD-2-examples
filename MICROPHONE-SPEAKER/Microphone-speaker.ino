/*  TME EDUCATION
 *  Template
 *  v0.0.0
 *  -------------
 *  The program makes it possible to read data from the microphone and represent them using the speaker.
 */ 
 
#define PROJECT_NAME "Microphone-Speaker"
#define VERSION "v0.1.0"

#include "includes.h"
////////CONSTANTS////////
//In this section, all constants resulting from the prototype board design are set
#define SPEAKER 2
#define MICROPHONE 0
#define POTENTIOMETER 1

////////MODIFIERS////////
//In this section there are constants whose modification will affect the operation of our plate

////////DECLARATIONS////////
//This section prepares variables that are responsible for the individual components on the board
hd44780_I2Cexp lcd(0x20, I2Cexp_MCP23008, 7, 6, 5, 4, 3, 2, 1, HIGH);

void setup(){
  lcd.begin(16, 2);
  intro(lcd);

  pinMode(SPEAKER, OUTPUT);  
  pinMode(MICROPHONE, INPUT);
}

unsigned long tempTime = 0;
int sensitivity = 250;

void loop(){
//Sometimes, when writing a program, we do not know how the equipment works, 
//or how any factor will affect the operation of the program. 
//That is why it is sometimes worth writing a program so that you can easily change its parameters. 
//In this case, by uncommenting the code below, you add the possibility to change the sensitivity. Useful, right?
  
//  if(tempTime < millis()){    
//    lcd.clear();
//    lcd.print(sensitivity);
//    tempTime = millis() + 500;
//  }  
//  sensitivity = analogRead(POTENTIOMETER);

  if(analogRead(MICROPHONE) > sensitivity){
    bip();
    delay(100);
  }
}

void bip(){
  digitalWrite(SPEAKER, HIGH);
  delay(1);
  digitalWrite(SPEAKER, LOW);
}

