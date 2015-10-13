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


void menuSystem(){
	menu mainMenu = {.name = "Main menu", .num_submenues = 3};
		
	menu highscore = {.name = "Highscore", .parent = &mainMenu};
	mainMenu.submenues[1] = &highscore;
	
	menu playGame = {.name = "Play Game", .parent = &mainMenu, .num_functions = 3};
	playGame.functions[0] = &play_draw;
	playGame.functions[1] = &playSnake;
	playGame.functions[2] = &playPong;
	playGame.name_functions[0] = "Draw";
	playGame.name_functions[1] = "Snake";
	playGame.name_functions[2] = "Pong";
	mainMenu.submenues[0] = &playGame;
		
	menu settings = {.name = "Settings", .parent = &mainMenu, .num_functions = 1};
	settings.functions[0] = &calibrateJoystick;
	settings.name_functions[0] = "Calibrate Joy";
	mainMenu.submenues[2] = &settings;
	
	
	
	direction previousDirection = NEUTRAL;
	Joystick joy;
	menu* currentMenu = &mainMenu;
	int num_elements;
	while(1){
		num_elements = (currentMenu->num_functions+currentMenu->num_submenues);
		joy = getJoystickPosition();
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

make_screen(menu* m){
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