/*
 * message_handler.cpp
 *
 * Created: 08.10.2015 10:19:30
 *  Author: andreabm
 */
#include <avr/io.h>
#include <arduino.h>
#include <avr/interrupt.h>
#include "controll_driver.h"
#include "message_handler.h"
#include "pingpong.h"


extern "C"{
#include "CAN_driver.h"
}


//Logic to check if pingpong message have been sent from node1 to node2
int play_pingpong_message;

void init_pingpong_message(){
  play_pingpong_message = 0;
}
int pingpong_message_status(){
  return play_pingpong_message;
}



void handler_init(){
   attachInterrupt(digitalPinToInterrupt(2),handle_message, FALLING);
}

void handle_message(){
  Message m;
  CAN_receive(&m);  
  //Decide what to do
  play_pingpong_message = m.id;
  switch(m.id){
    case JOY:
      update_controller(m.data[0], m.data[1], m.data[2], m.data[3], m.data[4], m.data[5], m.data[6], m.data[7]);
      break;
    case START_PINGPONG:      
      play_pingpong_message = 1;
      break;
    case EXIT_PINGPONG:
      printf("\n\nEXITING PINGPONG\n\n");
      play_pingpong_message = 1;
      break;
    default:
      break;
  }
}
