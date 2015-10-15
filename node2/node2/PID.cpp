/*
 * PID.cpp
 *
 * Created: 15.10.2015 10:19:30
 *  Author: andreabm
 */
#include <avr/io.h>
#include <arduino.h>
#include <avr/interrupt.h>
#include "PID.h"

#define k 3 //current index

volatile int u[k+1] = {0};
volatile int e[k+1] = {0};
double Kp, Ki, Kd, T;

int controllSignal(){
  return u[k];
}

void init_PID(double kp, double ki, double kd, int ms){
  Kp = kp;
  Ki = ki;
  Kd = kd;
  T = (double)ms/1000;

  TCCR2A = 0;                           // set entire TCCR1A register to 0
  TCCR2B = 0;                           // same for TCCR1B
  TCNT2  = 0;                           //initialize counter value to 0
  TCCR2B |= (1 << CS22) | (1 << CS20);  // Set CS10 and CS12 bits for 1024 prescaler
  OCR2A = F_CPU/1024*T;                 // set compare match register for (1/T)Hz increments
  TCCR2B |= (1 << WGM21);               // turn on CTC mode
  TIMSK2 |= (1 << OCIE2A);              // enable timer compare interrupt
  sei();                                // interrupts globally enabled
}

ISR(TIMER2_COMPA_vect){
  pid(0); //runs pid with new error
}

void pid(int error){
  //move samples in list u and e
  for(int i = 0; i < k; i++){
    u[i] = u[i+1];
    e[i] = e[i+1];
  }
  e[k] = error;
  
  //Z-transform of pid reguator
  double a = (Kp + Ki*T/2 +Kd/T);
  double b = (-Kp + Ki*T/2-2*Kd/T);
  double c = Kd/T;

  u[k] = u[k - 1] + a*e[k] + b*e[k-1] + c*e[k-2];
}


