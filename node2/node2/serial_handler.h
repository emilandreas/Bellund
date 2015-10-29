/*
 * serial_handler.h
 *
 * Created: 15.10.2015 09:51:08
 *  Author: andreabm
 */ 


#ifndef SERIAL_HANDLER_H_
#define SERIAL_HANDLER_H_

void init_serial();
void serialEvent();
void handel_command(String str);
void parse_command(String str, int command[]);

#endif /* SERIAL_HANDLER_H_ */
