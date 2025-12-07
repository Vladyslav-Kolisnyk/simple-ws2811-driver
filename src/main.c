#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>
#include <stdlib.h>
#include <stdint.h>

#include "ws2811_driver.h"

int main(void)
{
  struct Strip mystrip = initStrip(112, &PORTB, 1);

  clearStrip(mystrip);
  showStrip(mystrip);

  _delay_ms(500);

  for (int i = 0; i < mystrip.numLeds; i++)
  {
    if (i % 2 == 0)
    {
      mystrip.ledsArray[i] = setRGB(100, 0, 0);
    }
    else
    {
      mystrip.ledsArray[i] = setRGB(0, 100, 0);
    }
  showStrip(mystrip);
  }
}
