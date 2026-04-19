#include <Adafruit_GFX.h>  // Core graphics library
#include <MCUFRIEND_kbv.h> // Hardware specific library
#include <string.h>
typedef String string;

#define LCD_CS A3    // Chip Select  -> A3
#define LCD_CD A2    // Command/Data -> A2
#define LCD_WR A1    // LCD Write    -> A1
#define LCD_RD A0    // LCD Read     -> A0
#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

MCUFRIEND_kbv tft;

#define	BLACK   0x0000
#define WHITE   0xFFFF
#define	RED     0xF800
#define	GREEN   0x07E0
#define	BLUE    0x001F
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0

/* DISPLAY:
0------------------------320 X
|                          : 
|                          :
|             .            :
|                          :
|                          :
240........................:
Y

TARGET: - the text's rect is divided by 2 on both axes and placed in the center 
setCursor(tft.width()/2 - w/2, tft.height()/2 - h/2)
0------------------------320 X
|                          : 
|           _____          :
|          |TE.XT|         :
|          |_____|         :
|                          :
240........................:
*/

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
  

  string text = "EVERYWHERE";
  uint16_t x=0, y=0;
  int16_t x1=0, y1=0;
  uint16_t width=0, height=0;
  
  uint8_t size = 2;
  
  tft.setTextSize(5);
  tft.getTextBounds(text, x, y, &x1, &y1, &width, &height);
  uint16_t cursorX = tft.width()/2  -  width/2- x1;
  uint16_t cursorY = tft.height()/2 - height/2- y1;
  tft.setCursor(cursorX, cursorY);
  tft.print(text);
  
  tft.setTextSize(size);  
  tft.setCursor(0, 0);
  tft.print("size    "); tft.println(size);
  tft.print("x1      "); tft.println(x1);
  tft.print("y1      "); tft.println(y1); 
  tft.print("width   "); tft.println(width);
  tft.print("height  "); tft.println(height); 

  
}

void loop(void) {
  
}
