/*
 * joy_driver.h
 *
 * Created: 10.09.2015 09:16:07
 *  Author: andreabm
 */ 


#ifndef JOY_DRIVER_H_
#define JOY_DRIVER_H_

#include <stdio.h>

typedef enum  {LEFT, RIGHT, UP, DOWN, NEUTRAL} direction;

typedef struct { 
	int8_t X;
	int8_t Y;
	direction D;
} Joystick;

typedef struct {
	int left;
	int right;
} Slider;

Joystick getJoystickPosition();
direction getJoystickDirection(int x, int y);
void calibrateJoystick();
Slider getSliderPosition();

#endif /* JOY_DRIVER_H_ */