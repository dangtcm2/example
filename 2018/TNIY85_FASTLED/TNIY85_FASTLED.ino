#include <FastLED.h>

#define NUM_LEDS 28
#define DATA_PIN 1
//
#define CLR(x,y) (x&=(~(1<<y)))
#define SET(x,y) (x|=(1<<y))

#define LEDS_ALL 0xFFFF
#define LEDS_MAIN 0x1
#define LEDS_SUB 0x2

CRGB leds[NUM_LEDS];
uint16_t currentSRValue;

void setup() {

  FastLED.addLeds<UCS1903B, DATA_PIN>(leds, NUM_LEDS);

  SET(DDRB, 0); //MOSI OUTPUT
  SET(DDRB, 1); //LED_OUT OUTPUT
  SET(DDRB, 3); //LATCH OUTPUT
  SET(DDRB, 4); //SCK OUTPUT

  shiftOut16(LEDS_ALL);

}

void shiftOut16(uint16_t srData) {

  if (srData == currentSRValue) return;

  uint16_t mask = 0x8000;

  CLR(PORTB, 3); //LATCH LOW

  for (int i = 0; i < 16; i++) {
    if (mask & srData) SET(PORTB, 0); else CLR(PORTB, 0); //16-BIT DATA OUT
    SET(PORTB, 4); //CLK HIGH
    CLR(PORTB, 4); //CLK LOW
    mask = mask >> 1;
  }

  SET(PORTB, 3); //LATCH HIGH
  currentSRValue = srData;
}

void fadeall() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i].nscale8(250);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long ms_delay = 32;

  for (int i = 0; i < 3; i++) effect_1(ms_delay);

  effect_2(ms_delay, 0);
  effect_2(ms_delay, 192);
  effect_2(ms_delay, 65);
  effect_2(ms_delay, 128);

  fill_solid(leds, NUM_LEDS, CHSV(0, 0, 0));

  for (int i = 0; i < 10; i++) effect_3(ms_delay);
}
