/*
 * EEPROM_driver.h
 *
 * Created: 26.10.2015 13.37.28
 *  Author: AndreasBell
 */ 


#ifndef EEPROM_DRIVER_H_
#define EEPROM_DRIVER_H_

uint8_t EEPROM_read(unsigned int address);
void EEPROM_write(unsigned int address, uint8_t data);



#endif /* EEPROM_DRIVER_H_ */