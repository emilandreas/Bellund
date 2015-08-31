/*
 * ByggernBellLund.c
 *
 * Created: 27.08.2015 10:11:04
 *  Author: Administrator
 */ 
#define F_CPU 4915200

#include <avr/io.h>
#include <util/delay.h>
#include "uart_driver.h"

int main(void)
{
	DDRA = 0xFF;
	uartInit(9600);
    while(1)
    {
		PORTA |= (1 << PINA0);
		_delay_ms(500);
		PORTA &= ~(1 << PINA0);
		_delay_ms(500);
		printf("Hei \n");
        //TODO:: Please write your application code 
    }
}