/*
 * servo.h
 *
 * Created: 08.10.2015 14:59:27
 *  Author: andreabm
 */ 


#ifndef CONTROLL_DRIVER_H_
#define CONTROLL_DRIVER_H_
typedef enum  {LEFT, RIGHT, UP, DOWN, NEUTRAL} direction;
typedef struct { 
  int8_t X;
  int8_t Y;
  direction D;
} Joystick;

Joystick get_joy();
void update_joy(int x, int y, int d);

void req_joy();

#endif /* CONTROLL_DRIVER_H_ */
