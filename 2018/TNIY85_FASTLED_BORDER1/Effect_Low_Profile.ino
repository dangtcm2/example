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
  //FastLED.delay(7);
}

void lowProfileRainbow()
{
  // FastLED's built-in rainbow generator
  fill_rainbow( leds, NUM_LEDS, 255 - gHue, 7);
  for (int i = 0; i < NUM_LEDS; i++) leds[i] += CHSV(0, 0, 30);
}

void juggleMonochrome() {
  // eight monochrome dots, weaving in and out of sync with each other
  fadeToBlackBy( leds, NUM_LEDS, 20);
  for ( int i = 0; i < 8; i++) {
    leds[beatsin16(i + 7, 0, NUM_LEDS)] |= CHSV(gHue2, 200, 255);
  }
}

void border1()
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

void border1a() {

  leds[shinePos] = CHSV(randomHue, 255, 255);
}

void border2()
{
  static uint8_t lastPos;
  static uint8_t h;
  static uint8_t newHue;
  static uint8_t hueIndex;
  static uint8_t count1;
  static uint8_t count2;
  static uint16_t count;
  uint8_t c = 0;

  if (lastPos == shinePos) return;
  if (count1 <= 10) {
    count1++;
    return;
  } else     count1 = 0;


  if (count >= 0) {
    for (int i = count; i >= 0; i--) {
      if ((c <= 1) && (i <= NUM_LEDS)) leds[i] = CHSV(0, 0, 240);
      if ((c > 1) && (i <= NUM_LEDS)) leds[i] = CHSV(h, 255, 180);
      c++;
      if (c >= 6) c = 0;
    }
  }

  count++;
  lastPos = shinePos;
  if (h == newHue) count2++;
  if (count2 >= 20) {
    hueIndex = (hueIndex + 1) % ARRAY_SIZE(gLeadingHue);
    newHue = gLeadingHue[hueIndex];
    count2 = 0;
  }

  if (h < newHue) h++;
  if (h > newHue) h--;

  if (count >= 2 * NUM_LEDS) count -= 6;
}

void border2_()
{
  static uint8_t lastPos;
  static uint8_t h;
  static uint8_t newHue;
  static uint8_t hueIndex;
  static uint8_t count1;
  static uint8_t count2;
  static uint16_t count;
  uint8_t c = 0;

  if (lastPos == shinePos) return;
  if (count1 <= 2) {
    count1++;
    return;
  } else     count1 = 0;


  if (count >= 0) {
    for (int i = count; i >= 0; i--) {
      if ((c <= 6) && (i <= NUM_LEDS)) leds[i] = CHSV(h, 255, 255);
      if ((c > 6) && (i <= NUM_LEDS)) leds[i] = CHSV(0, 0, 80);
      c++;
      if (c >= 14) c = 0;
    }
  }

  count++;
  lastPos = shinePos;
  if (h == newHue) count2++;
  if (count2 >= 20) {
    hueIndex = (hueIndex + 1) % ARRAY_SIZE(gLeadingHue);
    newHue = gLeadingHue[hueIndex];
    count2 = 0;
  }

  if (h < newHue) h++;
  if (h > newHue) h--;

  if (count >= 2 * NUM_LEDS) count -= 14;

}


void border3()
{
  static uint8_t lastPos;
  static uint16_t count, count1;
  uint8_t c = 0;

  if (lastPos == shinePos) return;
  if (count1 <= 7) {
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
      if ((c == 9) && (i <= NUM_LEDS)) leds[i] = CHSV(gHue, 255, 60);
      if ((c == 10) && (i <= NUM_LEDS)) leds[i] = CHSV(gHue, 255, 50);
      if ((c >= 11) && (i <= NUM_LEDS)) leds[i] = CHSV(gHue, 255, 40);
      c++;
      if (c >= 14) c = 0;
    }
  }

  count++;
  lastPos = shinePos;
  if (count >= 2 * NUM_LEDS) count -= 14;
}

