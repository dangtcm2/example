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


#define NUM_LEDS 27
#define DATA_PIN 1
#define FRAMES_PER_SECOND  120

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
  SET(DDRB, 3); //LATCH OUTPUT
  SET(DDRB, 4); //SCK OUTPUT

  shiftOut16(LEDS_ALL);

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
SimplePatternList gPatterns = {colorful, shine1, shine2, shine3, lowProfileGlittering,  lowProfileRainbow, confetti, lowProfileSinelon, juggleMonochrome};
//{ rainbow, rainbowWithGlitter, confetti, sinelon, juggle, bpm };

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gHue = 0; // rotating "base color" used by many of the patterns
uint8_t gHue2 = 0;
uint8_t shinePos = 0;
uint8_t bAbort = 0;

void loop()
{
  if (bAbort > 0) return;
  // Call the current pattern function once, updating the 'leds' array
  gPatterns[gCurrentPatternNumber]();

  // send the 'leds' array out to the actual LED strip
  FastLED.show();
  // insert a delay to keep the framerate modest
  FastLED.delay(1000 / FRAMES_PER_SECOND);

  // do some periodic updates
  EVERY_N_MILLISECONDS( 10 ) {
    gHue++;  // slowly cycle the "base color" through the rainbow
    gHue2 += 8;
  }
  EVERY_N_SECONDS( 10 ) {
    nextPattern();  // change patterns periodically
    shiftOut16(LEDS_ALL);
  }

  EVERY_N_MILLISECONDS( 30 ) {
    shinePos++;
    if (shinePos >= NUM_LEDS) shinePos = 0;
  }

  EVERY_N_MINUTES( 10 ) {
    fill_solid(leds, NUM_LEDS, CHSV(0, 0, 50));
    FastLED.show();
    bAbort = 1;
  }
}

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns);
}


