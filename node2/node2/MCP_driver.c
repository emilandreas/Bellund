/*
 * MCP_driver.c
 *
 * Created: 24.09.2015 10:03:42
 *  Author: andreabm
 */ 
#include <avr/io.h>
#include <stdio.h>
#include "MCP_driver.h"
#include "SPI_driver.h"
#include "MCP2515.h"

int MCP_init(){ 
  //Start SPI driver
  SPI_init();
  
  //Reset MPC to enter configuration mode
  MCP_reset();
  
  // Self-test
  uint8_t value = MCP_read(MCP_CANSTAT);
  if ((value & MODE_MASK) != MODE_CONFIG) {
    return 1;
  }
  return 0;
}

void toggle_cs(uint8_t i){
  if(i){
    SPI_ss_high();
  }
  else{
    SPI_ss_low();
  }
}

void MCP_reset(){
  toggle_cs(0); //CS low
  SPI_transmit(MCP_RESET); // sen reset command 0b11000000
  toggle_cs(1); //CS high
}

uint8_t MCP_read(uint8_t address){
  toggle_cs(0);
  SPI_send(MCP_READ); //Send read command 0b00000011
  SPI_send(address);
  uint8_t data = SPI_receive();
  toggle_cs(1);
  return data;
}


void MCP_write(uint8_t address, uint8_t data){
  toggle_cs(0);
  SPI_send(MCP_WRITE); //Send write command 0b00000010
  SPI_send(address);
  SPI_send(data);
  toggle_cs(1);
}

void MCP_load_tx(){
  return 0;
}
void MCP_rts(uint8_t buffer){
  toggle_cs(0);
  switch(buffer%4){ //Select buffer to use, 3 = all
    case 0:
      SPI_send(MCP_RTS_TX0);
      break;
    case 1:
      SPI_send(MCP_RTS_TX1);
      break;
    case 2:
      SPI_send(MCP_RTS_TX2);
      break;
    case 3:
      SPI_send(MCP_RTS_ALL);
      break;
    default:
      break;
  }
  toggle_cs(1);
}
uint8_t MCP_read_status(){
  toggle_cs(0);
  SPI_send(MCP_READ_STATUS); //send read status code: 0b10100000
  uint8_t data = SPI_receive();
  toggle_cs(1);
  return data;
}
uint8_t MCP_rx_status(){
  toggle_cs(0);
  SPI_send(MCP_RX_STATUS); // send read rx status code: 0b10110000
  uint8_t data = SPI_receive();
  toggle_cs(1);
  return data;
}
void MCP_bit_modify(uint8_t address, uint8_t mask, uint8_t data){
  toggle_cs(0);
  SPI_send(MCP_BITMOD); // send bit modify command: 0b00000101
  SPI_send(address);
  SPI_send(mask);
  SPI_send(data);
  toggle_cs(1);
}
