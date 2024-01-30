//#include "SYSTICK.h"
//
////#define NVIC_ST_CTRL_COUNT      0x00010000  // Count Flag
////#define NVIC_ST_CTRL_CLK_SRC    0x00000004  // Clock Source
////#define NVIC_ST_CTRL_INTEN      0x00000002  // Interrupt Enable
////#define NVIC_ST_CTRL_ENABLE     0x00000001  // Enable
//
//
//inline void SysTickDisable(void) {
//    NVIC_ST_CTRL_R &= ~(NVIC_ST_CTRL_ENABLE);  // Clear the ENABLE bit to disable SysTick
//}
//
//inline void SysTickEnable(void) {
//    NVIC_ST_CTRL_R |= NVIC_ST_CTRL_ENABLE;   // Set the ENABLE bit to enable SysTick
//    NVIC_ST_CTRL_R |= NVIC_ST_CTRL_CLK_SRC;
//}
//
//void SysTickInterruptDisable(void) {
//    NVIC_ST_CTRL_R &= ~(NVIC_ST_CTRL_INTEN);   // Set the ENABLE bit to enable SysTick
//}
//
//void SysTickInterruptEnable(void) {
//    NVIC_ST_CTRL_R |= (NVIC_ST_CTRL_INTEN);   // Set the interrupt ENABLE bit to enable SysTick
//}
//
//uint32 SysTickPeriodGet(void) {
//    return NVIC_ST_RELOAD_R;
//}
//
//void SysTickPeriodSet(uint32 msDelay) {
//    NVIC_ST_RELOAD_R = msDelay * (uint32)(FREQUENCY/1000) - 1;
//}
//
//
//uint32 SysTickValueGet(void) {
//    return NVIC_ST_CURRENT_R;  // Return the current value of the SysTick counter from the VAL register
//}
//
//uint8 SysTick_Is_Time_out(void) {
//    return (NVIC_ST_CTRL_R & (NVIC_ST_CTRL_COUNT)) != 0;  // Check if the COUNTFLAG is set
//}
