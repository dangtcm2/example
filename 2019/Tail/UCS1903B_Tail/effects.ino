void rainbow(uint8_t stp) {
  static uint8_t h = 255;

  for (uint8_t i = 0; i < PIXELS; i++) {
    setPixelHSV(i, h + (stp * i), 255, 255);
  }

  h--;

}

void hueWalk(uint8_t dly) {
  static uint8_t h = 0;

  for (uint8_t i = 0; i < PIXELS; i++) {
    setPixelHSV(i, h, 255, 255);
  }

  h++;
  delay((uint8_t)(dly / 4));
  showArray();
}


void shine1(uint8_t dly) {
  uint8_t h = 0;
  static uint8_t pos = PIXELS;
  uint8_t count = 0;

  if (bSwitched) pos = PIXELS;

  for (uint8_t i = pos; i >= 0; i--) {
    if ((count ==  0) && (i < PIXELS)) setPixelHSV(i, h, 255, 20);
    if ((count ==  1) && (i < PIXELS)) setPixelHSV(i, h, 255, 120);
    if ((count ==  2) && (i < PIXELS)) setPixelHSV(i, h, 255, 255);
    if ((count ==  3) && (i < PIXELS)) setPixelHSV(i, h, 255, 120);
    if ((count ==  4) && (i < PIXELS)) setPixelHSV(i, h, 255, 20);
    if ((count ==  5) && (i < PIXELS)) setPixelHSV(i, 0, 0, 0);

    count++;
    if (count > 5) {
      count = 0;
      h += 32;
    }

    if (!i) break;
  }

  pos++;
  if (pos == 2 * PIXELS) pos = PIXELS + 4;

  showArray();
  delay(dly);
}


void shine1_reverse(uint8_t dly) {
  uint8_t h = 0;
  static uint8_t pos = PIXELS;
  uint8_t count = 0;

  if (bSwitched) pos = PIXELS;

  for (uint8_t i = pos; i > 0; i--) {
    if ((count ==  0) && (i <= PIXELS)) setPixelHSV(PIXELS - i, h, 255, 20);
    if ((count ==  1) && (i <= PIXELS)) setPixelHSV(PIXELS - i, h, 255, 100);
    if ((count ==  2) && (i <= PIXELS)) setPixelHSV(PIXELS - i, h, 255, 255);
    if ((count ==  3) && (i <= PIXELS)) setPixelHSV(PIXELS - i, h, 255, 100);
    if ((count ==  4) && (i <= PIXELS)) setPixelHSV(PIXELS - i, h, 255, 20);
    if ((count ==  5) && (i <= PIXELS)) setPixelHSV(PIXELS - i, 0, 0, 0);

    count++;
    if (count > 5) {
      count = 0;
      h += 32;
    }

    if (!i) break;
  }

  pos++;
  if (pos == 2 * PIXELS) pos = PIXELS + 4;

  showArray();
  delay(dly);
}

void shine2(uint8_t dly) {
  static uint8_t pos = PIXELS;
  uint8_t count = 0;
  static uint8_t hue = 0;

  if (bSwitched)     pos = PIXELS;


  for (uint8_t i = pos; i >= 0; i--) {
    if ((count == 0) && (i < PIXELS)) setPixelHSV(i, hue, 255, 255);
    if ((count == 1) && (i < PIXELS)) setPixelHSV(i, hue, 255, 200);
    if ((count == 2) && (i < PIXELS)) setPixelHSV(i, hue, 255, 80);
    if ((count == 3) && (i < PIXELS)) setPixelHSV(i, hue, 255, 20);
    if ((count == 4) && (i < PIXELS)) setPixelHSV(i, hue, 0, 0);

    count++;

    if (count > 5) count = 0;

    if (!i) break;
  }

  pos++;
  hue += 2;
  if (pos == 2 * PIXELS) pos = PIXELS + 4;

  showArray();
  delay((uint8_t)(dly * 1.4));
}

void shine2_reverse(uint8_t dly) {
  static uint8_t pos = PIXELS;
  uint8_t count = 0;
  static uint8_t hue = 0;

  if (bSwitched)     pos = PIXELS;


  for (uint8_t i = pos; i > 0; i--) {
    if ((count == 0) && (i <= PIXELS)) setPixelHSV(PIXELS - i, hue, 255, 255);
    if ((count == 1) && (i <= PIXELS)) setPixelHSV(PIXELS - i, hue, 255, 200);
    if ((count == 2) && (i <= PIXELS)) setPixelHSV(PIXELS - i, hue, 255, 80);
    if ((count == 3) && (i <= PIXELS)) setPixelHSV(PIXELS - i, hue, 255, 20);
    if ((count == 4) && (i <= PIXELS)) setPixelHSV(PIXELS - i, hue, 0, 0);

    count++;

    if (count > 5) count = 0;

    if (!i) break;
  }

  pos++;
  hue += 2;
  if (pos == 2 * PIXELS) pos = PIXELS + 4;

  showArray();
  delay((uint8_t)(dly * 1.4));
}


void shine6(uint8_t dly) {
  static uint8_t h = 64, pos = PIXELS;
  uint8_t count = 0;

  if (bSwitched) pos = PIXELS;

  for (uint8_t i = pos; i >= 0; i--) {
    if ((count <= 2) && (i < PIXELS)) setPixelHSV(i, h, 255, 30);
    if ((count == 3) && (i < PIXELS)) setPixelHSV(i, h, 0, 255);

    count++;
    if (count > 3)       count = 0;

    if (!i) break;
  }

  h += 2;
  pos++;
  if (pos == 2 * PIXELS) pos = PIXELS + 4; //DEPENDS ON HUE INCREASEMENT, NEEDS EXPERIMENT TO FIGURE OUT

  showArray();
  delay((uint8_t)(dly * 1.5));
}

void shine6_reverse(uint8_t dly) {
  static uint8_t h = 64, pos = PIXELS;
  uint8_t count = 0;

  if (bSwitched) pos = PIXELS;

  for (uint8_t i = pos; i > 0; i--) {
    if ((count <= 2) && (i <= PIXELS)) setPixelHSV(PIXELS - i, h, 255, 30);
    if ((count == 3) && (i <= PIXELS)) setPixelHSV(PIXELS - i, h, 0, 255);

    count++;
    if (count > 3)       count = 0;

    if (!i) break;
  }

  h += 2;
  pos++;
  if (pos == 2 * PIXELS) pos = PIXELS + 4; //DEPENDS ON HUE INCREASEMENT, NEEDS EXPERIMENT TO FIGURE OUT

  showArray();
  delay((uint8_t)(dly * 1.5));
}
