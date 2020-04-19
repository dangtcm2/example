void rainbow(uint8_t stp) {
  static uint8_t h = 255;

  if (bSwitched) h = realRandom();

  for (uint8_t i = 0; i < PIXELS; i++) {
    setPixelHSV(i, h + (stp * i), 255, 255);
  }

  h--;

}


void rainbowGlitter(uint8_t stp, uint8_t chance, uint8_t dly) {

  rainbow(stp);

  uint8_t pos;

  for (uint8_t i = 0; i < chance; i++) {
    pos = random(PIXELS);
    setPixelHSV(pos, 0, 0, 70);
  }

  showArray();
  delay(dly);
}


void shine1(uint8_t dly) {
  uint8_t h = 0;
  static uint8_t pos = 0;
  uint8_t count = 0;

  if (bSwitched) pos = 0;

  for (uint8_t i = pos; i >= 0; i--) {
    if ((count <=  4) && (i < PIXELS)) setPixelHSV(i, h, 255, 255);
    if ((count > 4) && (i < PIXELS)) setPixelHSV(i, 0, 0, 0);


    count++;
    if (count > 10) {
      count = 0;
      h += 50;
    }

    if (!i) break;
  }

  pos++;
  if (pos >= 3 * PIXELS) pos = PIXELS + 2; //DEPENDS ON HUE INCREASEMENT, NEEDS EXPERIMENT TO FIGURE OUT

  showArray();
  delay(dly);
}


void shine2(uint8_t dly) {
  static uint8_t pos = 0;
  uint8_t count = 0;
  static uint8_t hue = 0;

  if (bSwitched){
    hue = (uint8_t)(32 * realRandom() - 1);
    pos = 0;
  }

  for (uint8_t i = pos; i >= 0; i--) {
    if ((count == 0) && (i < PIXELS)) setPixelHSV(i, hue, 0, 255);
    if ((count == 1) && (i < PIXELS)) setPixelHSV(i, hue, 255, 220);
    if ((count == 2) && (i < PIXELS)) setPixelHSV(i, hue, 255, 120);
    if ((count == 3) && (i < PIXELS)) setPixelHSV(i, hue, 255, 20);
    if ((count > 4) && (i < PIXELS)) setPixelHSV(i, hue, 0, 0);

    count++;

    if (count > 5) count = 0;

    if (!i) break;
  }

  pos++;
  if (pos == 2 * PIXELS) pos = PIXELS + 4;

  showArray();
  delay((uint8_t)(dly * 1.4));
}


void shine3(uint8_t dly) {
  uint8_t h = 0;
  static uint8_t pos = 0;
  uint8_t count = 0;

  if (bSwitched) pos = 0;

  for (uint8_t i = pos; i >= 0; i--) {
    if ((count == 0) && (i < PIXELS)) setPixelHSV(i, 0, 0, 0);
    if ((count == 1) && (i < PIXELS)) setPixelHSV(i, h, 0, 220);
    if ((count == 2) && (i < PIXELS)) setPixelHSV(i, h, 0, 255);
    if ((count == 3) && (i < PIXELS)) setPixelHSV(i, h, 255, 200);
    if ((count == 4) && (i < PIXELS)) setPixelHSV(i, h, 255, 160);
    if ((count == 5) && (i < PIXELS)) setPixelHSV(i, h, 255, 120);
    if ((count == 6) && (i < PIXELS)) setPixelHSV(i, h, 255, 80);
    if ((count == 7) && (i < PIXELS)) setPixelHSV(i, h, 255, 40);
    if ((count == 8) && (i < PIXELS)) setPixelHSV(i, h, 255, 20);
    if ((count == 9) && (i < PIXELS)) setPixelHSV(i, h, 255, 10);
    if ((count == 10) && (i < PIXELS)) setPixelHSV(i, 0, 0, 0);

    count++;
    if (count > 10) {
      count = 0;
      h += 50;
    }

    if (!i) break;
  }

  pos++;
  if (pos >= 3 * PIXELS) pos = PIXELS + 2; //DEPENDS ON HUE INCREASEMENT, NEEDS EXPERIMENT TO FIGURE OUT

  showArray();
  delay(dly);
}

