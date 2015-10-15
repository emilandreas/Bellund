/*
 * SPI_driver.c
 *
 * Created: 24.09.2015 09:34:13
 *  Author: andreabm
 */ 
#define OE  A7
#define RST A6
#define SEL A5
#define EN  A4
#define DIR A3

#include <avr/io.h>
#include <util/delay.h>
#include <arduino.h>
#include "motor_driver.h"
#include "DAC_driver.h"

void motor_init(){
  DAC_init();
  
  //Set port K as input
  DDRK = 0x00;
  pinMode(OE, OUTPUT);
  pinMode(RST, OUTPUT);
  pinMode(SEL, OUTPUT);
  pinMode(EN, OUTPUT);
  pinMode(DIR, OUTPUT);
  //Enable motor
  digitalWrite(EN, HIGH);
  //Set !OE high to disable output of encoder
  digitalWrite(OE, HIGH);
  
  //Set !RST
  reset_encoder();
}

int read_encoder(){
    int val = 0;
    
    //Set !OE low to enable output of encoder
    digitalWrite(OE, LOW);
    
    //Set SEL low to get high byte
    digitalWrite(SEL, LOW);
    
    //Wait about 20 microseconds
    _delay_us(200);
    
    //Read MSB
    val |= (PINK << 8);
    
    //Set SEL high to get low byte
    digitalWrite(SEL, HIGH);

    //Wait about 20 microseconds
    _delay_us(200);
    
    //Read LSB
    val |= (PINK);
    
    //Set !OE high to disable output of encoder
    digitalWrite(OE, HIGH);

    return val;
}

void reset_encoder(){
  //Toggle !RST to reset encoder
  digitalWrite(RST, LOW);
  digitalWrite(RST, HIGH);
}

void controll_motor(int val){
  if (val > 0){
    digitalWrite(DIR, HIGH);
  }
  else{
    digitalWrite(DIR, LOW);
  }
  DAC_send(0x00, abs(val));
}