void border3r()
{
  static uint8_t lastPos;
  static uint16_t count, count1;
  uint8_t c = 0;

  if (lastPos == shinePos) return;
  if (count1 <= 7) {
    count1++;
    return;
  } else     count1 = 0;

  if (count >= 0) {
    for (int i = count; i >= 0; i--) {
      if ((c <= 2) && (i <= NUM_LEDS)) leds[NUM_LEDS - i] = CRGB(0, 0, 0);
      if ((c == 3) && (i <= NUM_LEDS)) leds[NUM_LEDS - i] = CHSV(gHue, 120, 240);
      if ((c == 4) && (i <= NUM_LEDS)) leds[NUM_LEDS - i] = CHSV(gHue, 170, 255);
      if ((c == 5) && (i <= NUM_LEDS)) leds[NUM_LEDS - i] = CHSV(gHue, 170, 240);
      if ((c == 6) && (i <= NUM_LEDS)) leds[NUM_LEDS - i] = CHSV(gHue, 255, 150);
      if ((c == 7) && (i <= NUM_LEDS)) leds[NUM_LEDS - i] = CHSV(gHue, 255, 100);
      if ((c == 8) && (i <= NUM_LEDS)) leds[NUM_LEDS - i] = CHSV(gHue, 255, 70);
      if ((c == 9) && (i <= NUM_LEDS)) leds[NUM_LEDS - i] = CHSV(gHue, 255, 60);
      if ((c == 10) && (i <= NUM_LEDS)) leds[NUM_LEDS - i] = CHSV(gHue, 255, 50);
      if ((c >= 11) && (i <= NUM_LEDS)) leds[NUM_LEDS - i] = CHSV(gHue, 255, 40);
      c++;
      if (c >= 14) c = 0;
    }
  }

  count++;
  lastPos = shinePos;
  if (count >= 2 * NUM_LEDS) count -= 14;
}

void border4()
{
  static uint8_t lastPos;
  static uint8_t count1;
  static uint16_t count;
  uint8_t c = 0;
  uint8_t h = 0;

  if (lastPos == shinePos) return;
  if (count1 <= 10) {
    count1++;
    return;
  } else     count1 = 0;


  if (count >= 0) {
    for (int i = count; i >= 0; i--) {
      if ((c == 0 ) && (i <= NUM_LEDS)) leds[i] = CHSV(h, 255, 40);
      if ((c == 1 ) && (i <= NUM_LEDS)) leds[i] = CHSV(h, 255, 110);
      if ((c == 2 ) && (i <= NUM_LEDS)) leds[i] = CHSV(h, 255, 255);
      if ((c == 3 ) && (i <= NUM_LEDS)) leds[i] = CHSV(h, 255, 255);
      if ((c == 4 ) && (i <= NUM_LEDS)) leds[i] = CHSV(h, 255, 255);
      if ((c == 5 ) && (i <= NUM_LEDS)) leds[i] = CHSV(h, 255, 110);
      if ((c == 6 ) && (i <= NUM_LEDS)) leds[i] = CHSV(h, 255, 40);
      if ((c > 6) && (i <= NUM_LEDS)) leds[i] = CRGB(0, 0, 0);
      c++;
      if (c > 6) {
        c = 0;
        h += 42;
      }
    }
  }

  count++;
  lastPos = shinePos;
  if (count == 2 * NUM_LEDS) count = NUM_LEDS;

}

