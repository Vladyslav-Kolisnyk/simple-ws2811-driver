#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#include <stdlib.h>
#include <stdint.h>

struct RGB 
{
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

void sendOne(volatile uint8_t* ledPORT, uint8_t ledPIN)
{
  *ledPORT = *ledPORT | (1 << ledPIN);
  asm volatile("nop\nnop\n");
  *ledPORT = *ledPORT &~ (1 << ledPIN);
  asm volatile("nop\nnop\nnop\nnop\n");
}

void sendZero(volatile uint8_t* ledPORT, uint8_t ledPIN)
{
  *ledPORT = *ledPORT | (1 << ledPIN);
  *ledPORT = *ledPORT &~ (1 << ledPIN);
  asm volatile("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");
}

void reset(volatile uint8_t* ledPORT, uint8_t ledPIN)
{
  *ledPORT = *ledPORT &~ (1 << ledPIN);
  _delay_us(60);
}

void sendByte(uint8_t colorValue, volatile uint8_t* ledPORT, uint8_t ledPIN)
{
  uint8_t bit;

  for (int i = 7; i >= 0; i--) {
    bit = (colorValue >> i) & 1;
    
    if (bit == 0)
    {
      sendZero(ledPORT, ledPIN);
    }
    else if (bit == 1)
    {
      sendOne(ledPORT, ledPIN);
    }
  }
}

void sendPixel(struct RGB rgb, volatile uint8_t* ledPORT, uint8_t ledPIN)
{
  sendByte(rgb.greenBits, ledPORT, ledPIN);
  sendByte(rgb.redBits, ledPORT, ledPIN);
  sendByte(rgb.blueBits, ledPORT, ledPIN);
}

struct RGB setRGB(uint8_t r, uint8_t g, uint8_t b)
{
  struct RGB rgb;
  
  rgb.redBits = r;
  rgb.greenBits = g;
  rgb.blueBits = b;

  return rgb;
}

struct Strip initStrip(uint32_t numLeds, volatile uint8_t* ledPORT, uint8_t ledPIN)
{
  *(ledPORT - 1) = *(ledPORT - 1) | (1 << ledPIN);

  struct Strip strip;

  strip.ledsArray = (struct RGB*)malloc(numLeds * sizeof(struct RGB));

  for (int i = 0; i < numLeds; i++)
  {
    strip.ledsArray[i] = setRGB(0, 0, 0);
  }

  strip.numLeds = numLeds;
  strip.ledPIN = ledPIN;
  strip.ledPORT = ledPORT;

  return strip;
}

void showStrip(struct Strip strip)
{
  for (int i = 0; i < strip.numLeds; i++)
  {
    sendPixel(strip.ledsArray[i], strip.ledPORT, strip.ledPIN);
  }

  reset(strip.ledPORT, strip.ledPIN);
}

void clearStrip(struct Strip strip)
{
  for (int i = 0; i < strip.numLeds; i++)
  {
    strip.ledsArray[i] = setRGB(0, 0, 0);
  }
}
