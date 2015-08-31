/*
 * uart_driver.h
 *
 * Created: 27.08.2015 12:09:15
 *  Author: Administrator
 */ 


#ifndef UART_DRIVER_H_
#define UART_DRIVER_H_


int uartInit(unsigned int baud);
int uartSend(char c);
char uartReceive();




#endif /* UART_DRIVER_H_ */