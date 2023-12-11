#include "LCD.h"
#include "DIO.h"


void lcd_init() {
    SYSCTL_RCGCGPIO_R |= 0x01; // enable clock for GPIOA
    SYSCTL_RCGCGPIO_R |= 0x02; // enable clock for GPIOB

    GPIO_PORTA_DIR_R |= 0xE0;  // setting pins 5, 6, 7 to output pins
    GPIO_PORTA_DEN_R |= 0xE0;  // setting pins 5, 6, 7 to be digital pins

    GPIO_PORTB_DIR_R |= 0xFF;  // setting pins 0-7 to output pins
    GPIO_PORTB_DEN_R |= 0xFF;  // setting pins 0-7 to be digital pins

    // Initialization sequence for initializing the LCD (waking up and start initialize)
    delayMs(20);
    lcd_command(0x30);
    delayMs(5);
    lcd_command(0x30);
    delayUs(100);
    lcd_command(0x30);
    delayUs(100);

    lcd_command(0x38); /* set 8-bit data, 2-line, 5x7 font */
    delayUs(100);
    lcd_command(0x06); /* move cursor right */
    delayUs(100);
    lcd_command(0x01); /* clear screen, move cursor to home */
    delayUs(100);
    lcd_command(0x0F); /* turn on display, cursor blinking */
    delayUs(100);
}

void lcd_command(unsigned char command) {
    GPIO_PORTA_DATA_R = 0;     /* setting RS, E, and R/W to zero */
    delayUs(1);
    GPIO_PORTB_DATA_R = command;
    delayUs(1);

    GPIO_PORTA_DATA_R = 0x80;  /* setting the enable pin to 1 */
    delayUs(1);
    GPIO_PORTA_DATA_R = 0;     /* setting all bits to 0 */
    delayUs(1);

    delayMs(3);
}

void lcd_data(unsigned char data) {
    GPIO_PORTA_DATA_R = 0x20;  /* setting RS to 1 and E to 0 */
    delayUs(1);
    GPIO_PORTB_DATA_R = data;
    delayUs(1);

    GPIO_PORTA_DATA_R = 0x80;  /* setting the enable pin to 1 */
    delayUs(1);
    GPIO_PORTA_DATA_R = 0;     /* setting all bits to 0 */
    delayUs(1);

    delayMs(3);
}

void lcd_data_string(const char* string) {
    while (*string != '\0') {
        lcd_data(*string);
        string++;
    }
}

