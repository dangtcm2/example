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
  for (int i = 0; i < NUM_STRINGS; i++) {
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

void shine1a()
{
  static uint8_t h1;

  fadeToBlackBy( leds, NUM_LEDS, 5);

  if (!shinePos) h1 = random8(255);

  leds[shinePos] = CHSV( h1, 255, 255);

}


void shine1b() {

  static uint8_t h1;

  fadeToBlackBy( leds, NUM_LEDS, 5);

  if (!shinePos) h1 = random8(255);

  leds[NUM_LEDS - 1 - shinePos] = CHSV( h1, 255, 255);
}


void shine2()
{
  static uint8_t lastPos;
  static uint8_t h;
  static uint8_t newHue;
  static uint8_t count1;
  static uint16_t count;
  uint8_t c = 0;

  if (lastPos == shinePos) return;
  if (count1 <= 3) {
    count1++;
    return;
  } else     count1 = 0;


  if (count >= 0) {
    for (int i = count; i >= 0; i--) {
      if ((c == 0 ) && (i <= NUM_LEDS)) leds[i] = CHSV(h, 235, 60);
      if ((c == 1 ) && (i <= NUM_LEDS)) leds[i] = CHSV(h, 235, 170);
      if ((c == 2 ) && (i <= NUM_LEDS)) leds[i] = CHSV(h, 235, 255);
      if ((c == 3 ) && (i <= NUM_LEDS)) leds[i] = CHSV(h, 235, 255);
      if ((c == 4 ) && (i <= NUM_LEDS)) leds[i] = CHSV(h, 235, 255);
      if ((c == 5 ) && (i <= NUM_LEDS)) leds[i] = CHSV(h, 235, 170);
      if ((c == 6 ) && (i <= NUM_LEDS)) leds[i] = CHSV(h, 235, 60);
      if ((c > 6) && (i <= NUM_LEDS)) leds[i] = CRGB(0, 0, 0);
      c++;
      if (c >= 10) c = 0;
    }
  }

  count++;
  lastPos = shinePos;
  if (!(count % (NUM_LEDS / 5))) newHue += 10;
  if (h < newHue) h++;
  if (h > newHue) h--;
  if (count == 2 * NUM_LEDS) count -= 10;

}

void shine2ex()
{
  static uint8_t lastPos;
  static uint8_t count1;
  static uint16_t count;
  uint8_t c = 0;
  uint8_t h = 0;

  if (lastPos == shinePos) return;
  if (count1 <= 4) {
    count1++;
    return;
  } else     count1 = 0;


  if (count >= 0) {
    for (int i = count; i >= 0; i--) {
      if ((c == 0 ) && (i <= NUM_LEDS)) leds[i] = CHSV(h, 255, 60);
      if ((c == 1 ) && (i <= NUM_LEDS)) leds[i] = CHSV(h, 255, 170);
      if ((c == 2 ) && (i <= NUM_LEDS)) leds[i] = CHSV(h, 255, 255);
      if ((c == 3 ) && (i <= NUM_LEDS)) leds[i] = CHSV(h, 255, 255);
      if ((c == 4 ) && (i <= NUM_LEDS)) leds[i] = CHSV(h, 255, 255);
      if ((c == 5 ) && (i <= NUM_LEDS)) leds[i] = CHSV(h, 255, 170);
      if ((c == 6 ) && (i <= NUM_LEDS)) leds[i] = CHSV(h, 255, 60);
      if ((c > 6) && (i <= NUM_LEDS)) leds[i] = CRGB(0, 0, 0);
      c++;
      if (c >= 10) {
        c = 0;
        h += 50;
      }
    }
  }

  count++;
  lastPos = shinePos;
  if (count == 3 * NUM_LEDS) count = NUM_LEDS + 4;

}

void shine2lite()
{
  static uint8_t lastPos;
  static uint8_t count1;
  static uint16_t count;
  uint8_t c = 0;
  uint8_t h = 0;

  if (lastPos == shinePos) return;
  if (count1 <= 4) {
    count1++;
    return;
  } else     count1 = 0;

  if (count >= 0) {
    for (int i = count; i >= 0; i--) {
      if ((c == 0 ) && (i <= NUM_LEDS)) leds[i] = CHSV(h, 0, 255);
      if ((c == 1 ) && (i <= NUM_LEDS)) leds[i] = CHSV(h, 240, 240);
      if ((c == 2 ) && (i <= NUM_LEDS)) leds[i] = CHSV(h, 240, 240);
      if ((c == 3 ) && (i <= NUM_LEDS)) leds[i] = CHSV(h, 240, 240);
      if ((c == 4 ) && (i <= NUM_LEDS)) leds[i] = CHSV(h, 0, 255);
      if ((c > 4 ) && (i <= NUM_LEDS)) leds[i] = CRGB(0, 0, 0);
      c++;
      if (c >= 10) {
        c = 0;
        h += 50;
      }
    }
  }

  count++;
  lastPos = shinePos;
  if (count == 3 * NUM_LEDS) count = NUM_LEDS + 4;

}

void shine3()
{
  static uint8_t lastPos;
  static uint8_t count;
  static uint8_t count1;
  uint8_t c = 0;


  if (lastPos == shinePos) return;
  if (count1 <= 3) {
    count1++;
    return;
  } else     count1 = 0;

  if (count >= 0) {
    for (int i = count; i >= 0; i--) {
      if ((c <= 2) && (i <= NUM_LEDS)) leds[i] = CRGB(0, 0, 0);
      if ((c == 3) && (i <= NUM_LEDS)) leds[i] = CHSV(gHue, 120, 240);
      if ((c == 4) && (i <= NUM_LEDS)) leds[i] = CHSV(gHue, 170, 255);
      if ((c == 5) && (i <= NUM_LEDS)) leds[i] = CHSV(gHue, 170, 240);
      if ((c == 6) && (i <= NUM_LEDS)) leds[i] = CHSV(gHue, 255, 150);
      if ((c == 7) && (i <= NUM_LEDS)) leds[i] = CHSV(gHue, 255, 100);
      if ((c == 8) && (i <= NUM_LEDS)) leds[i] = CHSV(gHue, 255, 70);
      if ((c == 9) && (i <= NUM_LEDS)) leds[i] = CHSV(gHue, 255, 55);
      if ((c == 10) && (i <= NUM_LEDS)) leds[i] = CHSV(gHue, 255, 40);
      c++;
      if (c >= 11)  c = 0;
    }
  }

  count++;
  lastPos = shinePos;
  if (count >= 2 * NUM_LEDS) count -= 11;
}

void shine3ex()
{
  static uint8_t lastPos;
  static uint8_t count;
  static uint8_t count1;
  static uint8_t h;
  uint8_t c = 0;


  if (lastPos == shinePos) return;
  if (count1 <= 2) {
    count1++;
    return;
  } else     count1 = 0;

  if (count >= 0) {
    for (int i = count; i >= 0; i--) {
      if ((c <= 2) && (i <= NUM_LEDS)) leds[i] = CRGB(0, 0, 0);
      if ((c == 3) && (i <= NUM_LEDS)) leds[i] = CHSV(h, 0, 255);
      if ((c == 4) && (i <= NUM_LEDS)) leds[i] = CHSV(h, 0, 255);
      if ((c == 5) && (i <= NUM_LEDS)) leds[i] = CHSV(h, 0, 255);
      if ((c == 6) && (i <= NUM_LEDS)) leds[i] = CHSV(h, 0, 180);
      if ((c == 7) && (i <= NUM_LEDS)) leds[i] = CHSV(h, 0, 80);
      if ((c == 8) && (i <= NUM_LEDS)) leds[i] = CHSV(h, 0, 70);
      if ((c == 9) && (i <= NUM_LEDS)) leds[i] = CHSV(h, 0, 50);
      if ((c == 10) && (i <= NUM_LEDS)) leds[i] = CHSV(h, 0, 20);
      if ((c == 11) && (i <= NUM_LEDS)) leds[i] = CHSV(h, 0, 20);
      if ((c == 12) && (i <= NUM_LEDS)) leds[i] = CHSV(h, 0, 20);
      //      if ((c == 13) && (i <= NUM_LEDS)) leds[i] = CHSV(h, 0, 55);
      //      if ((c == 14) && (i <= NUM_LEDS)) leds[i] = CHSV(h, 0, 45);
      //      if ((c > 14) && (c <= 18) && (i <= NUM_LEDS)) leds[i] = CHSV(h, 0, 20);
      if ((c > 12) && (i <= NUM_LEDS)) leds[i] = CRGB(0, 0, 0);
      c++;
    }
  }

  count++;
  lastPos = shinePos;
  if (count >= NUM_LEDS + 19)  {
    count = 0;
    c = 0;
  }
}

void shine4() {
  static uint8_t lastPos;
  static uint8_t h;
  static uint8_t newHue;
  static uint8_t count1;
  static uint16_t count;
  uint8_t c = 0;


  if (lastPos == shinePos) return;
  if (count1 <= 5) {
    count1++;
    return;
  } else     count1 = 0;


  if (count >= 0) {
    for (int i = count; i >= 0; i--) {
      if ((c == 0) && (i <= NUM_LEDS) ) leds[i] = CHSV(0, 0, 235);
      if ((c > 0) && (i <= NUM_LEDS) ) leds[i] = CHSV(h, 255, 120);
      c++;
      if (c >= 5) c = 0;
    }
  }

  count++;
  lastPos = shinePos;
  if (!(count % NUM_LEDS)) newHue += 32;
  if (h < newHue) h++;
  if (h > newHue) h--;
  if (count == 2 * NUM_LEDS) count -= 5;

}


