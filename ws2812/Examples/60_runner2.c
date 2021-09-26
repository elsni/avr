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

#define NUMLEDS 60

struct cRGB led[NUMLEDS];

uint8_t rpos=0;
uint8_t gpos=NUMLEDS/3;
uint8_t bpos=NUMLEDS/3*2;

int8_t radd=1;
int8_t gadd=2;
int8_t badd=-1;

uint8_t r=40;
uint8_t g=0;
uint8_t b=0;

void clr() {
	uint8_t counter;
	for(counter=0; counter<NUMLEDS; counter++) {
		led[counter].r=0;
		led[counter].g=0;
		led[counter].b=0;
	}
}

int main(void)
{
	#ifdef __AVR_ATtiny10__
		CCP=0xD8;		// configuration change protection, write signature
		CLKPSR=0;		// set cpu clock prescaler =1 (8Mhz) (attiny 4/5/9/10)
	#endif

	while(1) {
		clr();
		led[rpos].r=40;
		led[gpos].g=40;
		led[bpos].b=40;
		ws2812_setleds(led,NUMLEDS);

		if (rpos+radd <= 0) {
			rpos=-radd;
			radd=-radd;
		} else if (rpos+radd >= NUMLEDS) {
			rpos=NUMLEDS-1-radd;
			radd=-radd;
		} else {
			rpos+=radd;
		}

		if (gpos+gadd <= 0) {
			gpos=-gadd;
			gadd=-gadd;
		} else if (gpos+gadd >= NUMLEDS) {
			gpos=NUMLEDS-1-gadd;
			gadd=-gadd;
		} else {
			gpos+=gadd;
		}
		if (bpos+badd <= 0) {
			badd=-badd;
			bpos=badd;
		} else if (bpos+badd >= NUMLEDS) {
			bpos=NUMLEDS-1-badd;
			badd=-badd;
		} else {
			bpos+=badd;
		}

		_delay_ms(50);

	}
}
