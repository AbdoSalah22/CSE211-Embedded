#ifndef DIO_H
#define DIO_H

#include "tm4c123gh6pm.h"
#include "bitwise_operation.h"
#include "types.h"

#define PORTF (&GPIO_PORTF_DATA_R)

void DIO_Init(void);
void DIO_WritePin(vuint32_ptr PORT, uint8 PIN, uint8 VALUE);
void DIO_WritePort(vuint32_ptr PORT, uint32 DATA);
uint8 DIO_ReadPin(vuint32_ptr PORT, uint8 PIN);
uint32 DIO_ReadPort(vuint32_ptr PORT);


#endif /* DIO_H */
