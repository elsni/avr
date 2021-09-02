// Written for AVRStudio 4 and ATTINY
// I actually have no idea what it does in particular
// some PWM stuff, for LEDs?

#include <avr/io.h>
#include "2313_hard_pwm.h"
#define F_CPU 1000000l
#include <util/delay.h>

void blink(void);
void setbrightnessA(int);
void setbrightnessB(int);

int main (void)
{
 	int a[4]={0,127,255,127};
 	int b[4]={1,1,-1,-1};
	int i;
	init_pwm();


	for(;;) {
		for (i=0; i<=3; i++) {
			a[i]+=b[i];
			if (a[i] == 255) b[i]*=-1;
			if (a[i] == 0) b[i]*=-1;
		}
		_delay_loop_2(500);
		OCR0A=a[0];
		OCR0B=a[1];
		OCR1AH = 0;
 		OCR1AL = a[2];
		OCR1BH = 0;
		OCR1BL = a[3];
	 }

}

