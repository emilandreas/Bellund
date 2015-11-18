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
#include "camera_driver.h"

int shot_count;
unsigned long int start_time;
int is_shooting;

void pingpong_init(){
  servo_init();  //Controlling the racket
  motor_init();  
  init_solenoid();
  init_PID(2.25, 1, 0, 16); //Initiate PID(kp, ki, kd, ms);
  camera_init();
  shot_count = 0;
  start_time = millis();
  is_shooting = 0;
}


void play_pingpong(int servo_input, int carrige_input, int shoot_input){
  //shoot
  if (input_select(shoot_input)>90 && !is_shooting){
    is_shooting = 1;
    shoot(); 
    shot_count++;
    send_status(get_current_state(), shot_count);
  }
  else if(input_select(shoot_input)< 90){
    is_shooting = 0;
  }
  //servo
  servo_set(input_select(servo_input));
  //Choose where to get pid error
  switch(get_current_state()){
    case PLAY_PINGPONG_WEB:
    case PLAY_PINGPONG_JOY:
      set_pid_error(input_select(carrige_input) - get_position());
      break;
    case PLAY_PINGPONG_SELF:
      //set_pid_error(get_camera_error());
      set_pid_error((get_ball_pos_x()-get_position()));
      break;
  }
  //carrige
  controll_motor(controllSignal());
  //printf("Get_diode: %i\n",get_diode());
  if(!get_diode()){
    state_set(SLEEP);
    delay(100);
    send_status(SLEEP, shot_count);
    delay(100);
    send_status(SLEEP, shot_count);
    stop_pid();
    shot_count = 0;
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
    case CAM_X:
      return get_ball_pos_x();
      break;
    case CAM_Y:
      return get_ball_pos_y();
      break;
    default:
      break;
  }
}

