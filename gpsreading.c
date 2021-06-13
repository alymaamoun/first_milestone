#include "stdint.h"
#include "C:/Keil/EE319Kware/inc/tm4c123gh6pm.h"
#include "math.h"
#include "stdio.h"
#include "string.h"

void SystemInit(){}
void init(){
    SYSCTL_RCGCGPIO_R|=SYSCTL_RCGCGPIO_R3;
   SYSCTL_RCGCUART_R|= SYSCTL_RCGCUART_R2;
//port D initialization to initialize UART2
       GPIO_PORTD_LOCK_R=0x4C4F434B;
       GPIO_PORTD_CR_R|=0xC0;
       GPIO_PORTD_AFSEL_R|=0xC0;
       GPIO_PORTD_PCTL_R=0x11000000;
       GPIO_PORTD_DEN_R|=0xC0;
       GPIO_PORTD_AMSEL_R&=~0xC0;
//UART2 initialization for GPS
       UART2_CTL_R &= ~UART_CTL_UARTEN;
       UART2_FBRD_R=11;
       UART2_IBRD_R=104;
       UART2_CC_R = UART_CC_CS_SYSCLK;
       UART2_LCRH_R=(UART_LCRH_WLEN_8|UART_LCRH_FEN);
       UART2_CTL_R|=(UART_CTL_UARTEN | UART_CTL_RXE|UART_CTL_TXE);
//UART1 initialization to send data to computer to read ir



//Checking the availablity of GPS and reading it by char
void GPS_Read(){
	int i,j;
    while((UART2_FR_R &0x10) !=0);
    data= (UART2_DR_R&0xFF);
	
	for(i=0;i<17;i++){
		for(j=0;array_Data[i][j]!='\0';j++){
			array_Data[i]=(UART2_DR_R&0xFF);
}
	}

//sending data to computer
