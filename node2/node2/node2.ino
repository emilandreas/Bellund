#include <Wire.h>
#include <Servo.h>
#include <avr/io.h>
#include <stdio.h>

extern "C" {
#include "CAN_driver.h"
#include "spi_driver.h"
#include "MCP_driver.h"
}

#include "motor_driver.h"
#include "servo.h"
#include "print.h"
#include "controll_driver.h"
#include "message_handler.h"
#include "state_machine.h"
#include "serial_handler.h"


void setup() {
  uart_setup();  
  //Start can
  CAN_init();
  handler_init();
  init_serial();
}

void loop(){
  state_machine();
  serialEvent();
}




