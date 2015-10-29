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
  uint8_t left_slider;
  uint8_t right_slider;
  uint8_t left_button;
  uint8_t right_button;
  int8_t X;
  int8_t Y;
  int8_t joy_button;
  direction D;
} Controller;

typedef struct { 
  uint8_t X;
  uint8_t S;
  uint8_t B;
} Web;

Web get_web();

void update_web(int x, int slider, int button);

Controller get_controller();

void update_controller( int x, int y, int d, uint8_t joy_button, uint8_t left_slider, uint8_t right_slider, uint8_t left_button, uint8_t right_button);

void req_controller(); //request update on controller input

#endif /* CONTROLL_DRIVER_H_ */
