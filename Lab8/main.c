#include "SYSTICK.h"
#include "DIO.h"

#define RED_LED_PIN  (1 << 1)  // Assuming the red LED is connected to GPIO Port F, pin 1

volatile int counter = 0;

void SysTick_Handler(void){
  counter++;
}

int main(void) {
    DIO_Init();
    SysTickDisable();
    SysTickPeriodSet(500);
    SysTickEnable();
    SysTickInterruptEnable();    
    while (1) {
      if(counter == 5){
          counter = 0;
          GPIO_PORTF_DATA_R ^= RED_LED_PIN;
      }
    }
}
