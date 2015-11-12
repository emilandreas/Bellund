/*
 * menu.c
 *
 * Created: 17.09.2015 09:22:17
 *  Author: andreabm
 */ 

#include <util/delay.h>
#include "menu.h"
#include "../Driver_files/oled_driver.h"
#include "../Driver_files/joy_driver.h"
#include "../Game_files/draw.h"
#include "../Game_files/snake.h"
#include "../Game_files/pong.h"
#include "../Game_files/pingpong.h"
#include "../Game_files/highscore.h"


void menuSystem(){
	menu mainMenu = {.name = "Main menu", .num_submenues = 3};
		
	menu highscore = {.name = "Highscore", .parent = &mainMenu, .num_functions = 3, .num_submenues = 0};
	mainMenu.submenues[1] = &highscore;
	highscore.functions[0] = &highscore_print_snake;
	highscore.functions[1] = &highscore_print_pong;
	highscore.functions[2] = &highscore_print_pingpong;
	highscore.name_functions[0] = "Snake";
	highscore.name_functions[1] = "Pong";
	highscore.name_functions[2] = "Ping Pong";
	
	menu playGame = {.name = "Play Game", .parent = &mainMenu, .num_functions = 5};
	playGame.functions[0] = &play_draw;
	playGame.functions[1] = &playSnake;
	playGame.functions[2] = &playPong;
	playGame.functions[3] = &play_pingpong_web;
	playGame.functions[4] = &play_pingpong_joy;
	playGame.name_functions[0] = "Draw";
	playGame.name_functions[1] = "Snake";
	playGame.name_functions[2] = "Pong";
	playGame.name_functions[3] = "Ping Pong WEB";
	playGame.name_functions[4] = "Ping Pong JOY";
	mainMenu.submenues[0] = &playGame;
		
	menu settings = {.name = "Settings", .parent = &mainMenu, .num_functions = 2};
	settings.functions[0] = &calibrate_joystick;
	settings.functions[1] = &highscore_clear_all;
	settings.name_functions[0] = "Calibrate Joy";
	settings.name_functions[1] = "Clear highscore";
	mainMenu.submenues[2] = &settings;
	

	
	direction previousDirection = NEUTRAL;
	Joystick joy;
	menu* currentMenu = &mainMenu;
	int num_elements;
	while(1){
		num_elements = (currentMenu->num_functions+currentMenu->num_submenues);
		joy = get_joystick_position();
		if (joy.D != previousDirection){
			switch(joy.D){
				case NEUTRAL:
					break;
				case UP:
					currentMenu->arrow = (currentMenu->arrow - 1 + num_elements)%num_elements;
					break;
				case DOWN:
					currentMenu->arrow = (currentMenu->arrow + 1)%num_elements;
					break;
				case LEFT:
						currentMenu = (currentMenu->parent) ? currentMenu->parent : currentMenu;
					break;
				case RIGHT:
					if(currentMenu->arrow < currentMenu->num_submenues){
						currentMenu = currentMenu->submenues[currentMenu->arrow];
					}
					else{
						currentMenu->functions[(currentMenu->arrow - currentMenu->num_submenues)]();
					}
					
					break;
					default:
					break;
			}
		}
		previousDirection = joy.D;
		
		make_screen(currentMenu);
		_delay_ms(100);		
	}
	
	
	
}

void make_screen(menu* m){
	int startAddress = 0;
	
	oled_sram_clear_screen(startAddress);
	oled_sram_write_string(startAddress, m->name, 0); //Print menu name
	for (int i = 0; i < m->num_submenues; i++){
		menu *sm = m->submenues[i];
		
		int index = 1;
		char c = sm->name[0];
		if(m->arrow == i){
			oled_sram_write_char(startAddress, ">", i+1, 0);
		}
		else{
			oled_sram_write_char(startAddress, " ", i+1, 0);
		}
		while(c != '\0'){
			for(int line = 0; line < 8; line++){
				oled_sram_write_char(startAddress, &c, i+1, index*8);
			}
			c = sm->name[index++];
		}
	}
	for (int i = 0; i < m->num_functions; i++){
		char *funcnames = m->name_functions[i];
		
		int index = 1;
		char c = funcnames[0];
		if(m->arrow == i + m->num_submenues){
			oled_sram_write_char(startAddress, ">", i + m->num_submenues + 1, 0);
		}
		else{
			oled_sram_write_char(startAddress, " ", i + m->num_submenues + 1, 0);
		}
		while(c != '\0'){
			for(int line = 0; line < 8; line++){
				oled_sram_write_char(startAddress, &c, i + m->num_submenues + 1, index*8);
			}
			c = funcnames[index++];
		}
	}
	oled_sram_flush(startAddress);
} 
