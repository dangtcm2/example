void effect1() {
  uint16_t leds = 0;

  for (int i = 0; i < 16; i++) {
    leds = leds + (1 << i);
    shiftOut16(leds);
    delay(msDelay);
  }

  for (int i = 0; i <= 16; i++) {
    leds = leds & (0xFFFF << i);
    shiftOut16(leds);
    delay(msDelay);
  }

  delay(msDelay);

  for (int i = 0; i < 16; i++) {
    leds = leds + (0x8000 >> i);
    shiftOut16(leds);
    delay(msDelay);
  }

  for (int i = 0; i <= 16; i++) {
    leds = leds & (0xFFFF >> i);
    shiftOut16(leds);
    delay(msDelay);
  }

  delay(msDelay);
  nextPattern();
}








void effect2() {
  uint16_t leds = 0;
  static uint8_t cnt = 0;

  for (int i = 0; i < 8; i++) {
    leds = leds + (1 << i) + (0x8000 >> i);
    shiftOut16(leds);
    delay(msDelay);
  }

  for (int i = 0; i < 8; i++) {
    leds = leds - (1 << i) - (0x8000 >> i);
    shiftOut16(leds);
    delay(msDelay);
  }

  if (cnt++ >= 2) {
    cnt = 0;
    nextPattern();
  }
}








void effect3() {
  uint16_t leds = 0;
  uint16_t leds2 = 0;
  static uint8_t cnt = 0;

  for (int i = 15; i >= 0; i--) {
    for (int j = 0; j < i; j++) {
      leds = leds2 + (1 << j);
      shiftOut16(leds);
      delay(msDelay);
    }
    leds2 = leds2 + (1 << i);
  }

  delay(msDelay);

  leds2 = 0xFFFF;

  for (int i = 15; i >= 0; i--) {
    for (int j = i + 1; j <= 15; j++) {
      leds = leds2 + (1 << j);
      shiftOut16(leds);
      delay(msDelay);
    }

    leds2 = leds2 - (1 << i);
  }

  delay(msDelay);

  if (cnt++ >= 1) {
    cnt = 0;
    nextPattern();
  }
}








void effect4() {
  uint16_t leds = 0;
  uint16_t leds2 = 0;

  for (int i = 15; i >= 0; i--) {
    for (int j = (15 - i); j <= i; j++) {
      leds = leds2 + (1 << j);
      shiftOut16(leds);
      delay(msDelay);
    }

    leds2 = leds2 + (1 << i);

    for (int j = (i - 1); j >= (15 - i); j--) {
      leds = leds2 + (1 << j);
      shiftOut16(leds);
      delay(msDelay);
    }
    leds2 = leds2 + (1 << (15 - i));
  }

  nextPattern();
}








void effect5() {
  uint16_t leds = 1;
  static uint8_t cnt = 0;

  for (int i = 1; i < (16 + 10); i++) {
    shiftOut16(leds);
    delay(msDelay);

    leds = (leds << 1);
    if (i < 10) leds += 1;
  }

  delay(msDelay);
  leds = 0x8000;

  for (int i = 14; i >= -9; i--) {
    shiftOut16(leds);
    delay(msDelay);

    leds = (leds >> 1);
    if (i > 6) leds += 0x8000;
  }

  delay(msDelay);

  if (cnt++ >= 2) {
    cnt = 0;
    nextPattern();
  }
}








void effect6() {
  uint16_t leds = 0x9249;
  static uint8_t cnt = 0;

  for (int i = 1; i < 26; i++) {
    shiftOut16(leds);
    delay(2 * msDelay);

    leds = (leds << 1);
    if (!(i % 3)) leds = leds + 1;
  }

  leds = 0x9249;

  for (int i = 1; i < 26; i++) {
    shiftOut16(leds);
    delay(2 * msDelay);

    leds = (leds >> 1);
    if (!(i % 3)) leds = leds + 0x8000;
  }

  //delay(2 * msDelay);

  if (cnt++ >= 2) {
    cnt = 0;
    nextPattern();
  }
}








void effect7() {
  uint16_t leds = 0;
  static uint8_t cnt = 0;

  for (int i = 0; i < 16; i++) {
    leds = (1 << i);
    shiftOut16(leds);
    delay(msDelay);
  }

  shiftOut16(0xFFFF);
  delay(3 * msDelay);
  shiftOut16(0x00);
  delay(msDelay);

  for (int i = 0; i < 16; i++) {
    leds = (3 << i);
    shiftOut16(leds);
    delay(msDelay);
  }

  shiftOut16(0xFFFF);
  delay(3 * msDelay);
  shiftOut16(0x00);
  delay(msDelay);

  if (cnt++ >= 1) {
    cnt = 0;
    nextPattern();
  }
}








void effect8() {
  uint16_t leds = 0;
  uint8_t rnd1 = random(0, 15);
  static uint8_t cnt = 0;

  uint8_t rnd2 = rnd1;

  while (abs(rnd2 - rnd1) < 5) rnd2 = random(0, 15);

  if (rnd1 < rnd2) {
    for (int i = rnd1; i < rnd2; i++) {
      leds = leds + (1 << i);
      shiftOut16(leds);
      delay(msDelay);
    }
  }

  if (rnd1 > rnd2) {
    for (int i = rnd1; i >= rnd2; i--) {
      leds = leds + (1 << i);
      shiftOut16(leds);
      delay(msDelay);
    }
  }

  if (cnt++ >= 10) {
    cnt = 0;
    nextPattern();
  }
}

