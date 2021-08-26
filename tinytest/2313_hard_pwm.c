#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#include "2313_hard_pwm.h"


void init_pwm (void)
{  
  
  // Timer 0 PWM Init

	// Timer/Counter Control Rgister A
  TCCR0A = (1 << WGM00)    // FAST PWM
 		     | (1 << WGM01)
		     | (1 << COM0A1)	 // Set OC0A on Compare Match, Clear at TOP
		     | (1 << COM0B1);

  TCCR0B = (0 << WGM02)
 		     | (1 << CS00)		 // No Prescaling
		     | (0 << CS01)
		     | (0 << CS02);


  // OC0A PWM Port
	// Write PWM-Value to OCR0A
  DDRB   |= (1 << PB2);
  OCR0A = 0;


  // OC0B PWM Port
	// Write PWM-Value to OCR0B
  DDRD   |= (1 << PD5);
  OCR0B = 0;
  

  // Timer 1 PWM Init
  TCCR1A = (1 << WGM10)
    		 | (0 << WGM11)
	 			 | (1 << COM1A1)		// Set OC1A/OC1B on Compare Match, Clear at TOP
				 | (1 << COM1B1);

  TCCR1B = (1 << WGM12)
  			 | (0 << WGM13)
				 | (1 << CS10)
				 | (0 << CS11)
				 | (0 << CS12);


  // OC1A PWM Port
  DDRB   |= (1 << PB3);
	OCR1AH = 0;
  OCR1AL = 0;


  // OC1B PWM Port
  DDRB   |= (1 << PB4);
 	OCR1BH = 0;
  OCR1BL = 0;

}
