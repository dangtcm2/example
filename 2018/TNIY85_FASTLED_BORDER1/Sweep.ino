void rainbowSweep() {

  for (int i = 0; i < NUM_STRINGS; i++) {
    shiftOut16(1 << i);
    fill_solid(leds, NUM_LEDS, CHSV(gHue + 18 * i, 255, 255));
    FastLED.show();
  }
}

