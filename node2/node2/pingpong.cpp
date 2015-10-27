/*
 * pingpong.cpp
 *
 * Created: 15.10.2015 10:19:30
 *  Author: andreabm
 */
#include <avr/io.h>
#include <arduino.h>
#include "servo.h"
#include "motor_driver.h"
#include "PID.h"
#include "ir_driver.h"
#include "controll_driver.h"
#include "PID.h"
#include "pingpong.h"
#include "solenoid_driver.h"


void pingpong_init(){
  servo_init();  //Controlling the racket
  motor_init();  
  init_solenoid();
  init_PID(1.25, 1, -0.05, 16); //Initiate PID(kp, ki, kd, ms);
}

void play_pingpong(int servo_input, int carrige_input, int shoot_input){
  int shot_count = 0;
  unsigned long int start_time = millis();
  
  while(get_diode()){
    
    delay(50);
    //shoot
    if (input_select(shoot_input))shoot(); 

    //servo
    servo_set(input_select(servo_input));

    //carrige
    set_pid_reference(input_select(carrige_input));
    controll_motor(-controllSignal()); 
  }
  
}

int input_select(int input_num){
  switch(input_num){
    case JOY_X: 
      return (get_controller().X + 100)/2;
    case JOY_Y:
      return (get_controller().Y + 100)/2;
    case JOY_BUTTON:
      return get_controller().joy_button;
    case L_SLIDE:
      return get_controller().left_slider;
    case R_SLIDE:
      return get_controller().right_slider;
    case L_BUTTON:
      return get_controller().left_button;
    case R_BUTTON:
      return get_controller().right_button;
    case WEB_CARRIGE:
      break;
    case WEB_SLIDER:
      break;
    case WEB_BUTTON:
      break;
    default:
      break;
  }
}

