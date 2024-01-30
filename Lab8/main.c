#include "tm4c123gh6pm.h"
#include <stdint.h>

void Timer0A_Init(uint32_t delay);

int main(void) {
    // Enable the clock for Port F
    SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5;
    while ((SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R5) == 0) {}

    // Set Port F Pin 3 as output
    GPIO_PORTF_DIR_R |= 0x08;
    GPIO_PORTF_DEN_R |= 0x08;

    // Initialize Timer 0A with a 3-second delay
    Timer0A_Init(3000);
    GPIO_PORTF_DATA_R &= ~(0x0E);

    while (1) {
        // Your main code can continue running here
    }
}

void Timer0A_Init(uint32_t delay) {
    // Enable Timer 0A and configure it as a one-shot timer
    SYSCTL_RCGCTIMER_R |= SYSCTL_RCGCTIMER_R0;
    TIMER0_CTL_R = 0;
    TIMER0_CFG_R = TIMER_CFG_32_BIT_TIMER;
    TIMER0_TAMR_R = TIMER_TAMR_TAMR_1_SHOT;

    // Calculate the load value for the specified delay in milliseconds
    uint32_t loadValue = (delay * 16000) - 1;
    TIMER0_TAILR_R = loadValue;

    // Enable Timer 0A interrupt
    TIMER0_IMR_R |= TIMER_IMR_TATOIM;

//    // Set the interrupt priority (adjust as needed)
//    NVIC_PRI4_R = (NVIC_PRI4_R & 0xFFFFFF00) | 0x00000020;
//
    // Enable Timer 0A interrupt in NVIC
    NVIC_EN0_R |= 1 << (INT_TIMER0A - 16);

    // Start the timer
    TIMER0_CTL_R |= TIMER_CTL_TAEN;
}

// Timer 0A interrupt service routine
void Timer0A_Handler(void) {
    // Clear the interrupt flag
    TIMER0_ICR_R = TIMER_ICR_TATOCINT;

    // Turn on the green LED (Port F, Pin 3)
    GPIO_PORTF_DATA_R |= 0x08;
}
