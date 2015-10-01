/*
 * MCP_driver.h
 *
 * Created: 24.09.2015 10:03:20
 *  Author: andreabm
 */ 


#ifndef MCP_DRIVER_H_
#define MCP_DRIVER_H_

int MCP_init(); //return 1 if not in configuration mode

void MCP_reset();
uint8_t MCP_read(uint8_t address);
void MCP_read_rx();
void MCP_write(uint8_t address, uint8_t data);
void MCP_load_tx();
void MCP_rts(uint8_t buffer);
uint8_t MCP_read_status();
uint8_t MCP_rx_status();
void MCP_bit_modify(uint8_t address, uint8_t mask, uint8_t data);

#endif /* MCP_DRIVER_H_ */