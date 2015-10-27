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

extern "C"{
#include "CAN_driver.h"
}



void handler_init(){
   attachInterrupt(digitalPinToInterrupt(2),handle_message, FALLING);
}

void handle_message(){
  Message m;
  CAN_receive(&m);  
  //Decide what to do
  switch(m.id){
    case JOY:
      update_controller(m.data[0], m.data[1], m.data[2], m.data[3], m.data[4], m.data[5], m.data[6], m.data[7]);
      break;
    default:
      break;
    
  }
}
