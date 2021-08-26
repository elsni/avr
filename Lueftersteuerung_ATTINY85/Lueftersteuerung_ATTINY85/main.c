/*
 * Converted from Arduino: https://github.com/marceloaqno/4-Wire-FAN-Arduino/blob/master/ATtiny_PWM_25kHz.ino 
 *                         ATtiny85
 *                      -------u-------
 *  RST - A0 - (D 5) --| 1 PB5   VCC 8 |-- +5V
 *                     |               |
 *        A3 - (D 3) --| 2 PB3   PB2 7 |-- (D 2) - A1  --> 10K Potentiometer (not yet implemented)
 *                     |               | 
 *        A2 - (D 4) --| 3 PB4   PB1 6 |-- (D 1) - PWM --> Fan Blue wire
 *                     |               |      
 *              Gnd ---| 4 GND   PB0 5 |-- (D 0) - PWM --> Disabled
 *                     -----------------

 * main.c
 *
 * Created: 8/26/2021 8:12:55 PM
 *  Author: Stephan
 */ 


// Fuse bits must be set to let the Attiny 85 run at 8MHz
#define F_CPU 8000000
#include <xc.h>
#include <util/delay.h>
//#include <avr/io.h>

int main()
{

	// Setup:
	// Fast PWM Mode, Prescaler = /8
	// PWM on PB1, PB0 disabled
	// 8MHz / 8 / (39+1) = 25KHz
   
    /*
    Port B Data Direction Register (controls the mode of all pins within port B)
    DDRB is 8 bits: [unused:unused:DDB5:DDB4:DDB3:DDB2:DDB1:DDB0]
    1<<DDB1: sets bit DDB1 (data-direction, port B, pin 1), which puts PB1 (port B, pin 1) in output mode
    */
    DDRB =  1<<DDB1;

    /*
    Control Register A for Timer/Counter-0 (Timer/Counter-0 is configured using two registers: A and B)
    TCCR0A is 8 bits: [COM0A1:COM0A0:COM0B1:COM0B0:unused:unused:WGM01:WGM00]
	1<COM0B1 Clear OC0B on Compare Match, set OC0B at BOTTOM (non-inverting mode)
    3<<WGM00: sets bits WGM00 and WGM01, which (when combined with WGM02 from TCCR0B below) enables Fast PWM mode
    */
    TCCR0A = 1<<COM0B1 | 3<<WGM00;
   
    /*
    Control Register B for Timer/Counter-0 (Timer/Counter-0 is configured using two registers: A and B)
    TCCR0B is 8 bits: [FOC0A:FOC0B:unused:unused:WGM02:CS02:CS01:CS00]
    0<<WGM02: bit WGM02 set, which (when combined with WGM00 and WGM01 from TCCR0A above) enables Fast PWM mode 
    1<<CS01: sets bits CS01 /8 prescaler
    */
    TCCR0B = 1<<WGM02 | 1<<CS01;
   
	// Set TOP and initialize duty cycle to zero(0)
	OCR0A = 39;		// TOP - Do not change, sets PWM Pulse rate
	OCR0B = 0;		// duty cycle for PB1 - generates 500nS pulse even when 0
    
	
	uint8_t count =0;
	int step=1;

	// loop forever
    for (;;)
    {
       
	    
        OCR0B = count; // sets Pulse width. MAX TOP (39)
		
		count+=step;
        if (count ==39) {
			step=-1;
			_delay_ms(10000); // wait 10s
		}
        if (count ==0) {
			step=1;
			_delay_ms(10000);
		}
        _delay_ms(250);
    }
}