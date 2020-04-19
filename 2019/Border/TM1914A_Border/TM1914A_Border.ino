
#define PIXELS 100
#define EFFECTS 8


#define T1H  360    // Width of a 1 bit in ns
#define T1L  900    // Width of a 1 bit in ns

#define T0H  800    // Width of a 0 bit in ns
#define T0L  350    // Width of a 0 bit in ns

#define RES 6000    // Width of the low gap between bits to cause a frame to latch

// Here are some convience defines for using nanoseconds specs to generate actual CPU delays

#define NS_PER_SEC (1000000000L)          // Note that this has to be SIGNED since we want to be able to check for negative values of derivatives

#define CYCLES_PER_SEC (F_CPU)

#define NS_PER_CYCLE ( NS_PER_SEC / CYCLES_PER_SEC )

#define NS_TO_CYCLES(n) ( (n) / NS_PER_CYCLE )

uint8_t pixels_r[PIXELS], pixels_g[PIXELS], pixels_b[PIXELS];
uint8_t pixels_h[PIXELS], pixels_s[PIXELS], pixels_v[PIXELS];
uint8_t rowData[PIXELS];
uint8_t masterColor[3] = {0, 0, 0};
uint8_t masterDelay = 40;
uint8_t effectRelease = 0;
uint32_t sysTime = 0;
uint8_t bSwitched = 0;
uint8_t effectId = 0;

uint8_t parallel_pattern1[13] = {0xFF, 0x45, 0x12, 0x00, 0x21, 0x84, 0x1A, 0x40, 0x00, 0x21, 0x88, 0x46, 0x91};
uint8_t parallel_pattern2[13] = {0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF};

volatile

static inline void __attribute__ ((always_inline)) sendBitX8_B( uint8_t bitx8 ) {

  const uint8_t onBits = 0xff;
  uint8_t bits = ~bitx8;          // The bits were inverted because TM1914A uses the opposite encoding signal than NeoPixel

  asm volatile (                        // The below asm code has been modified to match TM1914A timing

    "out %[port],__zero_reg__  \n\t"        // 1st step - all bits low

    ".rept %[T0LCycles] \n\t"               // Execute NOPs to delay exactly the specified T0L number of cycles
    "nop \n\t"
    ".endr \n\t"

    "out %[port], %[bits] \n\t"             // Set the output bits to thier values

    ".rept %[dataCycles] \n\t"               // Execute NOPs to delay exactly the specified number of cycles
    "nop \n\t"
    ".endr \n\t"

    "out %[port], %[onBits] \n\t"           // last step - all bits high in T1H long

    /*
    ".rept %[T1HCycles] \n\t"               // Execute NOPs to delay exactly the specified T1H number of cycles
    "nop \n\t"
    ".endr \n\t"
    */

    // Don't need an explicit delay here since the overhead that follows will always be long enough

    ::
    [port]    "I" (_SFR_IO_ADDR(PORTB)),

    [T0LCycles]  "I" (NS_TO_CYCLES(T0L) - 2),           // 1-bit width less overhead  for the actual bit setting, note that this delay could be longer and everything would still work

    [bits]   "d" (bits),

    [dataCycles]   "I" (NS_TO_CYCLES(T1L-T0L) - 2),   // Minimum interbit delay. Note that we probably don't need this at all since the loop overhead will be enough, but here for correctness

    [onBits]   "d" (onBits),

    [T1HCycles]  "I" (NS_TO_CYCLES(T1H) - 2)

  );


  // Note that the inter-bit gap can be as long as you want as long as it doesn't exceed the reset timeout (which is A long time)

}

