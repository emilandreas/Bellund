#include <avr/io.h>
#include <arduino.h>
#include <Servo.h>
#include "servo.h"

Servo myServo;

void servo_init(){
  myServo.attach(A4);
}
void servo_set(int pos){
  //Map from % to angle in degrees
  int angle = map(pos, 0, 100,180 ,0);
  myServo.write(angle);
}

