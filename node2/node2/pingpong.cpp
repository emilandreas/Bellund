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
#include "controll_driver.h"
#include "PID.h"
#include "pingpong.h"
#include "solenoid_driver.h"
#include "message_handler.h"
#include "CAN_driver.h"
#include "state_machine.h"
#include "ir_driver.h"

int shot_count;
unsigned long int start_time;
int is_shooting;

void pingpong_init(){
  servo_init();  //Controlling the racket
  motor_init();  
  init_solenoid();
  init_PID(2.25, 1, 0, 16); //Initiate PID(kp, ki, kd, ms);
}

void start_pingpong(){
  pingpong_init();
  int shot_count = 0;
  unsigned long int start_time = millis();
  int is_shooting = 0;
}

void send_status(State S){
  Message m;
  m.id = GAME_STATUS;
  m.length = 2;
  m.data[0] = S;
  m.data[1] = shot_count;
  CAN_transmit(&m);
}


void play_pingpong(int servo_input, int carrige_input, int shoot_input){
  //shoot
  if (input_select(shoot_input)>90 && !is_shooting){
    is_shooting = 1;
    shoot(); 
    shot_count++;
  }
  else if(input_select(shoot_input)< 90){
    is_shooting = 0;
  }
  //servo
  servo_set(input_select(servo_input));

  //carrige
  //printf("Slider: %i \n", input_select(carrige_input));
  set_pid_reference(input_select(carrige_input));
  controll_motor(controllSignal()); 
  //req_controller();
  
  if(!get_diode()){
    state_set(SLEEP);
    delay(50);
    send_status(SLEEP);
    stop_pid();
    send_status(PLAY_PINGPONG);
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
      break;
    case WEB_SLIDER:
      return get_web().S;
      break;
    case WEB_BUTTON:
      return get_web().B;
      break;
    default:
      break;
  }
}

