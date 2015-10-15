#include <avr/io.h>
#include <arduino.h>
#include <Wire.h>
#include "DAC_driver.h"


void DAC_init(){
    Wire.begin();
}


void DAC_send(int command, int data){
  Wire.beginTransmission(0b0101000);
  Wire.write(command); //Command
  Wire.write(data);
  Wire.endTransmission();
}


