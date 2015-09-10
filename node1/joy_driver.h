/*
 * joy_driver.h
 *
 * Created: 10.09.2015 09:16:07
 *  Author: andreabm
 */ 


#ifndef JOY_DRIVER_H_
#define JOY_DRIVER_H_

typedef enum  {LEFT, RIGHT, UP, DOWN, NEUTRAL} direction;

typedef struct { 
	int X;
	int Y;
	direction D;
} Joystick;

Joystick getJoystickPosition();
direction getJoystickDirection(int x, int y);


#endif /* JOY_DRIVER_H_ */