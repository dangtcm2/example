#define DATA_PIN 1

#define CLR(x,y) (x&=(~(1<<y)))
#define SET(x,y) (x|=(1<<y))

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

void setup() {
  // put your setup code here, to run once:
  SET(DDRB, 0); //MOSI OUTPUT
  SET(DDRB, 1); //LED_OUT OUTPUT
  SET(DDRB, 3); //LATCH OUTPUT
  SET(DDRB, 4); //SCK OUTPUT
}

void loop() {
  // put your main code here, to run repeatedly:
  checkLedOut();
}

void checkLedOut() {
  shiftOut16(0xFFFF);
  SET(PORTB, 1); delay(100);
  CLR(PORTB, 1); delay(100);
}

