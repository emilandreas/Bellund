/*
 * oled_driver.c
 *
 * Created: 10.09.2015 12:55:40
 *  Author: andreabm
 */ 

#include <avr/io.h>
#include <stdio.h>
#include "oled_driver.h"
#include "font.h"


void write_data(uint8_t data){
	volatile char *oled_data = (char *) 0x1200;
	oled_data[0] = data;
}

void write_command(uint8_t command){
	volatile char *oled_command = (char *) 0x1000;
	oled_command[0] = command;
}

void oled_init(){
	write_command(0xae);    // display off
	write_command(0xa1);    //segment remap
	write_command(0xda);    //common pads hardware: alternative
	write_command(0x12);
	write_command(0xc8);    //common output scan direction:com63~com0
	write_command(0xa8);    //multiplex ration mode:63
	write_command(0x3f);
	write_command(0xd5);    //display divide ratio/osc. freq. mode
	write_command(0x80);
	write_command(0x81);    //contrast control
	write_command(0x50);
	write_command(0xd9);    //set pre-charge period
	write_command(0x21);
	write_command(0x20);    //Set Memory Addressing Mode
	write_command(0x02);
	write_command(0xdb);    //VCOM deselect level mode
	write_command(0x30);
	write_command(0xad);    //master configuration
	write_command(0x00);
	write_command(0xa4);    //out follows RAM content
	write_command(0xa6);    //set normal display
	write_command(0xaf);    // display on
	
	fdevopen(&oled_print, NULL);
}

void oled_home(){
	oled_pos(0,0);
}

void oled_goto_line(uint8_t line){
	//Set Page Start Address for Page Addressing Mode
	write_command(line + 0xB0);
}

void oled_clear_line(uint8_t line){
	oled_goto_line(line);
	for(int i = 0; i <128; i++){
		write_data(0);
	}
}

void oled_clear_screen(){
	for(int line = 0; line <8; line++){
		oled_clear_line(line);
	}
}

void oled_pos(uint8_t row, uint8_t column){
	oled_goto_line(row);
	//Set Lower Column Start Address for Page Addressing Mode
	write_command(column%16);
	//Set Higher Column Start Address for Page Addressing Mode
	write_command(column/16 + 0x10);
}

void oled_print(char* c){
	for(int line = 0; line < 8; line++){
		write_data(font[*c - 32][line]);
	}
}
