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
void oled_print(char *cstr);

void oled_sram_init();
void oled_sram_write(int start, int page, int column, uint8_t value); //Write int to specific position
void oled_sram_flush(int start);
void oled_sram_write_string(int start, char *cstr, int page);
void oled_sram_write_char(int start, char *c, int page, int col);
void oled_sram_clear_line(int start, int page);
void oled_sram_clear_screen(int start);
void oled_sram_write_line(int x0, int y0, int x1, int y1);
void oled_sram_write_bit(int start, int x, int y);



#endif /* OLED_DRIVER_H_ */