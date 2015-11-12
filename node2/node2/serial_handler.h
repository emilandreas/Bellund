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
void pass_highscore_to_web(uint8_t place, char initial_1, char initial_2, char initial_3, uint8_t score);

#endif /* SERIAL_HANDLER_H_ */
