#ifndef LCD_H
#define LCD_H


void lcd_init(void);
void lcd_command(unsigned char command);
void lcd_data(unsigned char data);
void lcd_data_string(const char* string);

#endif // LCD_H
