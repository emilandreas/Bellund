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
#include "joy_driver.h"
#include "oled_driver.h"
#include "menu.h"
#include "draw.h"
#include "CAN_driver.h"

int main(void)
{
	//DDRA = 0xFF;
	uartInit(9600);
	bus_init();
	oled_init();
	//oled_sram_init();
	CAN_init();
    while(1)
    {
		
		//printf("adc output: x = %i\t\t y = %i\t\t Direction = %i\n\r", get_adc(1),get_adc(0),joy.D);
		/*
		for (int line = 0; line < 8; line++){
			oled_pos(line,line*64);
			for(int i = 0; i <128; i++){
				//_delay_ms(50);
				write_data(i);
			}
		}
		*/
		
		//oled_clear_screen();
		//oled_pos(0,0);
		//oled_print("Hello");
		//oled_sram_write_string(0, "Hello", 4);
		//flush_sram(0);
		//_delay_ms(1000);
		
		//menuSystem();
		printf("Hello \n\r");
		Message m;
		m.id = 0b00001;
		m.data[0] = 'h';
		m.length = 4;
		
		CAN_transmit(&m);
		printf("message: %c \n\r", m.data[0]);
		
		Message answer;
		CAN_receive(&answer);
		printf("answer: %c \n\r", answer.data[0]);
		
		_delay_ms(1000);
				
    }
}