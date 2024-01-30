#include "SYSTICK.h"
#include "DIO.h"

#define RED_LED_PIN  (1 << 1)  // Assuming the red LED is connected to GPIO Port F, pin 1

void SYSTICK_Delay(uint32 ms) {
    SysTickDisable();
    SysTickPeriodSet(ms);
    SysTickEnable();
    while (!SysTick_Is_Time_out()) {}
}

int main(void) {
    DIO_Init();

    while (1) {
        // Toggle the red LED every 5000 milliseconds
        GPIO_PORTF_DATA_R ^= RED_LED_PIN;
        
        for(int i=0; i<5; i++){
          SYSTICK_Delay(1000);
        }
    }
}
