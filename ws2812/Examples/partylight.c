/*
* Light_WS2812 library example - RGB_blinky
*
* bounce one light through a 60 pixel strip.
* changing color at each bounce.
*
* This example is configured for a ATtiny85 with PLL clock fuse set and
* the WS2812 string connected to PB4.
*/

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "light_ws2812.h"

#define TRUE 1
#define FALSE 0

// buffer for LED Strip
struct cRGB led[60];

uint8_t r=40;
uint8_t g=0;
uint8_t b=0;
static uint8_t stop=FALSE;

void external_interrupt()
{
  sei();     //enabling global interrupt
  GIMSK |= (1<<INT0);     // enabling the INT0 (external interrupt) 
  MCUCR |= (1<<ISC01);    // Configuring as falling edge 
}


// ---------------------------------------------------------------------------------------

ISR (INT0_vect)        // Interrupt service routine 
{
  stop = stop==FALSE?TRUE:FALSE;    // Toggling stop
  _delay_ms(10);
}


// ---------------------------------------------------------------------------------------

void togglergb() {
	uint8_t temp =b;
	b=g;
	g=r;
	r=temp;
}

void runner1() {
	uint8_t counter=0;

	while(stop==FALSE) {
		for(counter=0; counter<60; counter++) {
			led[counter].r=r;
			led[counter].g=g;
			led[counter].b=b;
			ws2812_setleds(led,60);
			led[counter].r=led[counter].g=led[counter].b=0;
            if (stop==TRUE) break;
			_delay_ms(30);
		}
		togglergb();
		for(counter=59; counter>0; counter--) {
			led[counter].r=r;
			led[counter].g=g;
			led[counter].b=b;
			ws2812_setleds(led,60);
			led[counter].r=led[counter].g=led[counter].b=0;
            if (stop==TRUE) break;
			_delay_ms(30);
		}
		togglergb();
  }
}

void setup() {
    external_interrupt();
};

void run() {
    do {
        while(stop==TRUE){
            _delay_ms(50);
        };
        runner1();
    }
    while(TRUE);
};

int main(void){
    setup();
    run();

}
