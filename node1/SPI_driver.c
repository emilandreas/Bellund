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
uint8_t SPI_transmit(uint8_t data){
	// start transmission
	SPDR = data;
	//Wait for data to be ent and receved
	while(!(SPSR & (1<<SPIF)));
	//Return answer
	return SPDR;
}

void SPI_send(uint8_t c){
	SPI_transmit(c);
}

uint8_t SPI_receive(){
	return SPI_transmit(0);
}

void SPI_ss_high(){
	PORTB |= (1<<PB4);
}

void SPI_ss_low(){
	PORTB &= ~(1<<PB4);
}
