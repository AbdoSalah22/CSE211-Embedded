# include "DIO.h"

uint8 READ_SWITCH0(){
  return DIO_ReadPin(PORTF,0) ? 0 : 1;
}

uint8 READ_SWITCH4(){
  return DIO_ReadPin(PORTF,4) ? 0 : 1;
}