// IMPORTANT: ELEGOO_TFTLCD LIBRARY MUST BE SPECIFICALLY CONFIGURED FOR EITHER THE TFT SHIELD OR THE BREAKOUT BOARD.
// SEE RELEVANT COMMENTS IN Elegoo_TFTLCD.h FOR SETUP.
//Technical support:goodtft@163.com

#include <Adafruit_GFX.h>  // Core graphics library
#include <MCUFRIEND_kbv.h> // Hardware specific library
#include <string.h>
typedef String string;

// The control pins for the LCD can be assigned to any digital or analog pins...
// but we'll use the analog pins as this allows us to double up the pins with the touch screen (see the TFT paint example).
#define LCD_CS A3    // Chip Select  -> A3
#define LCD_CD A2    // Command/Data -> A2
#define LCD_WR A1    // LCD Write    -> A1
#define LCD_RD A0    // LCD Read     -> A0
#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

/* When using the BREAKOUT BOARD only, use these 8 data lines to the LCD:
  For the Arduino Uno, Duemilanove, Diecimila, etc.:
    D0 connects to digital pin 8  (Notice these are
    D1 connects to digital pin 9   NOT in order!)
    D2 connects to digital pin 2
    D3 connects to digital pin 3
    D4 connects to digital pin 4
    D5 connects to digital pin 5
    D6 connects to digital pin 6
    D7 connects to digital pin 7
  For the Arduino Mega, use digital pins 22 through 29
  (on the 2-row header at the end of the board). 
*/

MCUFRIEND_kbv tft;

#define	BLACK   0x0000 // https://rgbcolorpicker.com/565
#define WHITE   0xFFFF
#define	RED     0xF800
#define	GREEN   0x07E0
#define	BLUE    0x001F
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0

string lyrics[11] = {
  "AND",
  "OHH",
  "it's hard\nto see\nyou",
  "but I wish you",
  "WERE",
  "RIGHT",
  "HERE",
  "OHH",
  "it's hard\nto leave\nyou",
  "when I get you",
  "EVERYWHERE"
};

void printCentreLyrics(const string text[], uint8_t sizeLowercase, uint8_t sizeUppercase) {
  string temp[] = text;
  for(uint8_t i = sizeof(temp); i>=0; i++) { // for every element in the lyrics
    
    if(temp[i].find("\n") >= 0) { // if lines in element > 1
      strsep(temp[i], "\n");
      //more logic here ...

    }
    else { // if lines in element = 1
      int16_t x1, y1, width, height;
      
      tft.getTextBounds(temp[i], 0, 0, &x1, &y1, &width, &height); //width, height of new string
      tft.setCursor(tft.width()/2 - w/2 - x1, tft.height()/2 - h/2 - y1); // center
      tft.print(text);
    }

  }
}
/* void printCentreString(const string &text, int x, int y) {
  int16_t x1, y1;
  uint16_t w, h;
  tft.getTextBounds(text, x, y, &x1, &y1, &w, &h); //calc width of new string
  tft.setCursor(x - w / 2, y);
  tft.print(text);
} */
void printCenteredString(string text) {
  uint16_t x  = 0, y  = 0;
  int16_t  x1,     y1;
  uint16_t width,  height;

  uint8_t size = 1;
  if      (isupper(text)) { size = 5 ;}
  else if (islower(text)) { size = 3 ;} //unfigured
  
  tft.setTextSize(size);

  tft.getTextBounds(text,   x, y,   &x1, &y1,   &width, &height);

  uint16_t cursorX = tft.width()/2  -  width/2- x1;
  uint16_t cursorY = tft.height()/2 - height/2- y1;
  tft.setCursor(cursorX, cursorY);
  tft.print(text);
}

void setup(void) {
  Serial.begin(9600);

  #ifdef USE_Elegoo_SHIELD_PINOUT
    Serial.println(F("Using Elegoo 2.4\" TFT Arduino Shield Pinout"));
  #else
    Serial.println(F("Using Elegoo 2.4\" TFT Breakout Board Pinout"));
  #endif

  Serial.print("TFT size is "); Serial.print(tft.width()); Serial.print("x"); Serial.println(tft.height());

  tft.reset();

  uint16_t identifier = tft.readID();
  if      (identifier == 0x9325) { Serial.println(F("Found ILI9325 LCD driver"));                   }
  else if (identifier == 0x9328) { Serial.println(F("Found ILI9328 LCD driver"));                   }
  else if (identifier == 0x4535) { Serial.println(F("Found LGDP4535 LCD driver"));                  }
  else if (identifier == 0x7575) { Serial.println(F("Found HX8347G LCD driver"));                   }
  else if (identifier == 0x9341) { Serial.println(F("Found ILI9341 LCD driver"));                   }
  else if (identifier == 0x8357) { Serial.println(F("Found HX8357D LCD driver"));                   }
  else if (identifier==0x0101)   { identifier=0x9341; Serial.println(F("Found 0x9341 LCD driver")); }
  else if (identifier==0x1111)   { identifier=0x9328; Serial.println(F("Found 0x9328 LCD driver")); }
  else {
    Serial.print  (F("Unknown LCD driver chip: ")); Serial.println(identifier, HEX);
    Serial.println(F("If using the Elegoo 2.8\" TFT Arduino shield, the line:"));
    Serial.println(F("  #define USE_Elegoo_SHIELD_PINOUT"));
    Serial.println(F("should appear in the library header (Elegoo_TFT.h)."));
    Serial.println(F("If using the breakout board, it should NOT be #defined !"));
    Serial.println(F("Also if using the breakout, double-check that all wiring matches the tutorial."));
    identifier=0x9328;
  }

  tft.begin(identifier);
  tft.setRotation(1);
  tft.fillScreen(WHITE);
  tft.setTextWrap(false);

}

void loop(void) {
  for (uint8_t i=sizeof(lyrics) ; i>=0; i--) { //for every element in text do:
    
  }
}
