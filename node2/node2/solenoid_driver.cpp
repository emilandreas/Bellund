/*
 * SOLENOID_DRIVER.cpp
 *
 * Created: 15.10.2015 10:19:30
 *  Author: andreabm
 */
#include <avr/io.h>
#include <arduino.h>

#define SHOOTPIN 5

void init_solenoid(){
  pinMode(SHOOTPIN, OUTPUT);
  digitalWrite(SHOOTPIN, HIGH);
}

void shoot(){
  digitalWrite(SHOOTPIN, LOW);
  unsigned long int time = millis();
  while(time + 50 > millis());
  digitalWrite(SHOOTPIN, HIGH);
}