static inline void __attribute__ ((always_inline)) sendBitX8_C( uint8_t bitx8 ) {

  const uint8_t onBits = 0xff;
  uint8_t bits = ~bitx8;          // The bits were inverted because TM1914A uses the opposite encoding signal than NeoPixel

  asm volatile (                        // The below asm code has been modified to match TM1914A timing

    "out %[port],__zero_reg__  \n\t"        // 1st step - all bits low

    ".rept %[T0LCycles] \n\t"               // Execute NOPs to delay exactly the specified T0L number of cycles
    "nop \n\t"
    ".endr \n\t"

    "out %[port], %[bits] \n\t"             // Set the output bits to thier values

    ".rept %[dataCycles] \n\t"               // Execute NOPs to delay exactly the specified number of cycles
    "nop \n\t"
    ".endr \n\t"

    "out %[port], %[onBits] \n\t"           // last step - all bits high in T1H long

    /*
    ".rept %[T1HCycles] \n\t"               // Execute NOPs to delay exactly the specified T1H number of cycles
    "nop \n\t"
    ".endr \n\t"
    */

    // Don't need an explicit delay here since the overhead that follows will always be long enough

    ::
    [port]    "I" (_SFR_IO_ADDR(PORTC)),

    [T0LCycles]  "I" (NS_TO_CYCLES(T0L) - 2),           // 1-bit width less overhead  for the actual bit setting, note that this delay could be longer and everything would still work

    [bits]   "d" (bits),

    [dataCycles]   "I" (NS_TO_CYCLES(T1L-T0L) - 2),   // Minimum interbit delay. Note that we probably don't need this at all since the loop overhead will be enough, but here for correctness

    [onBits]   "d" (onBits),

    [T1HCycles]  "I" (NS_TO_CYCLES(T1H) - 2)

  );


  // Note that the inter-bit gap can be as long as you want as long as it doesn't exceed the reset timeout (which is A long time)

}

static inline void __attribute__ ((always_inline)) sendBitX8_D( uint8_t bitx8 ) {

  const uint8_t onBits = 0xff;
  uint8_t bits = ~bitx8;          // The bits were inverted because TM1914A uses the opposite encoding signal than NeoPixel

  asm volatile (                        // The below asm code has been modified to match TM1914A timing

    "out %[port],__zero_reg__  \n\t"        // 1st step - all bits low

    ".rept %[T0LCycles] \n\t"               // Execute NOPs to delay exactly the specified T0L number of cycles
    "nop \n\t"
    ".endr \n\t"

    "out %[port], %[bits] \n\t"             // Set the output bits to thier values

    ".rept %[dataCycles] \n\t"               // Execute NOPs to delay exactly the specified number of cycles
    "nop \n\t"
    ".endr \n\t"

    "out %[port], %[onBits] \n\t"           // last step - all bits high in T1H long

    /*
    ".rept %[T1HCycles] \n\t"               // Execute NOPs to delay exactly the specified T1H number of cycles
    "nop \n\t"
    ".endr \n\t"
    */

    // Don't need an explicit delay here since the overhead that follows will always be long enough

    ::
    [port]    "I" (_SFR_IO_ADDR(PORTD)),

    [T0LCycles]  "I" (NS_TO_CYCLES(T0L) - 2),           // 1-bit width less overhead  for the actual bit setting, note that this delay could be longer and everything would still work

    [bits]   "d" (bits),

    [dataCycles]   "I" (NS_TO_CYCLES(T1L-T0L) - 2),   // Minimum interbit delay. Note that we probably don't need this at all since the loop overhead will be enough, but here for correctness

    [onBits]   "d" (onBits),

    [T1HCycles]  "I" (NS_TO_CYCLES(T1H) - 2)

  );


  // Note that the inter-bit gap can be as long as you want as long as it doesn't exceed the reset timeout (which is A long time)

}

static inline void __attribute__ ((always_inline)) sendCommand_B() {

  // Send the C1 (0xFF 0xFF 0xFF) and C2 (0x00 0x00 0x00)

  uint8_t bit = 24;

  while (bit--) {

    sendBitX8_B( 0x03 ); //use only PB0 - PB1.
  }

  bit = 24;

  while (bit--) {

    sendBitX8_B( 0x00 );
  }

}

static inline void __attribute__ ((always_inline)) sendCommand_C() {

  // Send the C1 (0xFF 0xFF 0xFF) and C2 (0x00 0x00 0x00)

  uint8_t bit = 24;

  while (bit--) {

    sendBitX8_C( 0x3F ); //use only PC0 - PC5. PC6 is reserved for RESET.
  }

  bit = 24;

  while (bit--) {

    sendBitX8_C( 0x00 );
  }

}

static inline void __attribute__ ((always_inline)) sendCommand_D() {

  // Send the C1 (0xFF 0xFF 0xFF) and C2 (0x00 0x00 0x00)

  uint8_t bit = 24;

  while (bit--) {

    sendBitX8_D( 0xFF ); //use entire PORTD, PD0 - PD7.
  }

  bit = 24;

  while (bit--) {

    sendBitX8_D( 0x00 );
  }

}

