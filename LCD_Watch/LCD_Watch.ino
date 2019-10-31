/*  TME EDUCATION
 *  LCDWatch
 *  v0.1.0
 *  -------------
 *  In this program we will learn how to handle time.
 */ 
#define PROJECT_NAME "LCDWatch"
#define VERSION "v0.1.0"

#include "includes.h"
////////CONSTANTS////////
//In this section, all constants resulting from the prototype board design are set

////////MODIFIERS////////
//In this section there are constants whose modification will affect the operation of our plate


////////DECLARATIONS////////
//This section prepares variables that are responsible for the individual components on the board
hd44780_I2Cexp lcd(0x20, I2Cexp_MCP23008, 7, 6, 5, 4, 3, 2, 1, HIGH);

//In the previous program, we wrote our program using the setup () function. 
//This is part of the code that starts at the very start of our program.
void setup(){
  lcd.begin(16, 2);
  intro(lcd);
}


//Now we will use the loop () function. It takes place right after the setup () function and repeats
//over and over again until there is no electricity
void loop(){
  lcd.setCursor(0,0); //delete this line, and uncomment the following lines of code (under HOUR, MINUTES and SECONDS)
  //this change should fix the bug with the remaining 9 seconds. Do you know why this error occurred?
  
  //HOURS
//  lcd.setCursor(8, 0);
//  if(getHour() < 10){
//    lcd.print("0");
//  }
  lcd.print(getHour());
  lcd.print(":");

  //MINUTES
//  lcd.setCursor(11, 0);
//  if(getMinute() < 10){
//    lcd.print("0");
//  }
  lcd.print(getMinute());
  lcd.print(":");

  //SECONDS
//  lcd.setCursor(14, 0);
//  if(getSecond() < 10){
//    lcd.print("0");
//  }
  lcd.print(getSecond());
}

//Below you can see the function containing the millis() call. 
//millis() returns the nuber of milliseconds since the TME board began running the current program.
//We used this function to correctly return the program's time in the form of seconds, minutes and hours


int getMillis(){
  //Here we have a method giving milliseconds. Each second consists of 1000 milliseconds. 
  //Your task is to add a millisecond meter to our clock.
  //We use here modulo operation. This is the operator of the remainder of the division 
  //3%2 gives us 1. 3%3 equals 0. 
  return millis() % 1000;
}

int getSecond(){
  return (millis() / 1000) % 60;
}

int getMinute(){
  return (millis() / 1000 / 60) % 60;
}

int getHour(){
  return (millis() / 1000 / 60 / 60) % 60;
}






