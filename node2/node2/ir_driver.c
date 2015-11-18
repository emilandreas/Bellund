/*
 *
 * Created: 24.09.2015 09:34:13
 *  Author: andreabm
 */ 
#include <avr/io.h>
#include <arduino.h>
#include "ir_driver.h"


int get_diode(){

  return analogRead(A0)> 100;
}
