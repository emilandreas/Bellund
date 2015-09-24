/*
 * SPI_driver.c
 *
 * Created: 24.09.2015 09:34:13
 *  Author: andreabm
 */ 
#include <avr/io.h>
#include <util/delay.h>

void SPI_init(){
	//Datadir: MOSI (== PB6) out, SCK (== PB7) out, !SS (== PB4) out
	DDRB = (1<<PB6)|(1<<PB7)|(1<<PB4);
	//Enable SPI and Master, and set clock rate to fck/16
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}
char SPI_transmit(char c){
	SPDR = c;
	while(!(SPSR & (1<<SPIF)));
	return SPDR;
}
