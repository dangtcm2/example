#include "FastLED.h"

FASTLED_USING_NAMESPACE


#define NUM_LEDS 50
#define NUM_STRINGS 10
#define DATA_PIN 1
#define FRAMES_PER_SECOND  190
#define SR_MASK 0x1F

CRGB leds[NUM_LEDS];

//
#define CLR(x,y) (x&=(~(1<<y)))
#define SET(x,y) (x|=(1<<y))

#define LEDS_ALL 0xFFFF
#define LEDS_MAIN 0x1
#define LEDS_SUB 0x2

void setup() {
  //delay(3000); // 3 second delay for recovery

  // tell FastLED about the LED strip configuration
  FastLED.addLeds<UCS1903B, DATA_PIN>(leds, NUM_LEDS);

  SET(DDRB, 0); //MOSI OUTPUT
  SET(DDRB, 1); //LED_OUT OUTPUT
  CLR(DDRB, 2); //ADC INPUT
  SET(DDRB, 3); //LATCH OUTPUT
  SET(DDRB, 4); //SCK OUTPUT

  shiftOut16(LEDS_ALL);

  FastLED.setBrightness(255);
}

void shiftOut16(uint16_t srData) {

  uint16_t mask = 0x8000;
  uint16_t data = (srData & SR_MASK);

  CLR(PORTB, 3); //LATCH LOW

  for (int i = 0; i < 16; i++) {
    if (mask & data) SET(PORTB, 0); else CLR(PORTB, 0); //16-BIT DATA OUT
    SET(PORTB, 4); //CLK HIGH
    CLR(PORTB, 4); //CLK LOW
    mask = mask >> 1;
  }

  SET(PORTB, 3); //LATCH HIGH
}

// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = 
{lightSweep, shine2c, shine3,  shine2,  shine2d, rainbow,  shine2e, rainbow2, shine2e};

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gHue = 0; // rotating "base color" used by many of the patterns
uint8_t gHue2 = 0;
uint8_t shinePos = 0;
uint8_t stringPos = 0;
uint8_t randomHue = random8(255);
uint8_t isFadingOut = 0;
uint8_t effectSequence = 0;

void loop()
{

  // Call the current pattern function once, updating the 'leds' array
  if (isFadingOut > 0)
    stringClear();
  else
    gPatterns[gCurrentPatternNumber]();


  FastLED.show();
  FastLED.delay(1000 / FRAMES_PER_SECOND);

  // do some periodic updates
  EVERY_N_MILLISECONDS( 30 ) {
    gHue++;  // slowly cycle the "base color" through the rainbow
    gHue2 += 4;
  }
  EVERY_N_SECONDS( 10 ) {
    nextPattern();  // change patterns periodically
    shiftOut16(LEDS_ALL);
  }

  EVERY_N_MILLISECONDS( 60 ) {
    shinePos++;
    stringPos++;

    if (stringPos >= NUM_STRINGS) stringPos = 0;

    if (shinePos >= NUM_LEDS) {
      shinePos = 0;
      randomHue += 60;
    }
  }

}

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + random8(1,2) ) % ARRAY_SIZE( gPatterns);
  effectSequence++;
  isFadingOut = 1;
}

void stringClear() {
  static uint8_t c;


  fadeToBlackBy( leds, NUM_LEDS, 10);

  if (c++ >= 85) {
    c = 0;
    isFadingOut = 0;
    shinePos = 0;
  }
}

