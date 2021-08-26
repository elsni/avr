/*
 * AttinxHexDisplay.c
 * Attiny 85
 * Created: 05.03.2014 11:28:38
 *  Author: Elsni
 * Pin1 (PB5) --> OUT /Latch Eingangsschieberegister
 * Pin2 (PB3) --> OUT LOAD MAX 7221
 * Pin5 (DI)  --> IN  Serielle Daten des Eingasschieberegisters
 * Pin6 (DO)  --> OUT Serielle Daten MAX 7221
 * Pin7 (SCK) --> OUT Seriell Clock sowohl für Eingang als auch für Ausgang
 */ 


#include <avr/io.h>

void SPI_init(void)
{
	DDRB |= (1<<DDB2)|(1<<DDB1); //Output: PB2=USCK, PB1=DO
	DDRB &= ~(1<<DDB0); //Input: PB0=DI
	PORTB |= (1<<DDB0); //int. Pull-up an PB0 aktivieren

// hier weitermachen:
// von www.ne555.at/atmel-avr-mikrocontrollertechnik/392-usi-to-spi-schnittstelle-mit-dem-attiny44.html

	DDRA |= (1<<PA7); //LED auf Ausgang
	USICR = (1<<USIWM0) | (1<<USICLK)|(1<<USITC)| (1<<USICS1);
	// USIWM0 = 1: SPI-Betrieb mit DO, DI und USCK
	// USICLK = 1, USITC = 1, USICS1 = 1: generiert den Taktimpuls für das Schieberegister und
	// den 4bit Timer. Der Takt wird am USCK-Pin (PA4) ausgegeben.
}


int main(void)
{
	/* PORTB = (1 << PB0 | 1 << PB) */
	/* Outputs: Pin1 (PB5), Pin2 (PB3) 
	// Pin6 (PB1/MISO) Pin7 (PB2 / SCK)  
	// Frage: Auch bei SPI nötig?  
	*/
	DDRB = (1<<DDB5) | (1<<DDB3) | (1<<DDB2) | (1<<DDB1);

    while(1)
    {
        //TODO:: Please write your application code 
    }
}