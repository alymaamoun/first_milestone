#include "stdint.h"
#include "C:\Keil\Labware\inc\tm4c123gh6pm.h"
#include "math.h"

void portF_init(){
 SYSCTL_RCGCGPIO_R |= 0x20;
while ((SYSCTL_PRGPIO_R&0x20)==0){} 
  GPIO_PORTF_LOCK_R=0x4C4F434B;
  GPIO_PORTF_CR_R |=0x0E;
  GPIO_PORTF_DIR_R |=0x0E;
  GPIO_PORTF_DEN_R |= 0x0E;
  GPIO_PORTF_AMSEL_R &= ~0x0E;
  GPIO_PORTF_AFSEL_R &= ~0x0E;
  GPIO_PORTF_PCTL_R &= ~0x0000FFF0;
  GPIO_PORTF_DATA_R &= ~0x0E;
}
void portB_init(){ //LCD I/O
  SYSCTL_RCGCGPIO_R |= 0x02;
while ((SYSCTL_PRGPIO_R&0x02)==0){} 
  GPIO_PORTB_LOCK_R |=0x4C4F434B;
  GPIO_PORTB_CR_R |=0xFF;
  GPIO_PORTB_DIR_R |=0xFF;
  GPIO_PORTB_DEN_R |=0xFF;
  GPIO_PORTB_AFSEL_R&= ~0XFF;
  GPIO_PORTB_AMSEL_R&= ~0XFF;
  GPIO_PORTB_PCTL_R &=~0xFFFFFFFF; 
}
