/*
 * IncFile1.h
 *
 * Created: 03.09.2015 15:25:28
 *  Author: andreabm
 */ 


#ifndef INCFILE1_H_
#define INCFILE1_H_


void bus_init(void){
	//Mask out 4 msb of addrBus
	SFIOR |= (1<<XMM2);
	//Enable bus
	MCUCR |= (1<<SRE);
}


#endif /* INCFILE1_H_ */