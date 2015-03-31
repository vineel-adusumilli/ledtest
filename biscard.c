#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 8000000UL
#include <util/delay.h>

#define ENABLE(DDRk, PINk) DDR ## DDRk |= (1 << P ## DDRk ## PINk)
#define DISABLE(DDRk, PINk) DDR ## DDRk &= ~(1 << P ## DDRk ## PINk)

#define HIGH(PORTk, PINk) PORT ## PORTk |= (1 << P ## PORTk ## PINk)
#define LOW(PORTk, PINk) PORT ## PORTk &= ~(1 << P ## PORTk ## PINk)

void enable(uint8_t pin) {
  switch (pin) {
    case 0:
      ENABLE(C, 1);
      break;
    case 1:
      ENABLE(C, 0);
      break;
    case 2:
      ENABLE(B, 2);
      break;
    case 3:
      ENABLE(B, 1);
      break;
    case 4:
      ENABLE(B, 0);
      break;
    case 5:
      ENABLE(D, 7);
      break;
    case 6:
      ENABLE(D, 6);
      break;
    case 7:
      ENABLE(D, 5);
      break;
    case 8:
      ENABLE(B, 7);
      break;
  }
}

void disable(uint8_t pin) {
  switch (pin) {
    case 0:
      DISABLE(C, 1);
      break;
    case 1:
      DISABLE(C, 0);
      break;
    case 2:
      DISABLE(B, 2);
      break;
    case 3:
      DISABLE(B, 1);
      break;
    case 4:
      DISABLE(B, 0);
      break;
    case 5:
      DISABLE(D, 7);
      break;
    case 6:
      DISABLE(D, 6);
      break;
    case 7:
      DISABLE(D, 5);
      break;
    case 8:
      DISABLE(B, 7);
      break;
  }
}

void high(uint8_t pin) {
  switch (pin) {
    case 0:
      HIGH(C, 1);
      break;
    case 1:
      HIGH(C, 0);
      break;
    case 2:
      HIGH(B, 2);
      break;
    case 3:
      HIGH(B, 1);
      break;
    case 4:
      HIGH(B, 0);
      break;
    case 5:
      HIGH(D, 7);
      break;
    case 6:
      HIGH(D, 6);
      break;
    case 7:
      HIGH(D, 5);
      break;
    case 8:
      HIGH(B, 7);
      break;
  }
}

void low(uint8_t pin) {
  switch (pin) {
    case 0:
      LOW(C, 1);
      break;
    case 1:
      LOW(C, 0);
      break;
    case 2:
      LOW(B, 2);
      break;
    case 3:
      LOW(B, 1);
      break;
    case 4:
      LOW(B, 0);
      break;
    case 5:
      LOW(D, 7);
      break;
    case 6:
      LOW(D, 6);
      break;
    case 7:
      LOW(D, 5);
      break;
    case 8:
      LOW(B, 7);
      break;
  }
}

void on(uint8_t pin1, uint8_t pin2) {
  enable(pin1);
  enable(pin2);
  high(pin1);
}

void off(uint8_t pin1, uint8_t pin2) {
  disable(pin1);
  disable(pin2);
  low(pin1);
}

void flash(uint8_t pin1, uint8_t pin2) {
  uint8_t x = pin1;
  uint8_t y = pin1 + pin2 < 8 ? 8 - pin2 : 7 - pin2;
  on(x, y);
  _delay_ms(100);
  off(x, y);
}

void light(uint8_t x, uint8_t y) {
  uint8_t pin1 = x;
  uint8_t pin2 = x + y < 8 ? 8 - y : 7 - y;
  on(pin1, pin2);
}

void unlight(uint8_t x, uint8_t y) {
  uint8_t pin1 = x;
  uint8_t pin2 = x + y < 8 ? 8 - y : 7 - y;
  off(pin1, pin2);
}

int main() {
  HIGH(D, 2); // pull up the button

  uint8_t i, j;
  while (1) {
    for (j = 0; j < 8; j++) {
      for (i = 0; i < 8; i++) {
        light(i, j);
        while (1) {
          if (!(PIND & (1 << PD2))) {
            _delay_ms(100);
            if (!(PIND & (1 << PD2)))
              break;
          }
        }
        unlight(i, j);
      }
    }
  }
  
  return 1;
}
