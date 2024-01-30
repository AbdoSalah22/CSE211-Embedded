#include "tm4c123gh6pm.h"
#include <stdint.h>

void UART0_Init(void);
void UART0_Transmit(char data);
char UART0_Receive(void);
void delayMs(int n);

int main(void) {
    // Enable clock to GPIOF and GPIOA and UART0
    SYSCTL_RCGCGPIO_R |= (1 << 0); // Enable clock to GPIOA
    SYSCTL_RCGCGPIO_R |= (1 << 5); // Enable clock to GPIOF
    SYSCTL_RCGCUART_R |= (1 << 0); // Enable clock to UART0
    
    // Configure UART0 pins (PA0 and PA1)
    GPIO_PORTA_AFSEL_R |= 0x03; // Enable alternate functions
    GPIO_PORTA_PCTL_R = 0x11; // UART function for PA0 and PA1
    GPIO_PORTA_DEN_R |= (1 << 0) | (1 << 1); // Enable digital I/O on PA0 and PA1
    
    // Initialize UART0
    UART0_CTL_R &= ~0x01; // Disable UART0
    UART0_IBRD_R = 104;   // Integer part of the baud rate divisor
    UART0_FBRD_R = 11;    // Fractional part of the baud rate divisor
    UART0_LCRH_R = 0x70;  // 8-bit, no parity, 1-stop bit, FIFO enable
    UART0_CTL_R = 0x301;  // Enable UART0, Tx, and Rx

    // Configure Port F Pin 1 (Red LED) as output
    GPIO_PORTF_DIR_R |= (1 << 1);
    GPIO_PORTF_DEN_R |= (1 << 1);

    while (1) {
        UART0_Transmit('U');
        delayMs(500);
    }
}

void UART0_Transmit(char data) {
    while ((UART0_FR_R & (1 << 5)) != 0); // Wait until the Tx FIFO is not full
    UART0_DR_R = data; // Send data
}

char UART0_Receive(void) {
    while ((UART0_FR_R & (1 << 4)) != 0); // Wait until the Rx FIFO is not empty
    return UART0_DR_R; // Read received data
}

void delayMs(int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < 3180; j++) {}
    }
}
