/*
 * pingpong.h
 *
 * Created: 29.10.2015 12:05:43
 *  Author: andreabm
 */ 


#ifndef PINGPONG_H_
#define PINGPONG_H_

typedef enum{SLEEP = 0, PLAY_PINGPONG_WEB = 1, PLAY_PINGPONG_JOY = 2}State;

void play_pingpong(uint8_t controller_mode);
void play_pingpong_web();
void play_pingpong_joy();
void state_set(State state);
void score_set(uint8_t score);


#endif /* PINGPONG_H_ */