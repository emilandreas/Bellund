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
#include "sram_driver.h"
#include <avr/interrupt.h>


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

void oled_print(char *cstr){
	int index = 0;
	char c = cstr[0];
	while(c != '\0'){
		for(int line = 0; line < 8; line++){
			write_data(pgm_read_byte(&font[c - 32][line]));
		}
		c = cstr[++index];
	}
}






void oled_sram_init(){
	TCCR1B |= (1 << CS12)|(1 << CS10); // Prescaler 1024
	OCR1B = 80;
	TIFR |= (1<< OCF1B); //Output compare
	TIMSK |= (1 << OCIE1B); // Enable global interrupt on output compare B timer 1
	sei();
}

ISR(TIMER1_COMPB_vect){
	oled_sram_flush(0);
	TCNT1 = 0;
}

void oled_sram_flush(int start){
	int line = 0;
	for (int i = 0; i < 128*8; i++){
		if(i%128 == 0){
			oled_goto_line(line);
			line++;
		}
		write_data(getSRAM(i + start));
	}
}

void oled_sram_write(int start, int page, int column, uint8_t value){
	setSRAM(start + page*128 + column, value);
}


void oled_sram_write_string(int start, char *cstr, int page){
	start = start + page*128; //Starts at chosen line
	int index = 0;
	char c = cstr[0];
	while(c != '\0'){
		for(int line = 0; line < 8; line++){
			setSRAM(start++,pgm_read_byte(&font[c - 32][line]));
		}
		c = cstr[++index];
	}
}

void oled_sram_write_char(int start, char *c, int page, int col){
	start = start + page*128+col;
	for(int line = 0; line < 8; line++){
		setSRAM(start++,pgm_read_byte(&font[*c - 32][line]));
	}
}

void oled_sram_clear_line(int start, int page){
	start = start + page*128; // Starts on correct page
	for (int i = 0; i < 128; i++){
		setSRAM(start + i, 0);
	}
}

void oled_sram_clear_screen(int start){
	for (int page = 0; page < 8; page++){
		oled_sram_clear_line(start, page);
	}
}

void oled_sram_write_line(int x0, int y0, int x1, int y1){
	oled_clear_screen(0);
	float xLen = x1-x0;
	float yLen = y1-y0;
	float deriv;
	if (xLen < yLen){
		deriv = xLen/yLen;
		for(int i = y0; i < y1; i++){
			oled_sram_write_bit(0, x0 + i*deriv, y0 + i);
		}
	}
	else {
		deriv = yLen/xLen;
		for(int i = x0; i < x1; i++){
			oled_sram_write_bit(0, x0 + i, y0 + i*deriv);
		}
	}
	oled_sram_flush(0);
}

void oled_sram_write_bit(int start, int x, int y){
	int page = y/8;
	int row = y%8;
	int index = start + page*128 + x;
	uint8_t temp = getSRAM( index );
	temp |= (1 << row);
	setSRAM(index, temp);
}