inline void sendByteX8_B( unsigned char byte ) {

  for ( unsigned char bit = 0 ; bit < 8 ; bit++ ) {

    if bitRead( byte , 7 ) {
      sendBitX8_B(0x03);   // Read the MSB, if it's a 1-bit then we send '1' to 2 pins of PORTB
    }
    else  {
      sendBitX8_B(0x00);
    }

    byte <<= 1;            // Bring the next bit to MSB position

  }
}

inline void sendByteX8_C( unsigned char byte ) {

  for ( unsigned char bit = 0 ; bit < 8 ; bit++ ) {

    if bitRead( byte , 7 ) {
      sendBitX8_C(0x3F);   // Read the MSB, if it's a 1-bit then we send '1' to 6 pins of PORTC
    }
    else  {
      sendBitX8_C(0x00);
    }

    byte <<= 1;            // Bring the next bit to MSB position

  }
}

inline void sendByteX8_D( unsigned char byte ) {

  for ( unsigned char bit = 0 ; bit < 8 ; bit++ ) {

    if bitRead( byte , 7 ) {
      sendBitX8_D(0xFF);   // Read the MSB, if it's a 1-bit then we send '1' to all 8 pins (write 0xFF to PORTx)
    }
    else  {
      sendBitX8_D(0x00);
    }

    byte <<= 1;           // Bring the next bit to MSB position

  }
}

inline void sendPixelX8_B( unsigned char r, unsigned char g , unsigned char b )  {

  sendByteX8_B(r);          // TM1914A uses R-G-B color order
  sendByteX8_B(g);
  sendByteX8_B(b);

}

inline void sendPixelX8_C( unsigned char r, unsigned char g , unsigned char b )  {

  sendByteX8_C(r);          // TM1914A uses R-G-B color order
  sendByteX8_C(g);
  sendByteX8_C(b);

}

inline void sendPixelX8_D( unsigned char r, unsigned char g , unsigned char b )  {

  sendByteX8_D(r);          // TM1914A uses R-G-B color order
  sendByteX8_D(g);
  sendByteX8_D(b);

}

static inline void __attribute__ ((always_inline)) sendPixelRow_B( uint8_t row, uint8_t r, uint8_t g, uint8_t b ) {

  uint8_t mask;

  if (!row) {
    for (uint8_t i = 0; i < 24; i++) {
      sendBitX8_B(0x00);
    }
    return;
  }
  else {
    //send R
    for (uint8_t bit = 0; bit < 8; bit++) {
      mask = (0x80 >> bit);
      if (r & mask) sendBitX8_B((row >> 6)); else sendBitX8_B(0x00);
    }

    //send G
    for (uint8_t bit = 0; bit < 8; bit++) {
      mask = (0x80 >> bit);
      if (g & mask) sendBitX8_B((row >> 6)); else sendBitX8_B(0x00);
    }

    //send B
    for (uint8_t bit = 0; bit < 8; bit++) {
      mask = (0x80 >> bit);
      if (b & mask) sendBitX8_B((row >> 6)); else sendBitX8_B(0x00);
    }
  }
}

static inline void __attribute__ ((always_inline)) sendPixelRow_C( uint8_t row, uint8_t r, uint8_t g, uint8_t b ) {

  uint8_t mask;

  if (!row) {
    for (uint8_t i = 0; i < 24; i++) {
      sendBitX8_C(0x00);
    }
    return;
  }
  else {
    //send R
    for (uint8_t bit = 0; bit < 8; bit++) {
      mask = (0x80 >> bit);
      if (r & mask) sendBitX8_C((row & 0x3F)); else sendBitX8_C(0x00);
    }

    //send G
    for (uint8_t bit = 0; bit < 8; bit++) {
      mask = (0x80 >> bit);
      if (g & mask) sendBitX8_C((row & 0x3F)); else sendBitX8_C(0x00);
    }

    //send B
    for (uint8_t bit = 0; bit < 8; bit++) {
      mask = (0x80 >> bit);
      if (b & mask) sendBitX8_C((row & 0x3F)); else sendBitX8_C(0x00);
    }
  }
}

static inline void __attribute__ ((always_inline)) sendPixelRow_D( uint8_t row, uint8_t r, uint8_t g, uint8_t b ) {

  uint8_t mask;

  if (!row) {
    for (uint8_t i = 0; i < 24; i++) {
      sendBitX8_D(0x00);
    }
    return;
  }
  else {
    //send R
    for (uint8_t bit = 0; bit < 8; bit++) {
      mask = (0x80 >> bit);
      if (r & mask) sendBitX8_D(row); else sendBitX8_D(0x00);
    }

    //send G
    for (uint8_t bit = 0; bit < 8; bit++) {
      mask = (0x80 >> bit);
      if (g & mask) sendBitX8_D(row); else sendBitX8_D(0x00);
    }

    //send B
    for (uint8_t bit = 0; bit < 8; bit++) {
      mask = (0x80 >> bit);
      if (b & mask) sendBitX8_D(row); else sendBitX8_D(0x00);
    }
  }
}

