/*
 * ByggernBellLund.c
 *
 * Created: 27.08.2015 10:11:04
 *  Author: Administrator
 */ 
#define F_CPU 4915200

#include <avr/io.h>
#include <util/delay.h>
#include "Driver_files/uart_driver.h"
#include "Driver_files/sram_driver.h"
#include "Driver_files/adc_driver.h"
#include "Driver_files/bus_driver.h"
#include "Driver_files/joy_driver.h"
#include "Driver_files/oled_driver.h"
#include "Interface_files/menu.h"
#include "Game_files/draw.h"
#include "Driver_files/CAN_driver.h"
#include "Driver_files/message_handler.h"

int main(void)
{
	//DDRA = 0xFF;
	uartInit(9600);
	bus_init();
	oled_init();
	init_handler();
	//oled_sram_init();
	CAN_init();
	printf("Reset?");
    while(1)
    {
		menuSystem();
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
		
		
	
				//
    }
}