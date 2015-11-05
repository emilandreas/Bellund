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

void play_pingpong(){
	state_set(PLAY_PINGPONG);
	score_set(0);
	
	//Send message to node 2, and go into waiting mode
	Message m;
	m.id = GAME_STATUS;
	m.length = 1;
	m.data[0] = PLAY_PINGPONG;
	CAN_transmit(&m);
	
	//Print message on screen
	oled_sram_clear_screen(0);
	oled_sram_write_string(0, "Playing pingpong", 2);
	char score[16];
	printf("State %i \n", current_state);
	while(current_state == PLAY_PINGPONG){
		_delay_ms(100);
		send_controlls();
		sprintf(score, "Score: %d", current_score);
		oled_sram_write_string(0, score, 4);
		oled_sram_flush(0);
	}
	
	
	highscore hs;
	hs.name[0] = 'e';
	hs.name[1] = 'a';
	hs.name[2] = 'l';
	hs.score = current_score;
	hs.place = 0;
	//highscore_add(PINGPONG, &hs);
	_delay_ms(50);
	highscore hslist[16];
	highscore_leaderboard(PINGPONG, hslist, 10);
	for (int i = 0; i < 16; i++){
		printf("leaderboard: %i, %s, %i\n\r", hslist[i].place, hslist[i].name, hslist[i].score );
	}
}


void state_set(State state){
	
	current_state = state;
}

void score_set(uint8_t score){
	current_score = score;
}