void border4r()
{
  static uint8_t lastPos;
  static uint8_t count1;
  static uint16_t count;
  uint8_t c = 0;
  uint8_t h = 0;

  if (lastPos == shinePos) return;
  if (count1 <= 10) {
    count1++;
    return;
  } else     count1 = 0;


  if (count >= 0) {
    for (int i = count; i >= 0; i--) {
      if ((c == 0 ) && (i <= NUM_LEDS)) leds[NUM_LEDS - i] = CHSV(h, 255, 40);
      if ((c == 1 ) && (i <= NUM_LEDS)) leds[NUM_LEDS - i] = CHSV(h, 255, 110);
      if ((c == 2 ) && (i <= NUM_LEDS)) leds[NUM_LEDS - i] = CHSV(h, 255, 255);
      if ((c == 3 ) && (i <= NUM_LEDS)) leds[NUM_LEDS - i] = CHSV(h, 255, 255);
      if ((c == 4 ) && (i <= NUM_LEDS)) leds[NUM_LEDS - i] = CHSV(h, 255, 255);
      if ((c == 5 ) && (i <= NUM_LEDS)) leds[NUM_LEDS - i] = CHSV(h, 255, 110);
      if ((c == 6 ) && (i <= NUM_LEDS)) leds[NUM_LEDS - i] = CHSV(h, 255, 40);
      if ((c > 6) && (i <= NUM_LEDS)) leds[NUM_LEDS - i] = CRGB(0, 0, 0);
      c++;
      if (c > 6) {
        c = 0;
        h += 42;
      }
    }
  }

  count++;
  lastPos = shinePos;
  if (count == 2 * NUM_LEDS) count = NUM_LEDS;

}

void border4y()
{
  static uint8_t lastPos;
  static uint8_t count1;
  static uint16_t count;
  uint8_t c = 0;

  if (lastPos == shinePos) return;
  if (count1 <= 10) {
    count1++;
    return;
  } else     count1 = 0;


  if (count >= 0) {
    for (int i = count; i >= 0; i--) {
      if ((c == 0 ) && (i <= NUM_LEDS)) leds[NUM_LEDS - i] = CHSV(64, 200, 40);
      if ((c == 1 ) && (i <= NUM_LEDS)) leds[NUM_LEDS - i] = CHSV(64, 200, 80);
      if ((c == 2 ) && (i <= NUM_LEDS)) leds[NUM_LEDS - i] = CHSV(64, 200, 180);
      if ((c == 3 ) && (i <= NUM_LEDS)) leds[NUM_LEDS - i] = CHSV(64, 200, 240);
      if ((c == 4 ) && (i <= NUM_LEDS)) leds[NUM_LEDS - i] = CHSV(64, 200, 180);
      if ((c == 5 ) && (i <= NUM_LEDS)) leds[NUM_LEDS - i] = CHSV(64, 200, 80);
      if ((c == 6 ) && (i <= NUM_LEDS)) leds[NUM_LEDS - i] = CHSV(64, 200, 40);
      c++;

      if (c > 6)     c = 0;
    }
  }

  count++;
  lastPos = shinePos;
  if (count == 2 * NUM_LEDS) count = NUM_LEDS;

}

void join() {
  static uint8_t lastPos;
  static uint8_t count, count1, count2;
  static uint8_t hueIndex;
  static uint8_t h;

  if (lastPos == shinePos) return;

  //prescaler: wiping speed
  if (count2 <= 3) {
    count2++;
    return;
  } else     count2 = 0;

  if (!count1) {
    for (int i = 0; i < count; i++) {
      if (i > 0) leds[i - 1] = CHSV(h, 230, 255);
      leds[NUM_LEDS - i - 1] = CHSV(h, 230, 255);
    }
  } else {
    fadeToBlackBy( leds, NUM_LEDS, 8);
  }

  if (count >= (NUM_LEDS / 2) + 2) {
    count = 0;
    hueIndex = (hueIndex + 1) % ARRAY_SIZE(gLeadingHue);
    h = gLeadingHue[hueIndex];

    //prescaler: delays between wipes
    count1++;
    if (count1 > 3)         count1 = 0;
  }

  count++;
  lastPos = shinePos;
}

void rainbow2() {
  fill_solid(leds, NUM_LEDS, CHSV(gHue, 240, 220));
}

