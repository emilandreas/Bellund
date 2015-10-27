#include <avr/io.h>
#include <arduino.h>
#include "controll_driver.h"
#include "message_handler.h"
extern "C"{
#include "CAN_driver.h"
}

Controller joy;

Controller get_controller(){
  return joy;
}

void update_controller( int x, int y, int d,uint8_t joy_button, uint8_t left_slider, uint8_t right_slider, uint8_t left_button, uint8_t right_button){
    joy.left_slider = left_slider;
    joy.right_slider = right_slider;
    joy.left_button = left_button;
    joy.right_button = right_button;
    joy.X = x;
    joy.Y = y;
    joy.D = (direction)d;
}

void req_controller(){
  Message m;
  m.id = JOYREQ;
  m.length = 0;
  CAN_transmit(&m);
}


