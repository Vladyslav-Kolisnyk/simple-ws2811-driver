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

void sendOne()
{
  LED_PORT = LED_PORT | (1 << LED_PIN);
  asm volatile("nop\nnop\nnop\nnop\nnop\nnop\n");
  LED_PORT = LED_PORT &~ (1 << LED_PIN);
  asm volatile("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");
}

void sendZero()
{
  LED_PORT = LED_PORT | (1 << LED_PIN);
  asm volatile("nop\nnop\n");
  LED_PORT = LED_PORT &~ (1 << LED_PIN);
  asm volatile("nop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\nnop\n");
}

void reset()
{
  LED_PORT = LED_PORT &~ (1 << LED_PIN);
  _delay_us(60);
}

void sendByte(uint8_t colorValue)
{
  uint8_t bit;

  for (int i = 7; i >= 0; i--) {
    bit = (colorValue >> i) & 1;
    
    if (bit == 0)
    {
      sendZero();
    }
    else if (bit == 1)
    {
      sendOne();
    }
  }
}

void sendPixel(struct RGB rgb)
{
  sendByte(rgb.greenBits);
  sendByte(rgb.redBits);
  sendByte(rgb.blueBits);
}

struct RGB setRGB(uint8_t r, uint8_t g, uint8_t b)
{
  struct RGB rgb;
  
  rgb.redBits = r;
  rgb.greenBits = g;
  rgb.blueBits = b;

  return rgb;
}

struct RGB* initStrip(uint8_t numLeds)
{
  struct RGB* strip = (struct RGB*)malloc(numLeds * sizeof(struct RGB));

  for (int i = 0; i < numLeds; i++)
  {
    strip[i] = setRGB(0, 0, 0);
  }  
  
  return strip;
}

void showStrip(struct RGB* strip, uint8_t numLeds)
{
  for (int i = 0; i < numLeds; i++)
  {
   sendPixel(strip[i]);
  }

  reset();
}

void clearStrip(struct RGB* strip, uint8_t numLeds)
{
  for (int i = 0; i < numLeds; i++)
  {
    strip[i] = setRGB(0, 0, 0);
  }
}
