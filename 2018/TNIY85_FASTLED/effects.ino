void effect_1(unsigned long ms) {

  shiftOut16(LEDS_ALL);

  for (int hue = 0; hue < 255; hue++) {
    for (int i = 0; i < NUM_LEDS; i++)       leds[i] = CHSV(255 - hue, 255, 255);
    FastLED.show();
    FastLED.delay(ms / 3);
  }
}

void effect_2(unsigned long ms, uint8_t hue) {

  for (int i = 0; i < NUM_LEDS; i++) {

    fill_solid(leds, NUM_LEDS, CHSV(0, 0, 0));

    for (int k = 0; k < 10; k++) {
      if ((i - k) >= 0) leds[i - k] = CHSV(hue, 255, 255 - 25 * k);
    }
    FastLED.show();
    FastLED.delay(ms * 0.6);
  }
  FastLED.delay(ms * 1.5);

}

void effect_3(unsigned long ms) {

  static uint8_t hue = 0;

  // First slide the led in one direction
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(hue++, 255, 255);
    FastLED.show();
    fadeall();
    FastLED.delay(ms / 4);
  }


  // Now go in the other direction.
  for (int i = (NUM_LEDS) - 1; i >= 0; i--) {
    leds[i] = CHSV(hue++, 255, 255);
    FastLED.show();
    fadeall();
    FastLED.delay(ms / 4);
  }
}

