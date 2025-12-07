#ifndef ws2811_driver_h
#define ws2811_driver_h

#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#include <stdlib.h>
#include <stdint.h>

struct RGB {
  uint8_t redBits;
  uint8_t greenBits;
  uint8_t blueBits;
};

struct Strip
{
  uint8_t numLeds;
  uint8_t ledPIN;
  volatile uint8_t* ledPORT;
  struct RGB* ledsArray;
};

struct RGB setRGB(uint8_t r, uint8_t g, uint8_t b);

struct Strip initStrip(uint32_t numLeds, volatile uint8_t* ledPORT, uint8_t ledPIN);

void showStrip(struct Strip strip);

void clearStrip(struct Strip strip);

#endif
