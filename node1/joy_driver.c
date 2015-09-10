/*
 * Joy_driver.c
 *
 * Created: 10.09.2015 09:16:12
 *  Author: andreabm
 */
#include "joy_driver.h"
#include "adc_driver.h"
#include <math.h>

Joystick getJoystickPosition(){
	Joystick joy;
	joy.Y = ((get_adc(2)-127)*100)/128;
	joy.X = ((get_adc(3)-127)*100)/128;
	joy.D = getJoystickDirection(joy.X, joy.Y);
	return joy;
}

direction getJoystickDirection(int x, int y){
	
	if(fabs(x) < 50 && fabs(y) < 50){
		return NEUTRAL;
	}
	
	if(fabs(x) < fabs(y)){
		if(y > 0){
			return UP;
		}
		else{
			return DOWN;
		}
	}
	else{
		if(x > 0){
			return RIGHT;
		}
		else{
			return LEFT;
		} 
	}
}