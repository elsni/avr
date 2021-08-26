//
// Anpassungen im makefile:
//    ATMega8 => MCU=atmega8 im makefile einstellen
//    lcd-routines.c in SRC = ... Zeile anhängen
//
//#include <util/atomic.h>		// need "--std=c99"
#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/interrupt.h>
#include "lcd.h"
#include <util/delay.h>
#include "MobilePhone.h"

typedef unsigned char	u8;
typedef signed short	s16;

// Wählscheibe
#define WS_PORT		PORTD
#define WS_IN	  	PIND
#define WS_ENABLE PD2			// Wählen-Pin (Low-Aktiv)
#define WS_PULSE 	PD1			// Impuls-Pin (High-Aktiv)
#define WS_DDR		DDRD

// Lautsprecher
#define LS_DDR		DDRA
#define LS_PIN		PA0
#define LS_PORT		PORTA

volatile int sound=1;

int main(void)
{
	// Wählscheiben-Pins auf Input setzen mit Pullup
	WS_DDR &= ~( 1 << WS_ENABLE );
	WS_DDR &= ~( 1 << WS_PULSE );
	WS_PORT |= (1 << WS_ENABLE);
	WS_PORT |= (1 << WS_PULSE);

	LS_DDR |=  (1 << LS_PIN);  // PA1 im DDRA auf 1 setzen. PA1 ist Ausgang, alle anderen bleiben unberührt

	// Initialisierung des LCD
	lcd_init();
	
	// Setze Pin6 (PD2) als Interrupt-Pin
	PCMSK |= (1<<PIND2);

	// interrupt an INT0 pin wenn dieser low ist
	MCUCR &= ~3;	// Beide unterste bits löschen: ISC00 und ISC01

	// Interrupt INT0 an!
	GIMSK  |= (1<<INT0);
	sei();
	
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
	sleep_enable();

	while (1) {
		sleep_cpu();
		//if (sound==1) {
			// Blinken um Schlafmodus zu testen
			LS_PORT |= (1 << LS_PIN);
			_delay_ms(30);
			LS_PORT &= ~(1 << LS_PIN);
			_delay_ms(30);
		//}
	}
	return 0;
}

// -------------------------------------------------------
// INT0 Interrupt Routine
// -------------------------------------------------------
SIGNAL (SIG_INT0)
{
	char sreg = SREG;
	cli();
	char t=QueryDial();

	// t sollte nicht 0 sein. Dies nur zur Sicherheit, falls der Interrupt doch einmal aufgerufen wird
	// wenn WS_ENABLE gar nicht auf low ist.
	if (t!=0) {
		lcd_data(t);
	}
	sei();
	SREG=sreg;
}

// -------------------------------------------------------
// Abfrage der Wählscheibe, Wartet bis Nummer gewählt
// Rückgabe der Ziffer als ASCII
// -------------------------------------------------------
char QueryDial()
{
	int number=0;
	// Ist WS_ENABLE low?
	if (! (WS_IN & (1<<WS_ENABLE)) ) {
		_delay_ms(10);
		// Solange WS_ENABLE low ist
		while (!(WS_IN & (1<<WS_ENABLE))) {

			// Ist WS_PULSE high?
			if (WS_IN & (1<<WS_PULSE) ) {
				LS_PORT |= (1 << LS_PIN);
				_delay_ms(10);
				number++;

				// warten bis pin wieder low
				while ( WS_IN & (1<<WS_PULSE)) {}
				LS_PORT &= ~(1 << LS_PIN);
				_delay_ms(10);
			}
		}

		// Zahl ausgeben
		number+=48;
		if (number==58) number=48;
		_delay_ms(10);
		sound=0;
	}
	return number;
}

