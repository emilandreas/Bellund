/*
 * message_handler.c
 *
 * Created: 08.10.2015 10:19:30
 *  Author: andreabm
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include "message_handler.h"
#include "CAN_driver.h"
#include "joy_driver.h"
#include "../Game_files/pingpong.h"

volatile int handelingMessage = 0;


void init_handler(){
	// Set pin as input (PD3 = INT1)
	DDRD &= ~(1 << PD3);
	// Set internal pull-up
	PORTD |= (1 << PD3);
	
	//initialize external interrupt on falling edge
	MCUCR |= (1<<ISC11);
	MCUCR &= ~(1<<ISC10);
	GICR = (1<<INT1);
	
	//Enable global interrupts
	sei();
}

ISR(INT1_vect){
	handle_message();
}


void handle_message(){
	Message m;
	CAN_receive(&m);
	
	//Decide what to do
	switch(m.id){
		case JOY:
			break;
		case JOYREQ:
			send_controlls();
			break;
		case GAME_STATUS:
			state_set(m.data[0]);
			score_set(m.data[1]);
			break;
		default:
			break;
	}
}

void send_controlls(){
	Message m;
	Joystick J;
	Slider S;
		
	//Joystick
	J = get_joystick_position();
	m.id = JOY;
	m.length = 8;
	m.data[0] = J.X;
	m.data[1] = J.Y;
	m.data[2] = J.D;
	m.data[3] = J.Button;
		
	//Slider
	S = get_slider_position();
	m.data[4] = S.left;
	m.data[5] = S.right;
	m.data[6] = S.leftButton;
	m.data[7] = S.rightButton;
		
	//Send can message
	CAN_transmit(&m);
}




