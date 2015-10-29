/*
 * pingpong.c
 *
 * Created: 29.10.2015 12:05:33
 *  Author: andreabm
 */ 

#include "pingpong.h"
#include "message_handler.h"
#include "CAN_driver.h"
void start_pingpong(){
	Message *m;
	m->id = STARTPONG;
	m->length = 0;
	CAN_transmit(m);
}