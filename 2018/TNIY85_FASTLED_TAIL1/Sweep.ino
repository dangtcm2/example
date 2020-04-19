uint8_t pseudoRandom[5][5] = {
  {10, 15, 30, 35, 45},
  {00, 10, 20, 30, 40},
  {00, 15, 20, 25, 40},
  {00, 00, 00, 00, 00},
  {05, 20, 25, 35, 45}
};

void sweepRandom()
{
  static uint8_t lastPos;
  static uint8_t count1;
  static uint16_t count;
  static uint8_t lastSeq;
  static uint8_t str;
  uint8_t c = 0;

  if (lastPos == shinePos) return;

  if (lastSeq != effectSequence) {
    count = 0;
    //str = 0;
  }

  //  if (count1 <= 1) {
  //    count1++;
  //    return;
  //  } else     count1 = 0;

  //for (int str = 0; str < 5; str ++) {

  shiftOut16(1 << str); delay(5);

  fill_solid(leds, NUM_LEDS, CHSV(0, 0, 0));
  for (int i = count; i >= 0; i--) {

    for (int j = 0; j < 5; j++) {
      if ((c == pseudoRandom[str][j] ) && (i <= NUM_LEDS)) {
        leds[i] = CHSV(0, 0, 255);
        //leds[i + 1] = CHSV(0, 0, 255);
      }
    }

    c++;
    if (c >= 50) c = 0;
  }
  FastLED.show();
  //FastLED.delay(10);

  str++;   if (str >= 2) str = 0;

  count++;
  lastPos = shinePos;
  lastSeq = effectSequence;

}


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
      fill_solid(leds, NUM_LEDS, CHSV(h , 255, 255 - i * 25));
      //fill_solid(leds, NUM_LEDS, CHSV(h - i*25, 255, 255 ));
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
