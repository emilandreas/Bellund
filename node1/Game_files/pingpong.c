/*
 * pingpong.c
 *
 * Created: 29.10.2015 12:05:33
 *  Author: andreabm
 */ 

#include "avr/io.h"
#include "pingpong.h"
#include "../Driver_files/message_handler.h"
#include "../Driver_files/CAN_driver.h"
#include "../Driver_files/joy_driver.h"

void start_pingpong(){
	printf("starting pingpong");
	//Send message to node 2, and go into waiting mode
	Message m;
	m.id = START_PINGPONG;
	m.length = 0;
	CAN_transmit(&m);
	wait_mode("Playing pingpong");
	
	m.id = EXIT_PINGPONG;
	m.length = 0;
	CAN_transmit(&m);
}

void wait_mode(char* message){
	printf("waiting");
	//Print message on screen, and wait for slide from 0 to 100 on left slide
	Slider s;
	int first_check = 0;
	oled_sram_clear_screen(0);
	oled_sram_write_string(0, message, 2);
	oled_sram_write_string(0, "(slide to exit)", 4);
	oled_sram_flush(0);
	while(1){
		//s = getSliderPosition();
		//if (s.left < 10 || first_check){
			//first_check = 1;
			//if(s.left > 90){
				//printf("\nSlided open!\n");
				//first_check = 0;
				//break;
				//
			//}
		//}
	}
}