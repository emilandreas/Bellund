/*
 * state_machine.h
 *
 * Created: 08.10.2015 09:51:08
 *  Author: andreabm
 */ 


#ifndef STATE_MACHINE_H_
#define STATE_MACHINE_H_

typedef enum{SLEEP = 0, PLAY_PINGPONG_WEB = 1, PLAY_PINGPONG_JOY = 2, PLAY_PINGPONG_SELF = 3}State;

void state_machine();
void state_set(State state);
State get_current_state();
void send_status(State S, int shot_count);
#endif /* STATE_MACHINE_H_ */
