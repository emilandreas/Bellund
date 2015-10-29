/*
 * message_handler.h
 *
 * Created: 08.10.2015 09:51:08
 *  Author: andreabm
 */ 


#ifndef MESSAGE_HANDLER_H_
#define MESSAGE_HANDLER_H_
extern "C"{
#include "CAN_driver.h"
}


void handler_init();

void handle_message();

// Message types
#define JOY             0
#define JOYREQ          1
#define HighScore       2
#define START_PINGPONG  3

#endif /* MESSAGE_HANDLER_H_ */
