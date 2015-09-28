/*
 * SPI_driver.h
 *
 * Created: 24.09.2015 09:34:27
 *  Author: andreabm
 */ 


#ifndef SPI_DRIVER_H_
#define SPI_DRIVER_H_

void SPI_init();
uint8_t SPI_transmit(uint8_t data);
void SPI_send(uint8_t c);
uint8_t SPI_receive();

void SPI_ss_high();
void SPI_ss_low();




#endif /* SPI_DRIVER_H_ */