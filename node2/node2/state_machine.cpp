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

volatile State current_state = SLEEP;
volatile State next_state = SLEEP;

void state_machine(){
    delay(20);
    switch(current_state){
      case SLEEP:
        switch(next_state){
          case PLAY_PINGPONG:
            start_pingpong();
            break;
          case SLEEP:
            break;
      }
      break;
      case PLAY_PINGPONG:
        switch(next_state){
          case PLAY_PINGPONG:
            //play_pingpong(JOY_X, WEB_SLIDER, WEB_BUTTON);
            play_pingpong(JOY_X, R_SLIDER, JOY_Y);
            break;
          case SLEEP:
            //send message to node 1
            break;
        }
        break;
    }
    printf("state: %i\n", current_state);
    current_state = next_state;
}

void state_set(State state){
  next_state = state;
}

