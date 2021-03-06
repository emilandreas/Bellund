/*
 * message_handler.cpp
 *
 * Created: 08.10.2015 10:19:30
 *  Author: andreabm
 */
#include <avr/io.h>
#include <arduino.h>
#include "state_machine.h"
#include "pingpong.h"
#include "serial_handler.h"
#include "message_handler.h"

volatile State current_state = SLEEP;
volatile State next_state = SLEEP;

void state_machine(){
    serialEvent(); //check if message from server
    switch(current_state){
      case SLEEP:
        switch(next_state){
          case PLAY_PINGPONG_SELF:
          case PLAY_PINGPONG_WEB:
          case PLAY_PINGPONG_JOY:
            pingpong_init();
            break;
          case SLEEP:
            //send_status(current_state, 0);
            break;
        }
        break;
      case PLAY_PINGPONG_SELF:
      case PLAY_PINGPONG_WEB:
      case PLAY_PINGPONG_JOY:
        switch(next_state){
          case PLAY_PINGPONG_WEB:
            play_pingpong(JOY_X, WEB_SLIDER, WEB_BUTTON);
            break;
          case PLAY_PINGPONG_JOY:
            play_pingpong(JOY_X, R_SLIDER, JOY_Y);
            break;
          case PLAY_PINGPONG_SELF:
            play_pingpong(JOY_X, CAM_X, JOY_Y);
            break;
          case SLEEP:
            break;
        }
        break;
    }
    //printf("state: %i\n", (int)current_state);
    current_state = next_state;
    delay(20);
}

void send_status(State S, int shot_count){
  Message m;
  m.id = GAME_STATUS;
  m.length = 2;
  m.data[0] = S;
  m.data[1] = shot_count;
  CAN_transmit(&m);
}

/////////////////////////////
//External state manipulation
/////////////////////////////
State get_current_state(){
  return current_state;
}

void state_set(State state){
  next_state = state;
}

