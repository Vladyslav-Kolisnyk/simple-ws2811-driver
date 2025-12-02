#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#include <stdlib.h>
#include <stdint.h>

#include "ws2811_driver.h"
#include "globals.h" 

int main(void)
{
  struct RGB* mystrip = initStrip();

  clearStrip(mystrip);
  showStrip(mystrip);

  _delay_ms(500);

  for (int i = 0; i < NUM_LEDS; i++)
  {
    if (i % 2 == 0)
    {
      mystrip[i] = setRGB(100, 200, 0);
    }
    else
    {
      mystrip[i] = setRGB(0, 100, 100);
    }
    
    showStrip(mystrip);
  }

  free(mystrip);
}
