/*
* snake.c
*
* Created: 22.09.2015 21:39:07
*  Author: andreabm
*/

#define F_CPU 4915200
#include "snake.h"
#include "../Driver_files/joy_driver.h"
#include <util/delay.h>
#include "../Driver_files/oled_driver.h"
#include <stdlib.h>


int detectCollision(segment *s, int x, int y){
	while(s){
		if (s->x == x && s->y == y){
			return 1;
		}
		s = s->next;
	}
	return 0;
}

void placeFood(int food[], segment *first){
	do{
		food[0] = rand() % 64;
		food[1] = rand() % 32;
	} while(detectCollision(first, food[0], food[1]));
}

void drawBoard(segment *s, int food[]){
	oled_sram_clear_screen(0);
	while(s){
		for(int i = 0; i < 2; i++){
			for (int j = 0; j < 2; j++){
				oled_sram_write_bit(0, s->x*2 + i, s->y*2 + j);
			}
		}
		s = s->next;
	}
	for(int i = 0; i < 2; i++){
		for (int j = 0; j < 2; j++){
			oled_sram_write_bit(0, food[0]*2 +i, food[1]*2 + j);
		}
	}
	oled_sram_flush(0);
}

void playSnake(){
	//create linked list of snake segments
	segment *first = (segment*)malloc(sizeof(segment));
	first->x = 32;
	first->y = 16;
	segment *last = first;
	first->next = 0;
	first->prev = 0;
	for(int i = 0; i < 4; i++){
		segment *temp = (segment*)malloc(sizeof(segment));
		temp->x = first->x + 1;
		temp->y = first->y;
		temp->next = first;
		temp->prev = 0;
		first->prev = temp;
		first = temp;
	}


	//initalize food
	int food[2];
	placeFood(food, first);

	//initialize direction of snake
	direction S = RIGHT;
	oled_sram_clear_screen(0);
	//gamplay while loop
	while (!detectCollision(first->next, first->x, first->y)){
		Joystick j = get_joystick_position();
		direction D = j.D;
		S = (D == NEUTRAL) ? S : D;
		//Create and set up next snake segment
		segment *temp = (segment*)malloc(sizeof(segment));
		
		temp->x = first->x;
		temp->y = first->y;
		temp->next = first;
		temp->prev = 0;
		first->prev = temp;

		//Find direction of snake movement
		switch (S){
			case UP:
			temp->y--;
			break;
			case DOWN:
			temp->y++;
			break;
			case LEFT:
			temp->x--;
			break;
			case RIGHT:
			temp->x++;
			break;
			default:
			break;
		}

		first = temp;
		
		if(detectCollision(first, food[0], food[1])){//hit food?
			placeFood(food, first);
			temp = 0;
		}
		else{
			temp = last;
			last = last->prev;
			last->next = 0;
			free(temp);
		}
		drawBoard(first, food);
		_delay_ms(100);
	}

}