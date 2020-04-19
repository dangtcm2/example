#define CLR(x,y) (x&=(~(1<<y)))
#define SET(x,y) (x|=(1<<y))

uint16_t msDelay = 100;
volatile uint16_t cnt = 0;

void setup() {
  // put your setup code here, to run once:
  SET(DDRB, 0); //MOSI OUTPUT
  CLR(DDRB, 1);
  CLR(DDRB, 2);
  SET(DDRB, 3); //LATCH OUTPUT
  SET(DDRB, 4); //SCK OUTPUT
}

void shiftOut16(uint16_t srData) {

  uint16_t mask = 0x8000;

  CLR(PORTB, 3); //LATCH LOW

  for (int i = 0; i < 16; i++) {
    if (mask & srData) SET(PORTB, 0); else CLR(PORTB, 0); //16-BIT DATA OUT
    SET(PORTB, 4); //CLK HIGH
    CLR(PORTB, 4); //CLK LOW
    mask = mask >> 1;
  }

  SET(PORTB, 3); //LATCH HIGH
}

typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = {effect1, effect2, effect3, effect4, effect5, effect6, effect7, effect8};

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current

void loop() {
  gPatterns[gCurrentPatternNumber]();
}

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns);
}


