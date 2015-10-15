#include <Wire.h>
#include <Servo.h>
#include <avr/io.h>
#include <stdio.h>

extern "C" {
#include "CAN_driver.h"
#include "spi_driver.h"
#include "MCP_driver.h"
#include "ir_driver.h"
}

#include "motor_driver.h"
#include "servo.h"
#include "print.h"
#include "controll_driver.h"
#include "message_handler.h"

void setup() {
  uart_setup();
  
  //Start servo
  //servo_init();
  
  //Start can
  CAN_init();

  //start motor
  motor_init();
  handler_init();
}

void loop(){
  controll_motor(get_joy().X);
  printf("encoder: %i \n",read_encoder());
  req_joy();
  printf("JoyX: %i JoyY: %i",get_joy().X, get_joy().Y);
  delay(50);
}


