/*
* snake.c
*
* Created: 22.09.2015 21:39:07
*  Author: andreabm
*/

#define F_CPU 4915200

#include "snake.h"
#include "joy_driver.h"
#include <util/delay.h>
#include "oled_driver.h"
#include <stdlib.h>

//Board dimentions
#define width 64
#define height 32

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
		food[0] = rand() % width;
		food[1] = rand() % height;
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


void addSegment(segment* first, int x, int y){
	segment *temp = (segment*)malloc(sizeof(segment));
	temp->x = x;
	temp->y = y;
	temp->next = first;
	temp->prev = 0;
	first->prev = temp;
	first = temp;
}

void deleteSegment(segment* last){
	segment* temp = last;
	last = last->prev;
	if(!(last == 0)){
		last->next = 0;
	}
	free(temp);
}

void playSnake(){
	//create linked list of snake segments
	segment *first = (segment*)malloc(sizeof(segment));
	first->x = height/2;
	first->y = width/2;
	segment *last = first;
	first->next = 0;
	first->prev = 0;
	for(int i = 0; i < 4; i++){
		addSegment(first, first->x+1, first->y);
	}


	//initalize food
	int food[2];
	placeFood(food, first);

	//initialize direction of snake
	direction S = RIGHT;
	
	//gamplay while loop
	while (!detectCollision(first->next, first->x, first->y)){
		//Get user input and save in D
		direction D = getJoystickPosition().D;
		S = (D == NEUTRAL) ? S : D;
		//Create and set up next snake segment
		addSegment(first, first->x, first->y);

		//Find direction of snake movement
		switch (S){
			case UP:
				first->y = (first->y + height - 1)%height;
				break;
			case DOWN:
				first->y = (first->y + 1)%height;
				break;
			case LEFT:
				first->x = (first->x + width -1)%width;
				break;
			case RIGHT:
				first->x = (first->x + 1)%width;
				break;
			default:
			break;
		}
		
		//If snakes hits food it becomes longer else delete last segment
		if(detectCollision(first, food[0], food[1])){//hit food?
			placeFood(food, first);
		}
		else{
			deleteSegment(last);
		}
		drawBoard(first, food);
		_delay_ms(100); //Speed of snake
	}
	//Clear memory
	while(last){
		deleteSegment(last);
	}

}
