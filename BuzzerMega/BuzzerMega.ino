/*  TME EDUCATION
 *  BuzzerMega
 *  v0.1.0
 *  -------------
 *  This program will play everething in RTTTL format
 */ 
#define PROJECT_NAME "BuzzerMega"
#define VERSION "v0.2.0"

#include "includes.h"
#include "song.h"
////////CONSTANTS////////
//In this section, all constants resulting from the prototype board design are set

////////MODIFIERS////////
//In this section there are constants whose modification will affect the operation of our plate


////////DECLARATIONS////////
//This section prepares variables that are responsible for the individual components on the board
hd44780_I2Cexp lcd(0x20, I2Cexp_MCP23008, 7, 6, 5, 4, 3, 2, 1, HIGH);

uint16_t noteList[4][12] =  {{261, 277, 293, 311, 329, 349, 370, 392, 415, 440, 466, 493},
                          {523, 554, 587, 622, 659, 698, 740, 784, 830, 880, 932, 987},
                          {1047, 1109, 1175, 1245, 1319, 1397, 1480, 1568, 1661, 1760, 1865, 1976},
                          {2093, 2217, 2349, 2489, 2637, 2794, 2960, 3136, 3322, 3520, 3729, 3951}};

class Rtttl{
  public:
    String name;
    int duration;
    int octave;
    int tempo;
    String notes;

  Rtttl(String song){
    this->name = song.substring(0, song.indexOf(':'));
    this->duration = song.substring(song.indexOf("d=") + 2).toInt();
    this->octave = song.substring(song.indexOf("o=") + 2).toInt();
    this->tempo = song.substring(song.indexOf("b=") + 2).toInt();
    this->notes = song.substring(song.indexOf(":", song.indexOf("b=")) + 1);
    this->notes.replace(" ", "");
  }
  
  void Play(){
    String duration;
    String note;
    String octave;
    bool dot;
    int pitch;
    
    int pointer = 0;
    String token = "";
    
    while(true){
      token = notes.substring(pointer, notes.indexOf(",", pointer));
      
      duration = "";
      note = "";
      octave = "";
      
      int i = 0;
      while(token[i] >= '0' && token[i] <= '9' && i < token.length()){
        if(token[i] == '.'){
          i++;
          break;
        }
        duration += token[i];
        i++;
      }
  
      while((token[i] < '0' || token[i] > '9') && i < token.length()){
        if(token[i] == '.'){
          i++;
          break;
        }
        note += token[i];
        i++;
      }
  
      while(token[i] >= '0' && token[i] <= '9' && i < token.length()){
        if(token[i] == '.'){
          i++;
          break;
        }
        octave += token[i];
        i++;
      }
  
      dot = token.indexOf(".") != -1;
  
      if(duration == ""){
        duration = this->duration;
      }
      if(octave == ""){
        octave = this->octave;
      }
  
      pitch = -1;
      if(note.indexOf("c") != -1)
        pitch = 0;
      if(note.indexOf("c#") != -1)
        pitch = 1;
      if(note.indexOf("d") != -1)
        pitch = 2;
      if(note.indexOf("d#") != -1)
        pitch = 3;
      if(note.indexOf("e") != -1)
        pitch = 4;
      if(note.indexOf("f") != -1)
        pitch = 5;
      if(note.indexOf("f#") != -1)
        pitch = 6;
      if(note.indexOf("g") != -1)
        pitch = 7;
      if(note.indexOf("g#") != -1)
        pitch = 8;
      if(note.indexOf("a") != -1)
        pitch = 9;
      if(note.indexOf("a#") != -1)
        pitch = 10;
      if(note.indexOf("b") != -1)
        pitch = 11;
      if(note.indexOf("p") != -1)
        pitch = 12;

      int durationInt = (60000) / this->tempo * 4 / duration.toInt();
      durationInt = dot ? durationInt + durationInt / 2 : durationInt;
      
      int frequency = noteList[octave.toInt() - 4][pitch];
      if(pitch == 12)
        frequency = 0;
        
      tone(2, frequency, durationInt);
      delay(durationInt);

      pointer = notes.indexOf(",", pointer) + 1;
      if(pointer == 0)
        break;   
    }
    }
};

void setup(){
  Serial.begin(9600);
//  lcd.begin(16, 2);
 // intro(lcd);

  String song = SONG;
  Rtttl rtttl(song);
  rtttl.Play();
}

void loop(){
  
}


