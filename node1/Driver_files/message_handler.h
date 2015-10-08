/*
 * message_handler.h
 *
 * Created: 08.10.2015 09:51:08
 *  Author: andreabm
 */ 


#ifndef MESSAGE_HANDLER_H_
#define MESSAGE_HANDLER_H_
#include "CAN_driver.h"

void init_handler();

void handle_message();

// Message types
#define JOY			0
#define JOYREQ		1
#define HighScore	2

#endif /* MESSAGE_HANDLER_H_ */