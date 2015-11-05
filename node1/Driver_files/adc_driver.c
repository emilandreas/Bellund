/*
 * adc_driver.c
 *
 * Created: 03.09.2015 15:29:03
 *  Author: andreab
 */ 
#include <util/delay.h>
#include <avr/io.h>

void init_adc(){
	//Make INT0 input
	DDRD &= ~(1 << INT0);
}

uint8_t get_adc(int channel){
	volatile char *adc = (char *) 0x1400; // Start address adc

	adc[0] = 4 + (channel%4);
	_delay_us(200);
	return adc[0];
}
