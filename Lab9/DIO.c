#include "DIO.h"

void DIO_Init(void) {
    //Initializing Clock
    SYSCTL_RCGCGPIO_R |= 0x20;
    
    //Wait until port is ready
    while ((SYSCTL_PRGPIO_R & 0x20) == 0);
    
    //Unlock Port
    GPIO_PORTF_LOCK_R = 0x4C4F434B;
    
    //Commit Changes
    GPIO_PORTF_CR_R |= 0x1F;
    
    //Make Pins 1,2,3 as outputs and 0,4 as inputs
    GPIO_PORTF_DIR_R |= 0x0E;
    
    //Configurign switches as Pull-Up
    GPIO_PORTF_PUR_R |= 0x11;
    
    //Enabling Pins
    GPIO_PORTF_DEN_R |= 0x1F;
}


void DIO_WritePin(vuint32_ptr PORT, uint8 PIN, uint8 VALUE) {
    if (VALUE == 1) {
        Set_Bit(*PORT, PIN);
    } else {
        Clear_Bit(*PORT, PIN);
    }
}


void DIO_WritePort(vuint32_ptr PORT, uint32 DATA ){
    *PORT = DATA;
}


uint8 DIO_ReadPin(vuint32_ptr PORT, uint8 PIN) {
  return Get_Bit(*PORT, PIN);
}


uint32 DIO_ReadPort(vuint32_ptr PORT) {
  return *PORT;
}
