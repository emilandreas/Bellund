
#include <stdlib.h>
#include <util/delay.h>
#include "pong.h"
#include "../Driver_files/joy_driver.h"
#include "../Driver_files/oled_driver.h"

#define LEFT 0
#define RIGHT 1
#define RACKETSIZE 16

typedef struct{
	int posX;
	float posY;
	int angle; // from -45 deg to + 45 deg 
	int dir; //left or right
} Ball;

typedef struct{
	int pos; // from 0 to 45 (16 in width)
} Racket;

int racketHit(Ball *ball, int racketPos){
	if (ball->posY >= racketPos && ball->posY < racketPos + RACKETSIZE )
		return 1;
	return 0;
}

void updateBallAngle(Ball *ball, int racketPos){
	float hitPos = (float)(ball->posY - racketPos - 8)/8; //from -1 to 1
	int newBallAngle = ball->angle + hitPos * 45;
	if(newBallAngle > 45) ball->angle = 45;
	else if(newBallAngle < -45) ball->angle = 45;
	else ball->angle = newBallAngle;
}

void ballInit(Ball *ball){
	ball->dir = rand() % 2;
	ball->angle = (rand() % 91) - 45;
}

void updateBallPosition(Ball *ball){
	float tempPosY = ball->posY + ((float)(ball->angle)/45);
	
	//hits the wall
	if (tempPosY > 63){ 
		ball->posY = 63 - (tempPosY - 63);
		ball->angle *= -1;
	}
	else if (tempPosY < 0){
		ball->posY = -1*tempPosY;
		ball->angle *= -1;
	}
	else ball->posY = tempPosY;
	if(ball->dir == RIGHT) ball->dir++;
	else ball->dir--;
}

int playRound(){
	Ball ball;
	Slider slide;
	ballInit(&ball);
	
	while(1){
		slide = getSliderPosition();
		updateScreen:	

		if (ball.posX >= 127){
			if (racketHit(&ball, slide.right) ){
				ball.dir = LEFT;
				updateBallAngle(&ball, slide.right);
			}
			else{
				return LEFT;
			}
		}
		else if (ball.posX == 0){
			if (racketHit(&ball, slide.left) ){
				ball.dir = RIGHT;
				updateBallAngle(&ball, slide.left);
			}
			else {
				return RIGHT;
			}
		}
		updateScreen(ball, slide.left, slide.right);
		_delay_ms(200);
	}
}

void playPong(){
	int pointLeft = 0;
	int pointRight = 0;
	int point;
	oled_sram_clear_screen(0);
	while(1){
		point = playRound();
		if(pointLeft == 5){
			printEndScreen("Player Right won!");
		}
		else if(pointRight == 5){
			printEndScreen("Player Left won!");
		}
	}
}

void updateScreen(Ball ball, int leftRacketPos, int rightRacketPos){
	oled_sram_clear_screen(0);
	for (int i = 0; i < RACKETSIZE; i++){
		oled_sram_write_bit(0, 0, leftRacketPos + i);
		oled_sram_write_bit(0,126, rightRacketPos + i);
	}
	oled_sram_write_bit(0, ball.posX, ball.posY);
	oled_sram_flush(0);
}

void printEndScreen(char *endMessage){
	oled_sram_clear_screen(0);
	for(int i = 0; i < 10; i++){
		if( i % 2 ){
			oled_sram_write_string(0, endMessage, 2);
			_delay_ms(300);
		}
		else _delay_ms(300);
	}
}