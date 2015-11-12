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
void init_pingpong_message();
int pingpong_message_status();
void handle_message();
void request_highscore(uint8_t place);

// Message types
#define JOY             0
#define JOYREQ          1
#define GAME_STATUS     2
#define HIGHSCORE       3


#endif /* MESSAGE_HANDLER_H_ */
