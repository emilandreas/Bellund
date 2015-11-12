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

int max_encoder_val = -15000;

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
  
  //Calibrate
  calibrate_encoder();
}

int read_encoder(){
    int val = 0;
    
    //Set !OE low to enable output of encoder
    digitalWrite(OE, LOW);
    
    //Set SEL low to get high byte
    digitalWrite(SEL, LOW);
    
    //Wait about 20 microseconds
    _delay_us(20);
    
    //Read MSB
    val |= (reverse_byte(PINK) << 8);
    
    //Set SEL high to get low byte
    digitalWrite(SEL, HIGH);

    //Wait about 20 microseconds
    _delay_us(20);
    
    //Read LSB
    val |= reverse_byte(PINK);
    
    //Set !OE high to disable output of encoder
    digitalWrite(OE, HIGH);

    _delay_us(5);

    return val;
}

void reset_encoder(){
  //Toggle !RST to reset encoder
  digitalWrite(RST, LOW);
  _delay_ms(20);
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

uint8_t reverse_byte(uint8_t b){
  uint8_t bits = sizeof(b) * 8;
  uint8_t reversed_byte = 0;
  uint8_t i, temp_bit;
  
  for (i = 0; i < bits ; i++)    {
    temp_bit = (b & (1 << i));
    if(temp_bit){
      reversed_byte |= (1 << ((bits - 1) - i));
    }
  }
  
  return reversed_byte;
}

double get_position(){
  return (double)read_encoder()/max_encoder_val*100;
}

void calibrate_encoder(){
  controll_motor(-80);   //Find left boundary
  delay(3000);
  reset_encoder();
  controll_motor(80);  //Find right boundary
  delay(3000);
  max_encoder_val = read_encoder();
  controll_motor(0);
}


