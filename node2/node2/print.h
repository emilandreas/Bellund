/*
 * print.h
 *
 * Created: 01.10.2015 14:26:18
 *  Author: andreabm
 */ 


#ifndef PRINT_H_
#define PRINT_H_

// we need fundamental FILE definitions and printf declarations
#include <stdio.h>

// create a FILE structure to reference our UART output function

static FILE uartout = {0} ;

// create a output function
// This works because Serial.write, although of
// type virtual, already exists.
static int uart_putchar (char c, FILE *stream)
{
	Serial.write(c) ;
	return 0 ;
}

void uart_setup(void)
{
	// Start the UART
	Serial.begin(9600) ;

	// fill in the UART file descriptor with pointer to writer.
	fdev_setup_stream (&uartout, uart_putchar, NULL, _FDEV_SETUP_WRITE);

	// The uart is the standard output device STDOUT.
	stdout = &uartout ;
}



#endif /* PRINT_H_ */
