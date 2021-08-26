// 
// Anpassungen im makefile:
//    ATMega8 => MCU=atmega8 im makefile einstellen
//    lcd-routines.c in SRC = ... Zeile anhängen
// 
// LCD.h ist angepasst an das Modul mit ATTINY 2313 auf Lochrasterplatine
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <string.h>
#include "lcd.h"
#include <util/delay.h>

void createChars();
void showCharset();
void scroll( const char *data );
void bonf();
void lcdlaufschrift();
void timer0_init(void);

const uint8_t _heart1[] = {10,31,31,31,14,4,0,0};
const uint8_t _heart2[] = {0,10,14,14,4,0,0,0};
const uint8_t _heart3[] = {10,31,23,23,10,4,0,0};
const uint8_t _heart4[] = {10,21,17,17,10,4,0,0};


//const uint8_t _b2[] = { 0, 0,0,0,4,0,0,0};
//const uint8_t _b3[] = { 0, 0,0,4,10,4,0,0};
//const uint8_t _b4[] = { 0, 0,4,10,17,10,4,0};
//const uint8_t _b5[] = { 0, 0,14,17,17,17,14,0};
//const uint8_t _b6[] = { 0, 10,21,4,27,4,21,10};
//const uint8_t _b7[] = { 0, 4,4,0,17,0,4,4};
//const uint8_t _b8[] = { 0, 4,0,0,0,0,0,4};
//const uint8_t _b9[] = { 0, 0,0,0,0,0,0,0};



const char _text[] = "\4\4\4\4   Hallo  Meike   \4\4   ich liebe Dich!  \0";
//char _buffer[5];
volatile uint8_t step;

int main(void)
{
  // Timer Overflow Interrupt freischalten 

  lcd_init();

	createChars();
	lcd_setcursor(0,1);
	//TCCR0B  = 6;                     // Vorteiler 256 -> ~65ms Überlaufperiode
	//TCCR0A = (1 << COM0A1);
  //TIMSK = 2;  
	lcd_data(65);
	lcd_data(2);
	lcd_data(3);
	lcd_data(4);
	//sei();
	timer0_init();
	sei();
	//for(;;);

	lcdlaufschrift();
	return 0;
}

void timer0_init(void)
{
   OCR0A = 160; 
	 TIMSK = (1<<OCIE0A);
   TCCR0B = (1<<CS00 | 1<<CS02); 	    
}

void createChars()
{
	lcd_generatechar(4, _heart1);
//	lcd_generatechar(2, _heart2);
//	lcd_generatechar(3, _heart3);
//	lcd_generatechar(4, _heart4);
}


ISR( TIMER0_COMPA_vect ) {
  OCR0A  =160; //reload counter value
	//cli();
	switch (step){
	case 0:
		lcd_generatechar(4, _heart1);
		break;
	case 1:
		lcd_generatechar(4, _heart2);
		break;
	case 2:
		lcd_generatechar(4, _heart3);
		break;
	case 3:
		lcd_generatechar(4, _heart4);
		break;
/*	case 4:
		lcd_generatechar(4, _b6);
		break;
	case 5:
		lcd_generatechar(4, _b7);
		break;
	case 6:
		lcd_generatechar(4, _b8);
		break;
	case 7:
		lcd_generatechar(4, _b9);
		break;
	*/	
  }
	if (++step==4) step = 0;
	//sei();
}

void scroll( const char *data )
{
		int i=0;
		int count1 = 0;
		int count2 = 7;
		int len = strlen(data);
		const char *start = data;
    while( *data != '\0' ) {
			cli();
	  	lcd_setcursor(0,1);
			for (i=0; i<16; i++) {
     		lcd_data( *(start+((count1+i) % len)) );
			}
	  	lcd_setcursor(0,2);
			for (i=0; i<16; i++) {
     		lcd_data( *(start+((count2+i) % len)) );
			}
			sei();
			data++;
			count1++;
			count2++;
    	_delay_ms(450);
		}
}

void lcdlaufschrift()
{
	createChars();
	for(;;) {
		lcd_laufschrift(_text);
	}
}

