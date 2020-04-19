void lowProfileSinelon()
{
  //static uint8_t c, h;
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, 20);
  int pos = beatsin16(40, 0, NUM_LEDS);
  leds[pos] += CHSV( gHue2, 200, 200);

}

void lowProfileGlittering()
{
  for (int i = 0; i < 16; i++) {
    fill_solid(leds, NUM_LEDS, CHSV(0, 0, 0));
    shiftOut16(1 << i);
    addGlitter(160);
    addGlitter2(160);
    FastLED.show();
  }
  FastLED.delay(7);
}

void lowProfileRainbow()
{
  // FastLED's built-in rainbow generator
  fill_rainbow( leds, NUM_LEDS, 255 - gHue, 7);
  for (int i = 0; i < NUM_LEDS; i++) leds[i] += CHSV(0, 0, 70);
}

void juggleMonochrome() {
  // eight monochrome dots, weaving in and out of sync with each other
  fadeToBlackBy( leds, NUM_LEDS, 20);
  for ( int i = 0; i < 8; i++) {
    leds[beatsin16(i + 7, 0, NUM_LEDS)] |= CHSV(gHue2, 200, 255);
  }
}

void shine1()
{
  static uint8_t c1, h1;

  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, 30);

  leds[shinePos] += CHSV( h1, 255, 255);

  if (c1++ >= 40) {
    h1 += 20;
    c1 = 0;
  }

}

void shine2()
{
  static uint8_t lastPos;
  static uint8_t h;
  static uint8_t newHue;
  static uint16_t count;
  uint8_t c = 0;

  if (lastPos == shinePos) return;

  if (count >= 0) {
    for (int i = count; i >= 0; i--) {
      if ((c <= 4) && (i <= NUM_LEDS)) leds[i] = CRGB::White;
      if ((c > 4) && (i <= NUM_LEDS)) leds[i] = CHSV(h, 255, 255);
      c++;
      if (c >= 10) c = 0;
    }
  }

  count++;
  lastPos = shinePos;
  if (!(count % NUM_LEDS)) newHue = random8();
  if (h < newHue) h++;
  if (h > newHue) h--;
  if (count >= 5000) count = 0;

}

void shine3()
{
  static uint8_t lastPos;
  static uint16_t count;
  uint8_t c = 0;

  if (lastPos == shinePos) return;

  if (count >= 0) {
    for (int i = count; i >= 0; i--) {
      if ((c <= 2) && (i <= NUM_LEDS)) leds[i] = CRGB(0, 0, 0);
      if ((c == 3) && (i <= NUM_LEDS)) leds[i] = CHSV(gHue, 150, 60);
      if ((c == 4) && (i <= NUM_LEDS)) leds[i] = CHSV(gHue, 150, 255);
      if ((c == 5) && (i <= NUM_LEDS)) leds[i] = CHSV(gHue, 200, 180);
      if ((c == 6) && (i <= NUM_LEDS)) leds[i] = CHSV(gHue, 200, 150);
      if ((c == 7) && (i <= NUM_LEDS)) leds[i] = CHSV(gHue, 255, 120);
      if ((c == 8) && (i <= NUM_LEDS)) leds[i] = CHSV(gHue, 255, 90);
      if ((c == 9) && (i <= NUM_LEDS)) leds[i] = CHSV(gHue, 255, 60);
      if ((c == 10) && (i <= NUM_LEDS)) leds[i] = CHSV(gHue, 255, 30);
      c++;
      if (c >= 11) c = 0;
    }
  }

  count++;
  lastPos = shinePos;
  if (count >= 5000) count = 0;
  FastLED.delay(30);
}

void colorful() {
  uint8_t sat = beatsin8(30, 80, 160);
  uint8_t val = beatsin8(10, 80, 200);

  for (int i = 0; i < NUM_LEDS; i++) leds[i] = CHSV(gHue, sat, val);
}

