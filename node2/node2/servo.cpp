#include <avr/io.h>
#include <arduino.h>
#include <Servo.h>
#include "servo.h"

Servo myServo;
int prev_angle = 0;

void servo_init(){
  myServo.attach(18,900,2100);
}
void servo_set(int pos){
  //Map from % to angle in degrees
  int angle = map(pos, 0, 100,180 ,10);
  if (abs(angle - prev_angle) > 3){
    myServo.write(angle);
    prev_angle = angle;
  }
}

