void lightSweep() {

  uint16_t darkPos;
  static uint8_t h;

  if (!stringPos) h += 60;

  shiftOut16(1 << stringPos);
  fill_solid(leds, NUM_LEDS, CHSV(h, 255, 255));
  FastLED.show();

  darkPos = (1 << stringPos);

  for (int i = 1; i <= 10; i++) {
    if (stringPos >= i) {
      shiftOut16(1 << (stringPos - i));
      fill_solid(leds, NUM_LEDS, CHSV(h, 255, 255 - i * 25));
      FastLED.show();
      darkPos |= (1 << (stringPos - i));
    }
  }

  darkPos = ~darkPos;
  shiftOut16(darkPos);
  fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
  FastLED.show();

  FastLED.delay(70);
}

void darkSweep() {

  uint16_t darkPos;


  shiftOut16(1 << stringPos);
  fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
  FastLED.show();

  darkPos = (1 << stringPos);

  for (int i = 1; i <= 10; i++) {
    if (stringPos >= i) {
      shiftOut16(1 << (stringPos - i));
      fill_solid(leds, NUM_LEDS, CHSV(gHue2, 120, i * 22));
      FastLED.show();
      darkPos |= (1 << (stringPos - i));
    }
  }

  darkPos = ~darkPos;
  shiftOut16(darkPos);
  fill_solid(leds, NUM_LEDS, CHSV(gHue2, 120, 220));
  FastLED.show();

  FastLED.delay(70);
}
