/*
 * EEPROM_driver.c
 *
 * Created: 26.10.2015 13.38.06
 *  Author: AndreasBell
 */ 
#include <avr/interrupt.h>
#include <avr/io.h>
#include "EEPROM_driver.h"

// The Atmega 162 contains a 512 bytes EEPROM space.

uint8_t EEPROM_read(unsigned int address){
	//Wait for compleated preveouse write
	while(EECR & (1<<EEWE));
	
	//Set write address
	EEAR = address;
	
	//Start read
	EECR |= (1<<EERE);
	
	return EEDR;
}

void EEPROM_write(unsigned int address, uint8_t data){
	//Disable interrupt to make sure write is performed
	cli();
	
	//Wait for compleated preveouse write
	while(EECR & (1<<EEWE));
	
	//Set write address
	EEAR = address;
	
	//Save data to EEPROM Data Register
	EEDR = data;
	
	//Set EEMWE to 1 to enable write (set EEWE within four clock cycles to write)
	EECR |= (1<<EEMWE);
	
	//Start EEPROM write
	EECR |= (1<<EEWE);
	
	//Enable interrupt
	sei();
}
