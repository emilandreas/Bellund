/*
 * highscore.h
 *
 * Created: 26.10.2015 14.07.14
 *  Author: AndreasBell
 */ 


#ifndef HIGHSCORE_H_
#define HIGHSCORE_H_

typedef struct {
	char name[3];
	uint8_t score;
	uint8_t place;
} highscore;

//Define Game memory spaces
#define PINGPONG	0x00
#define SNAKE		0x40
#define PONG		0x80

//Functions
void highscore_save(uint8_t game, highscore *score); // saves hs in position
uint8_t highscore_add(uint8_t game, highscore *score); // adds hs to eeprom and returns position of HS
highscore highscore_get(uint8_t game, uint8_t position); //get highscore at position(1-16)
void highscore_leaderboard(uint8_t game, highscore leaderboard[], int length); //Saves length HS's in leaderboard
void highscore_clear(uint8_t game);
void highscore_clear_all();
void highscore_print(uint8_t game);
void highscore_prompt(uint8_t game, uint8_t score);


//Functions for menu since the menu funtion pointer needs void parameter
void highscore_print_snake();
void highscore_print_pong();
void highscore_print_pingpong();


#endif /* HIGHSCORE_H_ */