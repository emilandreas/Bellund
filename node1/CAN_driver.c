/*
 * CAN_driver.c
 *
 * Created: 24.09.2015 11:24:29
 *  Author: andreabm
 */ 
#include <avr/io.h>
#include "CAN_driver.h"
#include "MCP_driver.h"
#include "MCP2515.h"

void CAN_init(){
	MCP_init();
	//Enter config mode
	MCP_reset();
	//set loopback mode on CANCTRL
	MCP_write(MCP_CANCTRL, 0b01000000);
}

void CAN_transmit(Message *m){
	//Write id to register
	MCP_write(MCP_TXB0SIDL,m->id);
	//Write length to register
	MCP_write(MCP_TXB0DLC, m->length);
	//Write data to register
	for (int i = 0; i < m->length; i++){
		MCP_write(MCP_TXB0D0, m->data[i]);
	}
	
	//Send SPI RTS
	MCP_rts(0);
	
	//set !TXnRTS low of transmit register
}

void CAN_receive(Message *m){
	m->length = MCP_read(MCP_RBB0DLC);
	for(int i = 0; i < m->length; i++){
		m->data[i] = MCP_read(MCP_RXB0D0 + i);
	}
}