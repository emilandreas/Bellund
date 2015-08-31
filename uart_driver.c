/*
 * uart_driver.c
 *
 * Created: 27.08.2015 12:08:48
 *  Author: Administrator
 */ 
#define F_CPU 4915200

#include <avr/io.h>
#include <stdio.h>
#include "uart_driver.h"

int uartInit(unsigned int baud){
	//Calculate ubrr value
	unsigned int ubrr = F_CPU / 16 / baud - 1;
	
	//Set baud rate
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char) ubrr;

	//Enable receiver and transmitter
	UCSR0B |= (1<<RXEN0)|(1<<TXEN0);
	
	// 8data, 2stop
	UCSR0C |= (1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00);
	
	//Enable printf for uart
	fdevopen(&uartSend, NULL);
	
	return 0;
}
int uartSend(char c){
	//Wait for empty buffer
	while( !( UCSR0A & (1<<UDRE0)) );
	
	//Put data into buffer and send it
	UDR0 = c;
	
	return 0;
}

char uartReceive(){
	//Wait for data
	while(!(UCSR0A & (1 << RXC0)));
	
	//Return data
	return UDR0;
}