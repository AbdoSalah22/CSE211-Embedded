#include "KEYPAD.h"

/* delay n milliseconds (16 MHz CPU clock) */
//void delayMs(int n)
//{
//    int i, j;
//    for(i = 0 ; i < n; i++)
//        for (j = 0; j < 3180; j++)
//            {}                          /* do nothing for 1 ms */
//}
//
/*delay n microseconds (16 MHZ CPU clock) */
//void delayUs(int n){
//  int i, j;
//  for(i =0;i<n; i++)
//  for(j =0;j<3; j++)
//  {} /* do nothing for 1us */
//}

// Function to initialize the keypad
void KeyPad_Init(void) {
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
    GPIO_PORTC_CR_R = 0xF0;
    GPIO_PORTC_DIR_R &= ~0xF0;                // Set columns as input
    GPIO_PORTC_PUR_R |= 0xF0;                 // Enable pull-down resistors for columns
    GPIO_PORTC_DEN_R |= 0xF0;                 // Enable digital function for columns
}


//uint8 readVal;
uint8 KeyPad_ReadKey(void){
const unsigned char keymap[4][4] = {
{ '1', '2', '3', '+'},
{ '4', '5', '6', '-'},
{ '7', '8', '9', '*'},
{ 0, '0', '=', '/'},
};
int row, col;
/* check to see any key pressed first */
GPIO_PORTE_DATA_R = 0; /* enable all rows */
col = GPIO_PORTC_DATA_R & 0xF0; /* read all columns */
if (col == 0xF0) return 0; /* no key pressed */
/* If a key is pressed, it gets here to find out which key. */
/* Although it is written as an infinite loop, it will take one of the breaks or
return in one pass.*/
while (1)
{
row = 0;
GPIO_PORTE_DATA_R = 0x0E; /* enable row 0 */
delayUs(2); /* wait for signal to settle */
col = GPIO_PORTC_DATA_R & 0xF0;
if (col != 0xF0) break;

row = 1;
GPIO_PORTE_DATA_R = 0x0D; /* enable row 1 */
delayUs(2); /* wait for signal to settle */
col = GPIO_PORTC_DATA_R & 0xF0;
if (col != 0xF0) break;

row = 2;
GPIO_PORTE_DATA_R = 0x0B; /* enable row 2 */
delayUs(2); /* wait for signal to settle */
col = GPIO_PORTC_DATA_R & 0xF0;
if (col != 0xF0) break;

row = 3;
GPIO_PORTE_DATA_R = 0x07; /* enable row 3 */
delayUs(2); /* wait for signal to settle */
col = GPIO_PORTC_DATA_R & 0xF0;
if (col != 0xF0) break;

return 0; /* if no key is pressed */
}
/* gets here when one of the rows has key pressed */
if (col == 0xE0) return keymap[row][0]; /* key in column 0 */
if (col == 0xD0) return keymap[row][1]; /* key in column 1 */
if (col == 0xB0) return keymap[row][2]; /* key in column 2 */
if (col == 0x70) return keymap[row][3]; /* key in column 3 */
return 0; /* just to be safe */
}


    /*for (int row = 0; row < 4; ++row) {
        GPIO_PORTE_DATA_R = (1U << row);
            for (int col = 4; col < 8; col++){
                readVal = DIO_ReadPin(&GPIO_PORTC_DATA_R, col); 
                  if(readVal == 1){
                    while(readVal == 1){
                    readVal = DIO_ReadPin(&GPIO_PORTC_DATA_R, col);
                    }
                    readVal = keyMap[row][col-4];
                    DIO_WritePin(&GPIO_PORTE_DATA_R, row, 0);
                    return readVal;
                  }
              }
            DIO_WritePin(&GPIO_PORTE_DATA_R, row, 0);
        }
    return '!';
*/
  
