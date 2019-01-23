/*  TME EDUCATION
 *  LCDAlphabet
 *  v0.1.0
 *  -------------
 *  In this program you will learn what an ASCII table is and how to display individual characters
 */ 
#define PROJECT_NAME "LCDAlphabet"
#define VERSION "v0.1.0"

#include "includes.h"
////////CONSTANTS////////
//In this section, all constants resulting from the prototype board design are set

////////MODIFIERS////////
//In this section there are constants whose modification will affect the operation of our plate


////////DECLARATIONS////////
//This section prepares variables that are responsible for the individual components on the board
hd44780_I2Cexp lcd(0x20, I2Cexp_MCP23008, 7, 6, 5, 4, 3, 2, 1, HIGH);
char letter;

void setup(){
  lcd.begin(16, 2);
  intro(lcd);
  letter = 65;
}

//Each letter has its numerical value, which corresponds to it. 
//By entering the appropriate value we can get the letter on the display on which we care. 
//The appropriate values can be found in the ASCII table. 
//The cut-down version of the ascii table is visible at the bottom of the program
//Your task is to display small letters and check what will happen 
//when the values are greater than 127. Remember that the maximum value is 255.
void loop(){
  lcd.setCursor(0, 0);
  
  lcd.print(letter);

  delay(500);
  
  letter++;
  if(letter > 90){
    letter = 65;
  }
}

//ASCII

//  DEC   Char    DEC   Char    DEC   Char    DEC   Char    DEC   Char
//  32		Space   52    4       72    H       92    \       112   p
//  33    !       53    5       73    I       93    ]       113   q
//  34    "       54    6       74    J       94    ^       114   r
//  35    #       55    7       75    K       95    _       115   s
//  36    $       56    8       76    L       96    `       116   t
//  37    %       57    9       77    M       97    a       117   u
//  38    &       58    :       78    N       98    b       118   v
//  39    '       59    ;       79    O       99    c       119   w
//  40    (       60    <       80    P       100   d       120   x
//  41    )       61    =       81    Q       101   e       121   y
//  42    *       62    >       82    R       102   f       122   z
//  43    +       63    ?       83    S       103   g       123   {
//  44    ,       64    @       84    T       104   h       124   |
//  45    -       65    A       85    U       105   i       125   }
//  46    .       66    B       86    V       106   j       126   ~
//  47    /       67    C       87    W       107   k
//  48    0       68    D       88    X       108   l
//  49    1       69    E       89    Y       109   m
//  50    2       70    F       90    Z       110   n
//  51    3       71    G       91    [       111   o


