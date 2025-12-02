#ifndef ws2811_driver_h
#define ws2811_driver_h

#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#include <stdlib.h>
#include <stdint.h>

#include "globals.h"

struct RGB {
  uint8_t redBits;
  uint8_t greenBits;
  uint8_t blueBits;
};

struct RGB setRGB(uint8_t r, uint8_t g, uint8_t b);

struct RGB* initStrip();

void showStrip(struct RGB* strip);

void clearStrip(struct RGB* strip);

#endif
