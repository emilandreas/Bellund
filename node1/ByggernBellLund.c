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
#include "sram_driver.h"
#include "adc_driver.h"
#include "bus_init.h"

int main(void)
{
	//DDRA = 0xFF;
	uartInit(9600);
	bus_init();
    while(1)
    {
		//PORTA |= (1 << PINA0);
		_delay_ms(5);
		printf("adc output: x = %i\t\t y = %i\n\r",get_adc(2), get_adc(1));
		//PORTA &= ~(1 << PINA0); 
    }
}