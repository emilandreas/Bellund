/*
 * draw.c
 *
 * Created: 17.09.2015 16:37:50
 *  Author: andreabm
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "../Driver_files/joy_driver.h"
#include "../Driver_files/oled_driver.h"
#include "draw.h"


void play_draw(){
	oled_sram_clear_screen(0);
	int x = 63;
	int y = 31;
	
	Joystick joy;
	while (1){
		joy = getJoystickPosition();
		switch(joy.D){
			case NEUTRAL:
				break;
			case UP:
				y--;
				break;
			case DOWN:
				y++;
				break;
			case LEFT:
				x--;
				break;
			case RIGHT:
				x++;
			break;
			default:
			break;
		}
		oled_sram_write_bit(0,x,y);
		oled_sram_flush(0);
		_delay_ms(100);
	}
}