/*
 * highscore.c
 *
 * Created: 26.10.2015 14.06.51
 *  Author: AndreasBell
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "highscore.h"
#include "..\Driver_files\EEPROM_driver.h"
#include "..\Driver_files\oled_driver.h"
#include "..\Driver_files\joy_driver.h"


void highscore_save(uint8_t game, highscore *score){
	if (score->place > 0 && score->place < 17){
		//Calculate index of score
		int index = (score->place-1)*4;
		
		//Save name, score in EEPROM
		for (int i = 0; i < 3; i++){
			EEPROM_write(game + index + i, score->name[i]);
		}
		EEPROM_write(game + index + 3, score->score);
	}
}

uint8_t highscore_add(uint8_t game, highscore *score){
	highscore leaderboard[16];
	highscore_leaderboard(game, leaderboard, 16);
	score->place = 0;
	
	//find place
	for(int i = 0; i < 16; i++){
		if(leaderboard[i].score < score->score){
			score->place = leaderboard[i].place;
			i = 16;
		}
	}
	
	//return 0 if not a highscore
	if(score->place == 0){
		return 0;
	}
	
	// Add score and move down other scores
	else{
		highscore_save(game, score);
		for (int i = score->place -1; i < 16; i++){
			leaderboard[i].place++;
			highscore_save(game, &leaderboard[i]);
		}
		return score->place;
	}
}

highscore highscore_get(uint8_t game, uint8_t position){
	highscore hs;
	
	//Make sure legal position between 1 and 16
	position = (position > 0 && position < 17)? position : 0;
	hs.place = position;
	
	//Calculate index of score
	int index = (position-1)*4;
	
	//Get name, score from EEPROM
	for (int i = 0; i < 3; i++){
		hs.name[i] = EEPROM_read(game + index + i);
	}
	hs.score = EEPROM_read(game + index + 3);
	return hs;
}


void highscore_leaderboard(uint8_t game, highscore leaderboard[], int length){
	for (int i = 0; i < length; i++){
		leaderboard[i] = highscore_get(game, i+1);
	}
}

void highscore_clear(uint8_t game){
	highscore hs;
	
	hs.name[0] = 'N';
	hs.name[1] = 'A';
	hs.name[2] = 'N';
	hs.score = 0;
	for (int i = 0; i < 16; i++){
		hs.place = i + 1;
		highscore_save(game, &hs);
	} 
}

void highscore_clear_all(){
	highscore_clear(PINGPONG);
	highscore_clear(PONG);
	highscore_clear(SNAKE);
}

void highscore_print(uint8_t game){
	//Get highscore list
	highscore hslist[16];
	highscore_leaderboard(game, hslist, 16);
	
	//Clear SRAM and print list to SRAM
	oled_sram_clear_screen(0);
	char score[16];
	for (int i = 0; i < 7; i++){
		sprintf(score, "%i %c%c%c %i", hslist[i].place, hslist[i].name[0], hslist[i].name[1], hslist[i].name[2], hslist[i].score );
		oled_sram_write_string(0, score, i);
		//printf("%s \n\r", score);
	}
	
	oled_sram_flush(0);
	while(get_joystick_position().D != LEFT){
		_delay_ms(100);
	}
}

void highscore_print_pingpong(){
	highscore_print(PINGPONG);
}

void highscore_print_snake(){
	highscore_print(SNAKE);
}

void highscore_print_pong(){
	highscore_print(PONG);
}

void highscore_prompt(uint8_t game, uint8_t score){
	//Make highscore
	highscore hs;
	hs.name[0] = 'A';
	hs.name[1] = 'A';
	hs.name[2] = 'A';
	hs.score = score;
	
	//Print highscore
	oled_sram_clear_screen(0);
	char buffer[16];
	sprintf(buffer, "Score: %i", hs.score );
	oled_sram_write_string(0, buffer, 2);
	
	//Allow user to change name
	
	int letter_pointer = 0; 
	direction D = get_joystick_position().D;
	while(letter_pointer < 3){
		_delay_ms(100);
		if(D != get_joystick_position().D){
			D = get_joystick_position().D;
			switch(D){
				case LEFT:
					letter_pointer = (letter_pointer + 2)%3;
					break;
				case RIGHT:
					letter_pointer++;
					break;
				case UP:
					hs.name[letter_pointer]++;
					break;
				case DOWN:
					hs.name[letter_pointer]--;
					break;
				default:
					break;
			}
		}
		sprintf(buffer, "Name: %c%c%c", hs.name[0], hs.name[1], hs.name[2]);
		oled_sram_write_string(0, buffer, 3);
		oled_sram_write_string(0, "          ", 4);
		oled_sram_write_char(0, "^", 4, (6+letter_pointer)*8);
		oled_sram_flush(0);
	}
	
	
	highscore_add(game, &hs);
}