void shine4(uint8_t dly) {
  static uint8_t h = 0, pos = 0;

  effectRelease = 1;

  if (bSwitched) pos = 0;

  if (pos < PIXELS) {
    setPixelHSV(pos, h, 255, 255);
    showArray();
    delay(dly);
    pos++;
  } else {
    pos = 0;
    h += 100;
    effectRelease = 0;
  }
}

void shine5(uint8_t dly, uint8_t firstTime) {
  static uint8_t h = 20, count = 0;
  static uint8_t r = 0, g = 0, b = 0;
  uint8_t pos = 0;

  if (firstTime) {
    r = 0;
    g = 0;
    b = 0;
  }

  if (count < PIXELS) {

    while ((pixels_r[pos] != r) && (pixels_b[pos] != b) && (pixels_g[pos] != g)) {
      pos = random(PIXELS);
    }

    setPixelHSV(pos, h, 255, 255);
    //hsv2rgb(h, 255, 255, &pixels_r[pos], &pixels_g[pos], &pixels_b[pos]);

    showArray();
    delay(dly);
    count++;

  } else {
    delay(300);
    count = 0;
    hsv2rgb(h, 255, 255, &r, &g, &b);
    h += 100;
  }


}

void shine6(uint8_t dly) {
  static uint8_t h = 64, pos = 0;
  uint8_t count = 0;

  if (bSwitched) pos = 0;

  for (uint8_t i = pos; i >= 0; i--) {
    if ((count <= 1) && (i < PIXELS)) setPixelHSV(i, h, 255, 30);
    if ((count == 2) && (i < PIXELS)) setPixelHSV(i, h, 0, 255);

    count++;
    if (count > 2) {
      count = 0;
    }
    if (!i) break;
  }

  h += 2;
  pos++;
  if (pos == 3 * PIXELS) pos = PIXELS + 5; //DEPENDS ON HUE INCREASEMENT, NEEDS EXPERIMENT TO FIGURE OUT

  showArray();
  delay((uint8_t)(dly * 1.5));
}

void shine7(uint8_t dly) {
  uint8_t h = 0;
  static uint8_t pos = 0;
  uint8_t count = 0;

  if (bSwitched) pos = 0;

  for (uint8_t i = pos; i >= 0; i--) {
    if ((count == 0) && (i < PIXELS)) setPixelHSV(i, h, 255, 10);
    if ((count == 1) && (i < PIXELS)) setPixelHSV(i, h, 255, 80);
    if ((count == 2) && (i < PIXELS)) setPixelHSV(i, h, 255, 255);
    if ((count == 3) && (i < PIXELS)) setPixelHSV(i, h, 255, 80);
    if ((count == 4) && (i < PIXELS)) setPixelHSV(i, h, 255, 10);
    if ((count > 4) && (i < PIXELS)) setPixelHSV(i, h, 0, 0);


    count++;
    if (count > 7) {
      count = 0;
      h += 64;
    }

    if (!i) break;
  }

  pos++;
  if (pos >= 2 * PIXELS) pos = PIXELS - 3; //DEPENDS ON HUE INCREASEMENT, NEEDS EXPERIMENT TO FIGURE OUT

  showArray();
  delay((uint8_t)(dly * 1.4));
}

void shine8(uint8_t dly) {
  static uint8_t h = 0;
  static uint8_t pos = 0;
  uint8_t count = 0;

  if (bSwitched) pos = 0;

  effectRelease = 1;

  for (uint8_t i = pos; i >= 0; i--) {
    if ((count == 0) && (i < PIXELS)) setPixelHSV(i, h, 255, 255);
    if ((count == 1) && (i < PIXELS)) setPixelHSV(i, h, 255, 255);
    if ((count == 2) && (i < PIXELS)) setPixelHSV(i, h, 255, 200);
    if ((count == 3) && (i < PIXELS)) setPixelHSV(i, h, 255, 200);
    if ((count == 4) && (i < PIXELS)) setPixelHSV(i, h, 255, 160);
    if ((count == 5) && (i < PIXELS)) setPixelHSV(i, h, 255, 160);
    if ((count == 6) && (i < PIXELS)) setPixelHSV(i, h, 255, 100);
    if ((count == 7) && (i < PIXELS)) setPixelHSV(i, h, 255, 100);
    if ((count == 8) && (i < PIXELS)) setPixelHSV(i, h, 255, 80);
    if ((count == 9) && (i < PIXELS)) setPixelHSV(i, h, 255, 80);
    if ((count == 10) && (i < PIXELS)) setPixelHSV(i, h, 255, 60);
    if ((count == 11) && (i < PIXELS)) setPixelHSV(i, h, 255, 60);
    if ((count == 12) && (i < PIXELS)) setPixelHSV(i, h, 255, 60);
    if ((count == 13) && (i < PIXELS)) setPixelHSV(i, h, 255, 30);
    if ((count == 14) && (i < PIXELS)) setPixelHSV(i, h, 255, 10);
    if ((count == 15) && (i < PIXELS)) setPixelHSV(i, 0, 0, 0);

    count++;

    if (!i) break;
  }

  pos++;
  if (pos > PIXELS + 15) {
    pos = 0;
    h += 32;
    effectRelease = 0;
  }

  showArray();
  delay((uint8_t)(dly / 2) );
}

