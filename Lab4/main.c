#include "DIO.h"
#include "LED.h"
#include "SWITCH.h"

#define N_STATES 4

int main() {
//StateMachine
    DIO_Init();
    turnOffAll();
    turnOnAll();
    
    uint8 counter = 0;
    while(1) {
      if (READ_SWITCH0() && READ_SWITCH4()) {
      both:
        while(READ_SWITCH0() || READ_SWITCH4());
        turnOffAll();
        counter = 0;
        goto exit;
      } else if (READ_SWITCH0()) {
        while(READ_SWITCH0()) {
          if (READ_SWITCH4())
              goto both;
        };
        turnOffAll();
        if (counter == N_STATES - 1) {
          counter = 0;
        } else {
          ++counter;
        }
      } else if (READ_SWITCH4()) {
        while(READ_SWITCH4()) {
          if (READ_SWITCH0())
              goto both;
        };
        turnOffAll();
        if (counter == 0) {
          counter = N_STATES - 1;
        } else {
          --counter;
        }
      }
    exit:
      
      switch(counter) {
      case 0:
        turnOnAll();
        break;
      case 1:
        LED_ON('R');
        break;
      case 2:
        LED_ON('G');
        break;
      case 3:
        LED_ON('B');
        break;
      }
    }
}


/*
//Task1
    DIO_Init();
    turnOffAll();
    
    while(1){
      if(READ_SWITCH0() && READ_SWITCH4()){
        LED_OFF('R');
        LED_OFF('B');
        LED_ON('G');
      }
      
      else if(READ_SWITCH0()){
        LED_OFF('G');
        LED_OFF('B');
        LED_ON('R');
      }
      else if(READ_SWITCH4()){
        LED_OFF('R');
        LED_OFF('G');
        LED_ON('B');
      }
      
      else{
      turnOffAll();
      }
    }
*/

/*
//ArrayCheck
    DIO_Init();
    turnOffAll();
    
    int arr[5] = {1,2,1,1,2};
    int x = arr[1];

    while(1){
      if((x%2==1) && ( (READ_SWITCH0() ) || READ_SWITCH4()) ){
        LED_ON('R');
      }
      else if((x%2==0) && ( (READ_SWITCH0()) || READ_SWITCH4()) ){
        LED_ON('B');
      }
    }
*/

/*
//StateMachine
    DIO_Init();
    turnOffAll();
    turnOnAll();
    
    uint8 counter = 0;
    while(1) {
      if (READ_SWITCH0() && READ_SWITCH4()) {
      both:
        while(READ_SWITCH0() || READ_SWITCH4());
        turnOffAll();
        counter = 0;
        goto exit;
      } else if (READ_SWITCH0()) {
        while(READ_SWITCH0()) {
          if (READ_SWITCH4())
              goto both;
        };
        turnOffAll();
        if (counter == N_STATES - 1) {
          counter = 0;
        } else {
          ++counter;
        }
      } else if (READ_SWITCH4()) {
        while(READ_SWITCH4()) {
          if (READ_SWITCH0())
              goto both;
        };
        turnOffAll();
        if (counter == 0) {
          counter = N_STATES - 1;
        } else {
          --counter;
        }
      }
    exit:
      
      switch(counter) {
      case 0:
        turnOnAll();
        break;
      case 1:
        LED_ON('R');
        break;
      case 2:
        LED_ON('G');
        break;
      case 3:
        LED_ON('B');
        break;
      }
    }
*/
