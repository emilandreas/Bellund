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

void camera_init(){
  //start pixy I2C driver
  pixy.init();
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

