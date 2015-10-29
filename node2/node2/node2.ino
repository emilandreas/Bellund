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

void setup() {
  uart_setup();
  
  //Start can
  CAN_init();

  handler_init();
  init_pingpong_message();
}
int count = 0;
long int enc_val = 0;
void loop(){
  printf("pingpong_message_status: %i \n",pingpong_message_status());
  if(pingpong_message_status()){
    play_pingpong(JOY_X, R_SLIDER, JOY_Y);
  }
  
  if (++count%10 == 0){
      printf("pingpong_message_status: %i \n",pingpong_message_status());
      count = 0;
  }

  
  delay(25);

}




