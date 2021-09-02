/*=====================================================
|   TASK:  TOGGLING THE LED ATTACHED TO PB3 (physical Pin 2)
|          OF AN ATTINY85
|   DIFFICULTY LEVEL: VERY BASIC
|   Author:  BISWARUP BANERJEE
|            Modified for Attiny85 by Stephan Elsner
|   Language:  EMBEDDED C
|   To Compile:  RUN THE SCRIPT AS MENTIONED BY THE AUTHOR
|   Date:  June 2017, August 2021
================================================*/
#ifndef F_CPU

// Assume clock is set to 8MHz
#define F_CPU 8000000UL
#endif

#include <avr/io.h>                    // adding header files
#include <util/delay.h>                // for _delay_ms()

int main(void)
{
   DDRB = 0b00001000;                 // setting DDR of PORT B
   while(1)
   {
       // LED on
       PORTB = 0b00001000;            // PB3 = High = LED attached on PC0 is ON
       _delay_ms(500);                // wait 500 milliseconds

       //LED off
       PORTB = 0b00000000;            // PB3 = Low = LED attached on PC0 is OFF
       _delay_ms(500);                // wait 500 milliseconds
   }
}