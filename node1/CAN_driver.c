/*
 * CAN_driver.c
 *
 * Created: 24.09.2015 11:24:29
 *  Author: andreabm
 */ 
#include <avr/io.h>
#include <stdio.h>
#include "CAN_driver.h"
#include "MCP_driver.h"
#include "MCP2515.h"

int CAN_init(){
	MCP_init();
	//Enter config mode
	MCP_reset();
	//set loopback mode on CANCTRL
	MCP_bit_modify(MCP_CANCTRL, MODE_MASK, MODE_NORMAL);
	//Enable receve interrupt
	MCP_bit_modify(MCP_CANINTE, MCP_RX_INT, 0xFF);
	uint8_t value = MCP_read(MCP_CANSTAT);
	if ((value & MODE_MASK) != MODE_NORMAL){
		printf("System not in normal mode. Abandon ship.");
		return 1;
	}
	return 0;
}

void CAN_transmit(Message *m){
	//Write id to register
	MCP_write(MCP_TXB0SIDL,m->id);
	//Write length to register
	MCP_write(MCP_TXB0DLC, m->length);
	//Write data to register
	for (uint8_t i = 0; i < m->length; i++){
		MCP_write(MCP_TXB0D0 + i, m->data[i]);
	}
	
	//Send SPI RTS
	MCP_rts(0);
	
	//set !TXnRTS low of transmit register
}

int CAN_receive(Message *m){
	//IF interrupt flag high
	if (MCP_read(MCP_CANINTF) & MCP_RX0IF){
		m->length = MCP_read(MCP_RBB0DLC);
		for(uint8_t i = 0; i < m->length; i++){
			m->data[i] = MCP_read(MCP_RXB0D0 + i);
		}
		//Set intrupt flag low to indicate that message is read
		MCP_bit_modify(MCP_CANINTF, MCP_RX0IF, 0);
		return 0;
	}
	return 1;
}