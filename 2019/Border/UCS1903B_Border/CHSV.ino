uint8_t r0, g0, b0;

static inline void hsv2rgb(uint8_t h, uint8_t s, uint8_t v, uint8_t *r, uint8_t *g, uint8_t *b) {
  // this is the algorithm to convert from RGB to HSV
  h = (h * 192) / 256;  // 0..191
  unsigned int i = h / 32;   // We want a value of 0 thru 5
  unsigned int f = (h % 32) * 8;   // 'fractional' part of 'i' 0..248 in jumps

  unsigned int sInv = 255 - s;  // 0 -> 0xff, 0xff -> 0
  unsigned int fInv = 255 - f;  // 0 -> 0xff, 0xff -> 0
  byte pv = v * sInv / 256;  // pv will be in range 0 - 255
  byte qv = v * (256 - s * f / 256) / 256;
  byte tv = v * (256 - s * fInv / 256) / 256;

  switch (i) {
    case 0:
      r0 = v;
      g0 = tv;
      b0 = pv;
      break;
    case 1:
      r0 = qv;
      g0 = v;
      b0 = pv;
      break;
    case 2:
      r0 = pv;
      g0 = v;
      b0 = tv;
      break;
    case 3:
      r0 = pv;
      g0 = qv;
      b0 = v;
      break;
    case 4:
      r0 = tv;
      g0 = pv;
      b0 = v;
      break;
    case 5:
      r0 = v;
      g0 = pv;
      b0 = qv;
      break;
  }

  *r = r0;
  *g = g0;
  *b = b0;
}

void setPixelHSV(uint8_t pos, uint8_t h, uint8_t s, uint8_t v) {

//  Serial.print("Set ");
//  Serial.print(pos);
//  Serial.print(", ");
//  Serial.println(h);
//
//  return;
  
  pixels_h[pos] = h;
  pixels_s[pos] = s;
  pixels_v[pos] = v;
  hsv2rgb(h, s, v, &pixels_r[pos], &pixels_g[pos], &pixels_b[pos]);
}

inline uint8_t getPixelHue(uint8_t pos) {
  return  pixels_h[pos];
}

