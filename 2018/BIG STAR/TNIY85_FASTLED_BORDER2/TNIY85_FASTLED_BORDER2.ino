#include "FastLED.h"

FASTLED_USING_NAMESPACE

// FastLED "100-lines-of-code" demo reel, showing just a few
// of the kinds of animation patterns you can quickly and easily
// compose using FastLED.
//
// This example also shows one easy way to define multiple
// animations patterns and have them automatically rotate.
//
// -Mark Kriegsman, December 2014


#define NUM_LEDS 50
#define NUM_STRINGS 5
#define DATA_PIN 1
#define FRAMES_PER_SECOND  240
#define SR_MASK 0x1F

CRGB leds[NUM_LEDS];

//
#define CLR(x,y) (x&=(~(1<<y)))
#define SET(x,y) (x|=(1<<y))

#define LEDS_ALL 0x1F
#define LEDS_MAIN 0x1
#define LEDS_SUB 0x2

void setup() {
  //delay(3000); // 3 second delay for recovery

  // tell FastLED about the LED strip configuration
  FastLED.addLeds<UCS1903B, DATA_PIN>(leds, NUM_LEDS);

  SET(DDRB, 0); //MOSI OUTPUT
  SET(DDRB, 1); //LED_OUT OUTPUT
  SET(DDRB, 3); //LATCH OUTPUT
  SET(DDRB, 4); //SCK OUTPUT

  shiftOut16(SR_MASK);

  FastLED.setBrightness(255);

  // set master brightness control
}

void shiftOut16(uint16_t srData) {

  uint16_t mask = 0x8000;

  CLR(PORTB, 3); //LATCH LOW

  for (int i = 0; i < 16; i++) {
    if (mask & srData) SET(PORTB, 0); else CLR(PORTB, 0); //16-BIT DATA OUT
    SET(PORTB, 4); //CLK HIGH
    CLR(PORTB, 4); //CLK LOW
    mask = mask >> 1;
  }

  SET(PORTB, 3); //LATCH HIGH
}

// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = {border3, border4y, border2, border3r, rainbow2, border4, border3, border4r};


uint8_t gLeadingHue[] = {0, 96, 192, 128, 64, 224, 160};

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gHue = 0; // rotating "base color" used by many of the patterns
uint8_t gHue2 = 0;
uint8_t shinePos = 0;
uint8_t randomHue = random8(255);
uint8_t effectSequence = 0;

void loop()
{

  // Call the current pattern function once, updating the 'leds' array
  gPatterns[gCurrentPatternNumber]();

  FastLED.show();
  FastLED.delay(1000 / FRAMES_PER_SECOND);

  // do some periodic updates
  EVERY_N_MILLISECONDS( 15 ) {
    gHue++;  // slowly cycle the "base color" through the rainbow
    gHue2 += 8;
  }
  EVERY_N_SECONDS( 30 ) {
    nextPattern();  // change patterns periodically
    shiftOut16(LEDS_ALL);
  }

  EVERY_N_MILLISECONDS( 20 ) {
    shinePos++;
    if (shinePos >= NUM_LEDS) {
      shinePos = 0;
      randomHue += 60;
    }
  }

}

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void nextPattern()
{
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns);
  fill_solid(leds, NUM_LEDS, CHSV(0, 0, 0));
  effectSequence++;
}


