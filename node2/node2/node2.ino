#include <Wire.h>
#include <Servo.h>
#include <avr/io.h>
#include <stdio.h>

extern "C" {
#include "CAN_driver.h"
}
#include "print.h"
#include "message_handler.h"
#include "state_machine.h"
#include "serial_handler.h"


void setup() {
  uart_setup();  
  CAN_init();
  handler_init();
  init_serial();
}

void loop(){
  state_machine();
}




