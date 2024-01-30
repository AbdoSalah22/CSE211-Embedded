#include "tm4c123gh6pm.h"
#include "bitwise_operation.h"

void delayMs (int n);
void delayUs(int n);
void LCD_COMMAND(unsigned char command);
void LCD_DATA(unsigned char data);
void LCD_INIT(void);


int main(){
    LCD_INIT();

    LCD_DATA('H');
    LCD_DATA('E');
    LCD_DATA('L');
    LCD_DATA('L');
    LCD_DATA('O');
    LCD_DATA('H');
    LCD_DATA('E');
    LCD_DATA('L');
    LCD_DATA('L');
    LCD_DATA('O');
}


void LCD_INIT(){

    SYSCTL_RCGCGPIO_R|=0x01; //enable clock for GPIOA
    SYSCTL_RCGCGPIO_R|=0x02; //enable clock for GPIOB
    
    GPIO_PORTA_DIR_R|=0xE0;  //setting pins 5,6,7 to output pins
    GPIO_PORTA_DEN_R|=0xE0; //setting pins 5,6,7 to be digital pins
    
    GPIO_PORTB_DIR_R=0xFF;  //setting pins 0-7 to output pins
    GPIO_PORTB_DEN_R=0xFF;  //setting pins 0-7 to be digital pins
    
    //Initialization sequence for initializing the lcd (waking up and start initialize)
    delayMs(20);
    LCD_COMMAND(0x30);
    delayMs(5);
    LCD_COMMAND(0x30);
    delayUs(100);
    LCD_COMMAND(0x30);
      
    LCD_COMMAND(0x38);      /* set 8-bit data, 2-line, 5x7 font */
    LCD_COMMAND(0x06);      /* move cursor right */
    LCD_COMMAND(0x01);      /* clear screen, move cursor to home */
    LCD_COMMAND(0x0F);      /* turn on display, cursor blinking */

}

void LCD_COMMAND(unsigned char command){

  GPIO_PORTA_DATA_R=0;        /*setting all 7 bits of port A with 0 including RS(setting RS to zero to enable command register) and E and R/W */
  GPIO_PORTB_DATA_R=command;
  GPIO_PORTA_DATA_R=0x80;    /*setting the enable pin (pin 7) to 1 and other pins to zero */
  delayUs(0);
  GPIO_PORTA_DATA_R=0;   
 
  if (command<4){
    delayMs(2);             /* since the first 2 commands (1&2) takes 1.64ms to execute, therefore we delay the tiva for the required time*/
  }
  else{
    delayUs(40);          /*all other commands executes in 40us */
  }
  
}


void LCD_DATA(unsigned char data){
  GPIO_PORTA_DATA_R=0x20; /*setting pin 5 to 1 which is the RS pin (to enable the data register)*/
  GPIO_PORTB_DATA_R=data;
  GPIO_PORTA_DATA_R|=0x80;   
  delayUs(0);
  GPIO_PORTA_DATA_R=0;    
  delayUs(40);
}

