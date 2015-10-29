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
#include "serial_handler.h"

void pingpong_init(){
  init_serial();
  servo_init();  //Controlling the racket
  motor_init();  
  init_solenoid();
  init_PID(2.25, 1, 0, 16); //Initiate PID(kp, ki, kd, ms);
}

void play_pingpong(int servo_input, int carrige_input, int shoot_input){
  int shot_count = 0;
  unsigned long int start_time = millis();
  int is_shooting = 0;
  while(true){
    
    delay(30);
    //shoot
    if (input_select(shoot_input)>90 && !is_shooting){
      is_shooting = 1;
      shoot(); 
    }
    else if(input_select(shoot_input)< 90){
      is_shooting = 0;
    }

    //servo
    servo_set(input_select(servo_input));

    //carrige
    printf("%i \t %i \t %i\n", input_select(carrige_input), input_select(servo_input), input_select(shoot_input));
    set_pid_reference(input_select(carrige_input));
    controll_motor(controllSignal()); 
    req_controller();
    serialEvent();
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
    case L_SLIDER:
      return get_controller().left_slider;
    case R_SLIDER:
      return get_controller().right_slider;
    case L_BUTTON:
      return get_controller().left_button;
    case R_BUTTON:
      return get_controller().right_button;
    case WEB_CARRIGE:
      return get_web().X;
    case WEB_SLIDER:
      return get_web().S;
    case WEB_BUTTON:
      return get_web().B;
    default:
      break;
  }
}

