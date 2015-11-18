/*
 * ByggernBellLund.c
 *
 * Created: 27.08.2015 10:11:04
 *  Author: Administrator
 */ 
#define F_CPU 4915200

#include <avr/io.h>
#include <util/delay.h>
#include "Driver_files/uart_driver.h"
#include "Driver_files/bus_driver.h"
#include "Driver_files/oled_driver.h"
#include "Interface_files/menu.h"
#include "Driver_files/CAN_driver.h"
#include "Driver_files/message_handler.h"

int main(void)
{
	uartInit(9600);
	bus_init();
	oled_init();
	handler_init();
	CAN_init();
    while(1)
    {
		menuSystem();
    } 
}