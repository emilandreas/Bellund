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
#include "PID.h"
#include "solenoid_driver.h"
#include "pingpong.h"
#include "state_machine.h"
#include "serial_handler.h"
#include "camera_driver.h"

void setup() {
  uart_setup();  
  //Start can
  CAN_init();
  handler_init();
  init_serial();
  camera_init();
}

int count = 0;
void loop(){
  //camera_test();
  state_machine();
  serialEvent();
}




