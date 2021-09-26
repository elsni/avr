/*
* Light_WS2812 library example - RGB_blinky
*
* cycles one LED through red, green, blue
*
* This example is configured for a ATtiny85 with PLL clock fuse set and
* the WS2812 string connected to PB4.
*/

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "light_ws2812.h"

struct cRGB led[60];

uint8_t r=40;
uint8_t g=0;
uint8_t b=0;

void togglergb() {
	uint8_t temp =b;
	b=g;
	g=r;
	r=temp;
}

int main(void)
{
	#ifdef __AVR_ATtiny10__
		CCP=0xD8;		// configuration change protection, write signature
		CLKPSR=0;		// set cpu clock prescaler =1 (8Mhz) (attiny 4/5/9/10)
	#endif

	uint8_t counter=0;

	while(1) {
		for(counter=0; counter<60; counter++) {
			led[counter].r=r;
			led[counter].g=g;
			led[counter].b=b;
			ws2812_setleds(led,60);
			led[counter].r=led[counter].g=led[counter].b=0;
			_delay_ms(30);
		}
		togglergb();
		for(counter=59; counter>0; counter--) {
			led[counter].r=r;
			led[counter].g=g;
			led[counter].b=b;
			ws2812_setleds(led,60);
			led[counter].r=led[counter].g=led[counter].b=0;
			_delay_ms(30);
		}
		togglergb();
  }
}
