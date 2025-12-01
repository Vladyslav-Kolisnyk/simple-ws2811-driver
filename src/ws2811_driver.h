#ifndef ws2811_driver_h
#define ws2811_driver_h

#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#include <stdlib.h>
#include <stdint.h>

#define LED_PORT PORTB
#define LED_DDR DDRB
#define LED_PIN PORTB1

struct RGB {
  uint8_t redBits;
  uint8_t greenBits;
  uint8_t blueBits;
};

struct RGB setRGB(uint8_t r, uint8_t g, uint8_t b);

struct RGB* initStrip(uint8_t numLeds);

void showStrip(struct RGB* strip, uint8_t numLeds);

void clearStrip(struct RGB* strip, uint8_t numLeds);

#endif
