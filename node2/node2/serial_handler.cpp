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
#include "message_handler.h"

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
  //Serial.println(str);
  switch(str[0]){
    case '1':
      parse_command(str, command);
      update_web(50, command[0], command[1]*100);
      break;
    case '2':
      parse_command(str, command);
      request_highscore(command[0]); //Get highscore from node1 through CAN
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

void pass_highscore_to_web(uint8_t place, char initial_1, char initial_2, char initial_3, uint8_t score){
  printf("2,%i,%c%c%c,%i\n",place,initial_1,initial_2,initial_3, score); //Send score to website through serial port 
}


