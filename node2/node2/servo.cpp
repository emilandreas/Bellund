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
  int angle = map(pos, -100, 100,150 ,50);
  myServo.write(angle);
}

