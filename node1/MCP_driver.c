/*
 * MCP_driver.c
 *
 * Created: 24.09.2015 10:03:42
 *  Author: andreabm
 */ 
#include <avr/io.h>
#include "MCP_driver.h"
#include "SPI_driver.h"

void MCP_init(){
	SPI_init();
}

void toggle_cs(uint8_t i){
	if(i){
		PORTB |= (1<<PB4);		
	}
	else{
		PORTB &= ~(1<<PB4);		
	}
}

void MCP_reset(){
	toggle_cs(0);
	SPI_transmit(0b11000000);
	toggle_cs(1);
}

char MCP_read(uint8_t address){
	toggle_cs(0);
	SPI_transmit(0b00000011);
	SPI_transmit(address);
	char c = SPI_transmit('j'); //Send junk to recieve data
	toggle_cs(1);
	return c;
}

void MCP_read_rx(){
	return 0;
}

void MCP_write(uint8_t address, char data){
	toggle_cs(0);
	SPI_transmit(0b00000010);
	SPI_transmit(address);
	SPI_transmit(data);
	toggle_cs(1);
}

void MCP_load_tx(){
	return 0;
}
void MCP_rts(uint8_t buffer){
	switch(buffer){
		case 0:
			SPI_transmit(0b10000001);
			break;
		case 1:
			SPI_transmit(0b10000010);
			break;
		case 2:
			SPI_transmit(0b10000100);
			break;
	}
}
uint8_t MCP_read_status(){
	toggle_cs(0);
	SPI_transmit(0b10100000);
	uint8_t data = SPI_transmit('!');
	toggle_cs(1);
	return data;
}
uint8_t MCP_rx_status(){
	toggle_cs(0);
	SPI_transmit(0b10110000);
	uint8_t data = SPI_transmit('!');
	toggle_cs(1);
	return data;
}
void MCP_bit_modify(uint8_t address, uint8_t mask, char data){
	toggle_cs(0);
	SPI_transmit(0b00000101);
	SPI_transmit(address);
	SPI_transmit(mask);
	SPI_transmit(data);
	toggle_cs(1);
}