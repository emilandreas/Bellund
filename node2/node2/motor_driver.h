/*
 * SPI_driver.h
 *
 * Created: 24.09.2015 09:34:27
 *  Author: andreabm
 */ 


#ifndef MOTOR_DRIVER_H_
#define MOTOR_DRIVER_H_

void motor_init();
int read_encoder();
void reset_encoder();
void controll_motor(int val);

#endif /* MOTOR_DRIVER_H_ */
