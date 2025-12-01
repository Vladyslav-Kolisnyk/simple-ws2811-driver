#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#include <stdlib.h>
#include <stdint.h>

#include "ws2811_driver.h"

int main(void)
{
  LED_DDR = LED_DDR | (1 << LED_PIN);
  
  uint8_t numLeds = 112;

  struct RGB* mystrip = initStrip(numLeds);

  clearStrip(mystrip, numLeds);
  showStrip(mystrip, numLeds);

  _delay_ms(500);

  for (int i = 0; i < numLeds; i++)
  {
    if (i % 2 == 0)
    {
      mystrip[i] = setRGB(100, 200, 0);
    }
    else
    {
      mystrip[i] = setRGB(0, 100, 100);
    }
    
    showStrip(mystrip, numLeds);
  }

  free(mystrip);
}
