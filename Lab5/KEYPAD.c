#include "KEYPAD.h"

// Function to initialize the keypad
void keypad_init(void) {
    // Configure Port E pins 3-0 as output digital pins for rows
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R4;   // Enable clock for Port E
    while ((SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R4) == 0);
    GPIO_PORTE_CR_R |= 0x0F;
    GPIO_PORTE_DIR_R |= 0x0F;                 // Set rows as output
    GPIO_PORTE_ODR_R |= 0x0F;                 // Enable open drain for rows
    GPIO_PORTE_DEN_R |= 0x0F;                 // Enable digital function for rows

    // Configure Port C pins 7-4 as input digital pins with pull-down resistors
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R2;   // Enable clock for Port C
    while ((SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R2) == 0);
    GPIO_PORTC_CR_R |= 0xF0;
    GPIO_PORTC_DIR_R &= ~0xF0;                // Set columns as input
    GPIO_PORTC_PUR_R |= 0xF0;                 // Enable pull-down resistors for columns
    GPIO_PORTC_DEN_R |= 0xF0;                 // Enable digital function for columns
}

uint8 keypad_readkey(void) {
    const unsigned char keymap[4][4] = {
        {'1', '2', '3', '+'},
        {'4', '5', '6', '-'},
        {'7', '8', '9', '*'},
        {0, '0', '=', '/'}
    };
    
    int row, col;

    // Check to see if any key is pressed
    GPIO_PORTE_DATA_R = 0; 
    col = GPIO_PORTC_DATA_R & 0xF0; 
    if (col == 0xF0) return 0; 

    // If a key is pressed, find out which key
    while (1) {
        row = 0;
        GPIO_PORTE_DATA_R = 0x0E; 
        delayUs(2);
        col = GPIO_PORTC_DATA_R & 0xF0;
        if (col != 0xF0) break;

        row = 1;
        GPIO_PORTE_DATA_R = 0x0D; 
        delayUs(2);
        col = GPIO_PORTC_DATA_R & 0xF0;
        if (col != 0xF0) break;

        row = 2;
        GPIO_PORTE_DATA_R = 0x0B; 
        delayUs(2);
        col = GPIO_PORTC_DATA_R & 0xF0;
        if (col != 0xF0) break;

        row = 3;
        GPIO_PORTE_DATA_R = 0x07; 
        delayUs(2);
        col = GPIO_PORTC_DATA_R & 0xF0;
        if (col != 0xF0) break;

        return 0; 
    }

    // Gets here when one of the rows has a key pressed
    if (col == 0xE0) return keymap[row][0]; 
    if (col == 0xD0) return keymap[row][1]; 
    if (col == 0xB0) return keymap[row][2]; 
    if (col == 0x70) return keymap[row][3]; 

    return 0; 
}