void show() {
  _delay_us( (RES / 1000UL) + 1);       // Round up since the delay must be _at_least_ this long (too short might not work, too long not a problem)
}


void showArray() {
  cli();

  sendCommand_B();
  sendCommand_C();
  sendCommand_D();
  for ( int p = 0; p < PIXELS; p++ ) {
    sendPixelX8_B( pixels_r[p] , pixels_g[p] , pixels_b[p] );
    sendPixelX8_C( pixels_r[p] , pixels_g[p] , pixels_b[p] );
    sendPixelX8_D( pixels_r[p] , pixels_g[p] , pixels_b[p] );
  }

  show();
  sei();

}

void showMatrix() {
  cli();

  sendCommand_B();
  for ( int p = 0; p < PIXELS; p++ ) {
    sendPixelRow_B(rowData[p], pixels_r[p] , pixels_g[p] , pixels_b[p]);
  }
  show();

  sendCommand_C();
  for ( int p = 0; p < PIXELS; p++ ) {
    sendPixelRow_C(rowData[p], pixels_r[p] , pixels_g[p] , pixels_b[p]);
  }
  show();

  sendCommand_D();
  for ( int p = 0; p < PIXELS; p++ ) {
    sendPixelRow_D(rowData[p], pixels_r[p] , pixels_g[p] , pixels_b[p]);
  }
  show();

  sei();
}

static inline void __attribute__ ((always_inline)) clearArray() {
  memset(pixels_r, 0, sizeof(pixels_r));
  memset(pixels_g, 0, sizeof(pixels_g));
  memset(pixels_b, 0, sizeof(pixels_b));
  memset(pixels_h, 0, sizeof(pixels_h));
  memset(pixels_s, 0, sizeof(pixels_s));
  memset(pixels_v, 0, sizeof(pixels_v));

}

static inline void __attribute__ ((always_inline)) clearMatrix() {
  memset(masterColor, 0, sizeof(masterColor));
  memset(rowData, 0, sizeof(rowData));
}


void setup() {

  DDRD = 0xff;    // Set all row pins to output
  PORTD = 0xff;   // Set all row pins to high (signal line of TM1914A is normally high)
  DDRC = 0x3f;    // Set all row pins to output
  PORTC = 0x3f;   // Set all row pins to high (signal line of TM1914A is normally high)
  DDRB = 0x03;    // Set all row pins to output
  PORTB = 0x03;   // Set all row pins to high (signal line of TM1914A is normally high)

  effectId = 0;

  sysTime = millis();
}

uint8_t realRandom() {
  return (uint8_t)(analogRead(A7) + random(128));
}


void loop() {
  uint32_t currentTime = millis();

  uint8_t adc = analogRead(A6);

  masterDelay = 50 - (uint8_t)(adc / 10);

  //shine2(masterDelay);
  //shine2_reverse(masterDelay);

  //hueWalk(masterDelay);

  //shine1(masterDelay);
  //shine1_reverse(masterDelay);

  //rainbow((255/PIXELS)*8);
  //showArray();

  //shine6(masterDelay);
  //shine6_reverse(masterDelay);

  //return;

  if ((currentTime - sysTime  >= 6000UL) && (effectRelease == 0)) {
    effectId++;
    clearArray();
    sysTime = currentTime;
    bSwitched = 1;
  }

  doEffects(effectId % EFFECTS);

  bSwitched = 0;

}

void doEffects(uint8_t id) {
  static uint8_t lastId = 0;


  switch (id) {
    case 0:
      rainbow((255 / PIXELS) * 8);
      showArray();
      break;
    case 1:
      shine1(masterDelay);
      break;
    case 2:
      shine2_reverse(masterDelay);
      break;
    case 3:
      hueWalk(masterDelay);
      break;
    case 4:
      shine6(masterDelay);
      break;
    case 5:
      shine1_reverse(masterDelay);
      break;
    case 6:
      shine2(masterDelay);
      break;
    case 7:
      shine6_reverse(masterDelay);
      break;
    default:
      break;
  }

  lastId = id;
}
