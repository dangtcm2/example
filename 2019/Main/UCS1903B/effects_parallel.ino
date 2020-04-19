void parallel_1(uint8_t dly) {
  uint8_t h = 0;
  static uint8_t pos = 0;
  uint8_t count = 0;

  if (bSwitched) clearMatrix();

  for (uint8_t i = pos; i >= 0; i--) {
    if ((count < 13) && (i < PIXELS)) rowData[i] = parallel_pattern1[count];
    if ((count == 13) && (i < PIXELS)) rowData[i] = 0x00;

    count++;
    if (count > 13) {
      count = 0;
      h += 50;
    }

    if (!i) break;
  }

  pos++;
  if (pos >= 5 * PIXELS) pos = PIXELS + 2; //DEPENDS ON HUE INCREASEMENT, NEEDS EXPERIMENT TO FIGURE OUT

  showMatrix();
  delay((uint8_t)(dly * 1.2));
}

void parallel_1_reverse(uint8_t dly) {
  uint8_t h = 0;
  static uint8_t pos = 0;
  uint8_t count = 0;

  if (bSwitched) clearMatrix();

  for (uint8_t i = pos; i > 0; i--) {
    if ((count < 13) && (i <= PIXELS)) rowData[PIXELS - i] = parallel_pattern1[count];
    if ((count == 13) && (i <= PIXELS)) rowData[PIXELS - i] = 0x00;

    count++;
    if (count > 13) {
      count = 0;
      h += 50;
    }

    if (!i) break;
  }

  pos++;
  if (pos >= 5 * PIXELS) pos = PIXELS + 2;

  showMatrix();
  delay((uint8_t)(dly * 1.2));
}

void parallel_2(uint8_t dly) {
  uint8_t h = 0;
  static uint8_t pos = 0;
  uint8_t count = 0;

  if (bSwitched) clearMatrix();

  for (uint8_t i = pos; i >= 0; i--) {
    if ((count < 13) && (i < PIXELS)) rowData[i] = parallel_pattern2[count];
    if ((count == 13) && (i < PIXELS)) rowData[i] = 0x00;

    count++;
    if (count > 13) {
      count = 0;
      h += 50;
    }

    if (!i) break;
  }

  pos++;
  if (pos >= 5 * PIXELS) pos = PIXELS + 2; //DEPENDS ON HUE INCREASEMENT, NEEDS EXPERIMENT TO FIGURE OUT

  showMatrix();
  delay((uint8_t)(dly * 1.4));
}
