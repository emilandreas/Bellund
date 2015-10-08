/*
 * Joy_driver.c
 *
 * Created: 10.09.2015 09:16:12
 *  Author: andreabm
 */

#define F_CPU 4915200
#include <avr/io.h>
#include <stdio.h>
#include "joy_driver.h"
#include "adc_driver.h"
#include <math.h>
#include "oled_driver.h"
#include <avr/io.h>
#include <util/delay.h>

float xMean = 127;
float yMean = 127;

Slider getSliderPosition(){
	Slider slide;
	slide.left = ((get_adc(0))*100)/255;
	slide.right = ((get_adc(1))*100)/255;
	return slide;
}

Joystick getJoystickPosition(){
	Joystick joy;
	joy.Y = ((get_adc(2)-yMean)*100)/yMean;
	joy.X = ((get_adc(3)-xMean)*100)/xMean;
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

void calibrateJoystick(){
	uint8_t yMax = 127;
	uint8_t yMin = 127;
	uint8_t xMax = 127;
	uint8_t xMin = 127;
	for (int i = 0; i < 1000; i++)
	{
		uint8_t y = get_adc(2);
		uint8_t x = get_adc(3);
		
		yMin = (y < yMin) ? y : yMin;
		xMin = (x < xMin) ? x : xMin;
		
		xMax = (x > xMax) ? x : xMax;
		yMax = (y > yMax) ? y : yMax;
		_delay_ms(5);
		if (i%200 == 0){
			calibration_visual_countdown(i);
		}
	}
	
	yMean = (yMax - yMin)/2.0;
	xMean = (xMax - xMin)/2.0;
	printf("%i %i %i %i", yMin, yMax, xMin, xMax);
}

void calibration_visual_countdown(int i){
	char c = (1000-i)/200 + 48;
	oled_sram_clear_screen(0);
	oled_sram_write_string(0,"Move Joystick",0);
	oled_sram_write_string(0,"Time left: ", 2);
	oled_sram_write_char(0, &c, 2, 12*8); //writes count after "Time left: "
	oled_sram_flush(0);
}