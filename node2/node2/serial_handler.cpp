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
#include "controll_driver.h"

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

int command[8] = {0};
void handel_command(String str){
  //First letter in string is opcode
  switch(str[0]){
    case '1':
      parse_command(str, command);
      update_web(50, command[0], command[1]*100);
      break;
    case '2':
      break;
    default:
      break;
  }
}

void parse_command(String str, int command[]){
  int counter = 1; // Start after first comma
  String substr;
  int commandCount = 0;
  while(counter++ < str.length()){
    if (str[counter] == ',' || counter == str.length()){
      //Serial.println(substr.toInt());
      command[commandCount++] = substr.toInt();
      substr = "";
    }
    else{
      substr += str[counter];
    }
  }
}

