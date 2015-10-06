/*
 * snake.h
 *
 * Created: 22.09.2015 21:39:07
 *  Author: andreabm
 */ 


#ifndef SNAKE_H_
#define SNAKE_H_

typedef struct segment segment;

struct segment{
	segment *next, *prev; //pointer to next and preveouse segment
	int x, y; // x and y position of segment
};

int detectCollision(segment *s, int x, int y);

void placeFood(int food[], segment *first);

void playSnake();



#endif /* SNAKE_H_ */
