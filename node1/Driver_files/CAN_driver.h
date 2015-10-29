/*
 * CAN_driver.h
 *
 * Created: 24.09.2015 11:24:40
 *  Author: andreabm
 */ 


#ifndef CAN_DRIVER_H_
#define CAN_DRIVER_H_


typedef struct{
	uint8_t id;
	uint8_t length;
	uint8_t data[8];
} Message;

int CAN_init();

void CAN_transmit(Message *m);

int CAN_receive(Message *m);



#endif /* CAN_DRIVER_H_ */