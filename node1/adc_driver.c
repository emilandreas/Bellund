/*
 * adc_driver.c
 *
 * Created: 03.09.2015 15:29:03
 *  Author: andreab
 */ 
#include <util/delay.h>

uint8_t get_adc(int channel){
	_delay_us(200);
	volatile char *adc = (char *) 0x1400; // Start address adc
	uint16_t adc_size       = 0x400;
	
	adc[0] = 3 + channel;
	_delay_us(30);
	return adc[0];
}