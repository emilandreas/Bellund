/*
 * oled_driver.h
 *
 * Created: 10.09.2015 12:56:02
 *  Author: andreabm
 */ 


#ifndef OLED_DRIVER_H_
#define OLED_DRIVER_H_


void write_data(uint8_t data);
void write_command(uint8_t command);
void oled_init();
void oled_home();
void oled_goto_line(uint8_t line);
void oled_clear_line(uint8_t line);
void oled_clear_screen();
void oled_pos(uint8_t row,uint8_t column);
void oled_print(char* c);



#endif /* OLED_DRIVER_H_ */