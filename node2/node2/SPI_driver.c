/*
 * SPI_driver.c
 *
 * Created: 24.09.2015 09:34:13
 *  Author: andreabm
 */ 
#include <avr/io.h>
#include <arduino.h>
#include <util/delay.h>

#define MOSI  PB2
#define MISO  PB3
#define SCK   PB1
#define SS    PB0

void SPI_init(){
  //Datadir: MOSI (== PB5) out, SCK (== PB7) out, !SS (== PB4) out
  DDRB = (1<<MOSI)|(1<<SCK)|(1<<SS);
  //Enable SPI and Master, and set clock rate to fck/64
  SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR1);
}
uint8_t SPI_transmit(uint8_t data){
  // start transmission
  SPDR = data;
  //Wait for data to be ent and receved
  while(!(SPSR & (1<<SPIF)));
  //Return answer
  return SPDR;
}

void SPI_send(uint8_t c){
  SPI_transmit(c);
}

uint8_t SPI_receive(){
  return SPI_transmit(0b11001100);
}

void SPI_ss_high(){
  //digitalWrite(19, HIGH);
  PORTB |= (1<<SS);
}

void SPI_ss_low(){
  //digitalWrite(19, LOW);
  PORTB &= ~(1<<SS);
}

