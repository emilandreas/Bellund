/*
 * pingpong.h
 *
 * Created: 29.10.2015 12:05:43
 *  Author: andreabm
 */ 


#ifndef PINGPONG_H_
#define PINGPONG_H_

typedef enum{SLEEP = 0, PLAY_PINGPONG = 1}State;

void play_pingpong();
void state_set(State state);
void score_set(uint8_t score);


#endif /* PINGPONG_H_ */