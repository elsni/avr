/*
 * BugLogger.c
 *
 * Created: 31.05.2012 15:49:04
 *  Author: Elsni
 */ 


#include <avr/io.h>
#include "lcd.h"

int main(void)
{
	lcd_init();
	lcd_string("BugLogger v0.1");
	
    while(1)
    {
        //TODO:: Please write your application code 
    }
}