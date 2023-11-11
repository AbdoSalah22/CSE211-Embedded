#include "DIO.h"
#include "LED.h"

void LED_ON(uint8 COLOR){
  switch (COLOR){
    case 'R':
    DIO_WritePin(PORTF,1,1);
    break;
    case 'B':
    DIO_WritePin(PORTF,2,1);
    break;
    case 'G':
    DIO_WritePin(PORTF,3,1);
    break;
    case 'W':
    DIO_WritePin(PORTF,1,1);
    DIO_WritePin(PORTF,2,1);
    DIO_WritePin(PORTF,3,1);
    break;
  }
}

void LED_OFF(uint8 COLOR){
  switch (COLOR){
    case 'R':
    DIO_WritePin(PORTF,1,0);
    break;
    case 'B':
    DIO_WritePin(PORTF,2,0);
    break;
    case 'G':
    DIO_WritePin(PORTF,3,0);
    break;
    case 'W':
    DIO_WritePin(PORTF,1,0);
    DIO_WritePin(PORTF,2,0);
    DIO_WritePin(PORTF,3,0);
    break;
  default:
    break;
  }
}

void turnOffAll(){
  DIO_WritePort(PORTF, 0x00);
}

void turnOnAll(){
  DIO_WritePin(PORTF,1,1);
  DIO_WritePin(PORTF,2,1);
  DIO_WritePin(PORTF,3,1);
}


