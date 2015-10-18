/*
 * serial_handler.cpp
 *
 * Created: 15.10.2015 10:19:30
 *  Author: andreabm
 */
#include <avr/io.h>
#include <arduino.h>
#include <avr/interrupt.h>
#include "serial_handler.h"

String inputString = "";        // a string to hold incoming data

void init_serial(){
  Serial.begin(9600);
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      String str = inputString;
      inputString = "";
      handel_command(str);
    }
  }
}

void handel_command(String str){
  //First letter in string is opcode
  switch(str[0]){
    case '1':
      Serial.println(str);
      break;
    default:
      break;
  }
}

