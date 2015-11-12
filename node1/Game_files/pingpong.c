/*
 * pingpong.c
 *
 * Created: 29.10.2015 12:05:33
 *  Author: andreabm
 */ 

#include "avr/io.h"
#include <util/delay.h>
#include "pingpong.h"
#include "../Driver_files/message_handler.h"
#include "../Driver_files/CAN_driver.h"
#include "../Driver_files/joy_driver.h"
#include "../Driver_files/oled_driver.h"
#include "highscore.h"

volatile State current_state;
volatile uint8_t current_score;

//Send CAN message to node 2 to start ping pong game with one of two controller states
void play_pingpong(uint8_t state){
	state_set(state);
	score_set(0);
	
	//Send message to node 2
	Message m;
	m.id = GAME_STATUS;
	m.length = 1;
	m.data[0] = state;
	CAN_transmit(&m);
	
	//Print message on screen, and go into waiting mode
	oled_sram_clear_screen(0);
	oled_sram_write_string(0, "Playing pingpong", 2);
	char score[16];
	while(current_state == PLAY_PINGPONG_WEB || current_state == PLAY_PINGPONG_JOY){
		_delay_ms(100);
		printf("State %i \n\r", current_state);
		send_controlls();
		sprintf(score, "Score: %d", current_score);
		oled_sram_write_string(0, score, 4);
		oled_sram_flush(0);
	}
	
	highscore_prompt(PINGPONG, current_score);
}

void play_pingpong_web(){
	play_pingpong(PLAY_PINGPONG_WEB);
}

void play_pingpong_joy(){
	play_pingpong(PLAY_PINGPONG_JOY);
}

void state_set(State state){
	
	current_state = state;
}

void score_set(uint8_t score){
	current_score = score;
}