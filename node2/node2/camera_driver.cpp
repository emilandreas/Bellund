/*
 * camera_driver.cpp
 *
 * Created: 15.10.2015 10:19:30
 *  Author: andreabm
 */
 #include <Wire.h>
#include <avr/io.h>
#include <arduino.h>
#include "PixyI2C.h"

PixyI2C pixy;

uint16_t ball_pos_x = 150;
uint16_t ball_pos_y = 150;

uint16_t shooter_pos_x = 150;
uint16_t shooter_pos_y = 150;

void camera_init(){
  //start pixy I2C driver
  pixy.init();
}

void update_pos(){
  uint16_t blocks;
  blocks = pixy.getBlocks();
  if (blocks){
    for(int i = 0; i < 2; i++){
      //printf("B: %i, S: %i, X:%i \n", blocks, pixy.blocks[i].signature, pixy.blocks[i].x);
      switch(pixy.blocks[i].signature){
        case 1:
          //printf("Ball: %i, %i \t \n", pixy.blocks[i].signature,pixy.blocks[i].x);
          ball_pos_x = pixy.blocks[i].x;
          ball_pos_y = pixy.blocks[i].y;
          break;
        case 2:
          //printf("Shooter: %i, %i \n",  pixy.blocks[i].signature,pixy.blocks[i].x);
          shooter_pos_x = pixy.blocks[i].x;
          shooter_pos_y = pixy.blocks[i].y;
          break;
        default:
          break;
      }
    }
  }
}

uint16_t get_ball_pos_x(){
  update_pos();
  int value = map(ball_pos_x,320-60,60, 0, 99); // 0, 319 is left, right limit of pixi
  if (value > 100){
    value = 100;
  }
  else if (value < 0){
    value = 0;
  }
  return value;
}

uint16_t get_shooter_pos_x(){
  update_pos();
  int value = map(shooter_pos_x,280,50, 0, 99); // 0, 319 is left, right limit of pixi
  if (value > 100){
    value = 100;
  }
  else if (value < 0){
    value = 0;
  }
  return value;
}

int get_camera_error(){
  update_pos();
  //printf("Error: %i \n", ((int)shooter_pos_x - (int)ball_pos_x)/4);
  return -((int)ball_pos_x - (int)shooter_pos_x)/4;
}


uint16_t get_ball_pos_y(){
  update_pos();
  int value = map(ball_pos_x,280,50, 0, 99); // 0, 319 is left, right limit of pixi
  if (value > 100){
    value = 100;
  }
  else if (value < 0){
    value = 0;
  }
  return value;
}

void camera_test(){
  int i = 0;
  int j;
  while(1){
    uint16_t blocks;
    blocks = pixy.getBlocks();
    
    if (blocks)
    {
      i++;
      
      // do this (print) every 50 frames because printing every
      // frame would bog down the Arduino
      if (i%50==0)
      {
        printf("Detected %d:\n", blocks);
        for (j=0; j<blocks; j++)
        {
          printf("  block %d: ", j);
          pixy.blocks[j].print();
        }
      }
    }  
  }
}

