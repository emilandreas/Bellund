/*
 * PID.h
 *
 * Created: 15.10.2015 09:51:08
 *  Author: andreabm
 */ 


#ifndef PINGPONG_H_
#define PINGPONG_H_

#define JOY_X 0
#define JOY_Y 1 
#define JOY_BUTTON 2
#define L_SLIDE 3
#define R_SLIDE 4
#define L_BUTTON 5
#define R_BUTTON 6
#define WEB_CARRIGE 7
#define WEB_SLIDER 8
#define WEB_BUTTON 9

void pingpong_init();
void play_pingpong();
int input_select(int input_num);

#endif /* PINGPONG_H_ */