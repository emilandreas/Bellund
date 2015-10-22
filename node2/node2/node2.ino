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

void setup() {
  uart_setup();
  
  //Start servo
  //servo_init();
  
  //Start can
  CAN_init();

  //start motor
  motor_init();
  handler_init();

  //Initiate PID(kp, ki, kd, ms)
  init_PID(1.25, 1, -0.05, 16);
}
int count = 0;
long int enc_val = 0;
void loop(){
  /*
  enc_val = get_position();
  if (++count%10 == 0){
      printf("encoder: %li \n",enc_val);
      count = 0;
  }
  controll_motor(get_joy().X);
  req_joy();
  //printf("JoyX: %i JoyY: %i",get_joy().X, get_joy().Y);
  */
  //printf("encoder: %i, %i \n",read_encoder(), (int)get_position());
  delay(25);
  controll_motor(-controllSignal());
}




