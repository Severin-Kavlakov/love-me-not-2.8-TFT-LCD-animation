#include <Adafruit_GFX.h>  // Core graphics library
#include <MCUFRIEND_kbv.h> // Hardware specific library
MCUFRIEND_kbv tft;

// The control pins for the LCD can be assigned to any digital or analog pins...
// but we'll use the analog pins as this allows us to double up the pins with the touch screen (see the TFT paint example).
#define LCD_CS A3    // Chip Select  -> A3
#define LCD_CD A2    // Command/Data -> A2
#define LCD_WR A1    // LCD Write    -> A1
#define LCD_RD A0    // LCD Read     -> A0
#define LCD_RESET A4 // Can alternately connect to Arduino's reset pin

#define	BLACK   0x0000 // https://rgbcolorpicker.com/565
#define WHITE   0xFFFF
#define	RED     0xF800
#define	GREEN   0x07E0
#define	BLUE    0x001F
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0

const uint8_t displayWidth=tft.width(), displayHeight = tft.height();

const uint8_t numFrames = 11;
char* lyrics[numFrames] = { //https://www.geeksforgeeks.org/c/array-of-strings-in-c/
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
uint8_t sizes[numFrames] = {0};

uint8_t findMaxTextSize(const char* text) {
  uint16_t x  = 0, y  = 0, width=0, height=0;
  int16_t  x1 = 0, y1 = 0;
  uint8_t maxSize=1;
  uint8_t currentSize=1;

  //start at size 1 ; check if width and height are smaller than screen sizes ; if NOT : STOP
  while (width < displayWidth && height < displayHeight) {
    tft.setTextSize(currentSize);
    tft.getTextBounds(text,  x, y,  &x1, &y1,   &width, &height);
    if(width < displayWidth && height < displayHeight) {
      maxSize = currentSize;
      currentSize++;
    }
    else {
      break;
    }
  }
  return maxSize;
}

for(int8_t i = 0; i < numFrames; i++) {
  sizes[i] = findMaxTextSize(lyrics[i]);
}

//could be an algorithm to determine if a string of a given size would fit on the screen AKA for each string find biggest size so it fits on the screen
//uint8_t sizeLowercase=3, sizeUppercase=5, sizeFullScreen=8; 

/*
void printCentreLyrics(const String text[], uint8_t sizeLowercase, uint8_t sizeUppercase) {
  String temp[] = text;
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
 void printCentreString(const string &text, int x, int y) {
  int16_t x1, y1;
  uint16_t w, h;
  tft.getTextBounds(text, x, y, &x1, &y1, &w, &h); //calc width of new string
  tft.setCursor(x - w / 2, y);
  tft.print(text);
} 
*/

//https://forum.arduino.cc/t/adafruit-oled-how-to-center-text/617181/5
//https://forum.arduino.cc/t/adafruit-gfx-gettextbounds-cursor-position-vs-bounding-box-top-left/1239441
void printCenteredString(char text[], uint8_t size) {
  uint16_t x  = 0, y  = 0, width=0, height=0;
  int16_t  x1 = 0, y1 = 0;

  tft.setTextSize(size);

  tft.getTextBounds(text,  x, y,  &x1, &y1,   &width, &height);

  uint16_t cursorX = displayWidth /2 - width /2 - x1;
  uint16_t cursorY = displayHeight/2 - height/2 - y1;
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
  tft.fillScreen(BLACK);
  tft.setTextWrap(false);
  tft.setTextColor(WHITE);
}

void loop(void) {
  for (int i = 0; i < numFrames; i++) { //for every element in text do:
    printCenteredString(lyrics[i], sizes[i]);
    tft.flush();
    delay(500);
    tft.fillScreen(BLACK);
  }
  delay(2000);
}
