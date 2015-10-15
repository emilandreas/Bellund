#include <avr/io.h>
#include <arduino.h>
#include "controll_driver.h"
#include "message_handler.h"
extern "C"{
#include "CAN_driver.h"
}

Joystick joy;

Joystick get_joy(){
  return joy;
}

void update_joy(int x, int y, int d){
    joy.X = x;
    joy.Y = y;
    joy.D = (direction)d;
}

void req_joy(){
  Message m;
  m.id = JOYREQ;
  m.length = 0;
  CAN_transmit(&m);
}


