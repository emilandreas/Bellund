/*
 * highscore.c
 *
 * Created: 26.10.2015 14.06.51
 *  Author: AndreasBell
 */ 

#include <avr/io.h>
#include "highscore.h"
#include "..\Driver_files\EEPROM_driver.h"


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