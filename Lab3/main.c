#include "DIO.h"
#define DELAY   2000000

void delay(void){
  volatile unsigned long i;
  for(i = 0; i < DELAY ; i++){}
}

int main() {
    DIO_Init();
    DIO_WritePort(PORTF, 0x0000);

    while(1){
      DIO_WritePin(PORTF, 1, 1);
      delay();
      DIO_WritePin(PORTF, 1, 0);
      DIO_WritePin(PORTF, 2, 1);
      delay();
      DIO_WritePin(PORTF, 2, 0);
      DIO_WritePin(PORTF, 3, 1);
      delay();
      DIO_WritePin(PORTF, 3, 0);
    }
}
