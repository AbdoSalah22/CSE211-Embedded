#include "DIO.h"
#include <stdint.h>
#include "C:\ti\TivaWare_C_Series-2.2.0.295\driverlib\systick.h"

#define RED_LED_PIN  (1 << 1)  // Assuming the red LED is connected to GPIO Port F, pin 1

int main(void) {
    // Initialize your system, set up GPIO, etc.
    DIO_Init();
    //Configure the red LED pin as an output
    GPIO_PORTF_DIR_R |= 0X0E;
    GPIO_PORTF_DEN_R |= 0X0E;
    SysTickDisable();
    SysTickIntEnable();
    SysTickEnable();
    SysTickPeriodSet(8000000-1);
    __asm("CPSIE i");
 
while (1) {
        __asm("  wfi");
  }
}
 
volatile int counter =0;
void SysTickHandler(void){
  counter++;
    if (counter==5){
 
     GPIO_PORTF_DATA_R ^= 0xE;
    counter=0;
    }
}
