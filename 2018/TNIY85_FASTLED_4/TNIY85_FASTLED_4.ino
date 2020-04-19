#include "FastLED.h"

FASTLED_USING_NAMESPACE


#define NUM_LEDS 80
#define NUM_STRINGS 26 //15 visible strings and 11 strings out-of-vision
#define DATA_PIN 1
#define FRAMES_PER_SECOND  240
#define SR_MASK 0x7FFF

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
SimplePatternList gPatterns = {lightSweep, shine1a, shine2, shine3, lowProfileRainbow, shine1b, darkSweep, shine2ex};
//{ shine1, shine2, shine3, lowProfileGlittering,  lowProfileRainbow, confetti, lowProfileSinelon, juggleMonochrome};
//{colorful, rainbow, rainbowWithGlitter, confetti, sinelon, juggle, bpm };

uint8_t gCurrentPatternNumber = random(0, 2); // Index number of which pattern is current
uint8_t gHue = 0; // rotating "base color" used by many of the patterns
uint8_t gHue2 = 0;
uint8_t shinePos = 0;
uint8_t stringPos = 0;
uint8_t randomHue = random8(255);

void loop()
{

  // Call the current pattern function once, updating the 'leds' array
  gPatterns[gCurrentPatternNumber]();

  FastLED.show();
  FastLED.delay(1000 / FRAMES_PER_SECOND);

  // do some periodic updates
  EVERY_N_MILLISECONDS( 50 ) {
    gHue++;  // slowly cycle the "base color" through the rainbow
    gHue2 += 8;
  }
  EVERY_N_SECONDS( 15 ) {
    nextPattern();  // change patterns periodically
    shiftOut16(LEDS_ALL);
  }

  EVERY_N_MILLISECONDS( 45 ) {
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
  gCurrentPatternNumber = (gCurrentPatternNumber + 1 + random8(0, 2) ) % ARRAY_SIZE( gPatterns);
}


