void effect1() {
  uint16_t leds = 0;
  static uint8_t count = 0;
  static uint8_t speedUp = 0;

  for (int i = 0; i < 6; i++) {
    leds = leds + (1 << i);
    shiftOut16(leds);
    delay(msDelay - speedUp);
  }

  for (int i = 0; i <= 6; i++) {
    leds = leds & (0xFFFF << i);
    shiftOut16(leds);
    delay(msDelay - speedUp);
  }

  delay(msDelay);
  speedUp += 50;

  if (count++ >= 5)  {
    count = 0;
    speedUp = 0;
    nextPattern();
  }
}




void effect2() {
  uint16_t leds = 0;
  static uint8_t count = 0;

  for (int i = 0; i < 6; i++) {
    leds = (1 << i);
    shiftOut16(leds);
    delay(msDelay);
  }

  shiftOut16(0x3F);
  delay(msDelay / 2);
  shiftOut16(0x00);
  delay(msDelay / 2);

  if (count++ >= 2)  {
    count = 0;
    nextPattern();
  }
}





void effect3() {
  uint16_t leds = 0;
  static uint8_t count = 0;

  for (int i = 0; i < 6; i++) {
    leds = ~(1 << i);
    shiftOut16(leds);
    delay(msDelay);
  }

  if (count++ >= 5)  {
    count = 0;
    nextPattern();
  }
}



void effect4() {
  uint16_t leds = 0;
  static uint8_t count = 0;
  uint8_t c = 0;


  for (int i = 0; i < 12; i++) {
    if (i % 2) {
//      shiftOut16(0x3F);
//      delay(msDelay / 2);
      shiftOut16(0x00);
      delay(msDelay / 2);
    }
    else {
      shiftOut16(1 << c);
      delay(msDelay / 2);
      c++;
    }
  }

  if (count++ >= 3)  {
    count = 0;
    nextPattern();
  }

}