void shine8_reverse(uint8_t dly) {
  static uint8_t h;
  static uint8_t pos = 0;
  uint8_t count = 0;

  effectRelease = 1;

  for (uint8_t i = pos; i >= 0; i--) {
    if ((count == 0) && (i < PIXELS)) setPixelHSV(PIXELS - i, h, 255, 255);
    if ((count == 1) && (i < PIXELS)) setPixelHSV(PIXELS - i, h, 255, 255);
    if ((count == 2) && (i < PIXELS)) setPixelHSV(PIXELS - i, h, 255, 200);
    if ((count == 3) && (i < PIXELS)) setPixelHSV(PIXELS - i, h, 255, 200);
    if ((count == 4) && (i < PIXELS)) setPixelHSV(PIXELS - i, h, 255, 160);
    if ((count == 5) && (i < PIXELS)) setPixelHSV(PIXELS - i, h, 255, 160);
    if ((count == 6) && (i < PIXELS)) setPixelHSV(PIXELS - i, h, 255, 100);
    if ((count == 7) && (i < PIXELS)) setPixelHSV(PIXELS - i, h, 255, 100);
    if ((count == 8) && (i < PIXELS)) setPixelHSV(PIXELS - i, h, 255, 80);
    if ((count == 9) && (i < PIXELS)) setPixelHSV(PIXELS - i, h, 255, 80);
    if ((count == 10) && (i < PIXELS)) setPixelHSV(PIXELS - i, h, 255, 60);
    if ((count == 11) && (i < PIXELS)) setPixelHSV(PIXELS - i, h, 255, 60);
    if ((count == 12) && (i < PIXELS)) setPixelHSV(PIXELS - i, h, 255, 60);
    if ((count == 13) && (i < PIXELS)) setPixelHSV(PIXELS - i, h, 255, 30);
    if ((count == 14) && (i < PIXELS)) setPixelHSV(PIXELS - i, h, 255, 10);
    if ((count == 15) && (i < PIXELS)) setPixelHSV(PIXELS - i, 0, 0, 0);

    count++;

    if (!i) break;
  }

  pos++;
  if (pos > PIXELS + 15) {
    pos = 0;
    effectId = effectId + 1 + randomEnable * realRandom(); //A7 is a floating ADC pin -> real  randomization
    clearArray();
    bSwitched = 1;
  }

  showArray();
  delay((uint8_t)(dly / 2) );
}

void shine9(uint8_t dly) {
  static uint8_t h = 0;
  static uint8_t pos = 0, count2 = 0;
  uint8_t count = 0;

  effectRelease = 1;

  for (uint8_t i = pos; i >= 0; i--) {
    if ((count <= 8) && (i < PIXELS)) setPixelHSV(i, h, 255, 255);
    if ((count > 8) && (i < PIXELS)) setPixelHSV(i, h, 255, 0);
    if ((count > 8) && (i < PIXELS) && (i <= 15 - count2)) setPixelHSV(i, (h + count2 * 3), 255, 255);

    count++;
    if (!i) break;
  }

  pos++;

  if (pos > 8) count2++;

  if (pos > PIXELS + 8) {
    pos = 0;
    h += 32;
    count2 = 0;
    effectRelease = 0; //tell main loop it can switch to next effect
  }

  showArray();
  delay(dly );
}
