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
	uint8_t Button;
} Joystick;

typedef struct {
	uint8_t left;
	uint8_t right;
	uint8_t leftButton;
	uint8_t rightButton;
} Slider;

Joystick getJoystickPosition();
direction getJoystickDirection(int x, int y);
void calibrateJoystick();
Slider getSliderPosition();

#endif /* JOY_DRIVER_H_ */
