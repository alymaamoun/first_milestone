#include "stdint.h"
#include "C:/Keil/Labware/inc/tm4c123gh6pm.h"
#include "math.h"
#include "stdlib.h"
#include "stdio.h"
#include "stdint.h"
#include "string.h"
#define gpsinnput "$GPGLL,3004.29195,N,03121.03497,E,183127.00,A,A*6E"
#define earthRadius 6,371e3;//define earth radius for use in calculating distance
#define degToRadian (3.1415926536 / 180)

void SystemInit(){}

void init(){

     //clock initialization
      SYSCTL_RCGCGPIO_R |=0x2B;
      while((SYSCTL_PRGPIO_R&0x2B)==0){};

      //port f initialization
      GPIO_PORTF_LOCK_R = 0x4C4F434B;
      GPIO_PORTF_CR_R=0x1F;
      GPIO_PORTF_PUR_R=0X11;
      GPIO_PORTF_DIR_R=0X0E;
      GPIO_PORTF_DEN_R=0X1F;

      //port a initialization

      GPIO_PORTA_LOCK_R |=0x4C4F434B;
      GPIO_PORTA_CR_R |=0xE0;
      GPIO_PORTA_DIR_R |=0xE0;
      GPIO_PORTA_DEN_R |=0xE0;
      GPIO_PORTA_AFSEL_R&= ~0XE0;
      GPIO_PORTA_AMSEL_R&= ~0XE0;
      GPIO_PORTA_PCTL_R &=~0xFFF00000;

      //port B initialization

      GPIO_PORTB_LOCK_R |=0x4C4F434B;
      GPIO_PORTB_CR_R |=0xFF;
      GPIO_PORTB_DIR_R |=0xFF;
      GPIO_PORTB_DEN_R |=0xFF;
      GPIO_PORTB_AFSEL_R&= ~0XFF;
      GPIO_PORTB_AMSEL_R&= ~0XFF;
      GPIO_PORTB_PCTL_R &=~0xFFFFFFFF;

      //uart init on port D
        SYSCTL_RCGCUART_R |= 0x04;
        GPIO_PORTD_DEN_R |=0xC0;
        GPIO_PORTD_AFSEL_R |=0XC0;
        GPIO_PORTD_PCTL_R |=0x11000000;
        GPIO_PORTD_AMSEL_R&= ~0XC0;

        UART2_CTL_R &= ~UART_CTL_UARTEN;
              UART2_FBRD_R=11;
              UART2_IBRD_R=104;
              UART2_CC_R = UART_CC_CS_SYSCLK;
              UART2_LCRH_R=(UART_LCRH_WLEN_8|UART_LCRH_FEN);
              UART2_CTL_R|=(UART_CTL_UARTEN | UART_CTL_RXE|UART_CTL_TXE);

              SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R0;
                  SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R0;
    }

char *protocolValues[];
     const char comma[2] = ",";
     float UTC_Time;
     float currentLongitude=0;
     float currentAltitude=0;
     float currentLatitude=0;
     int distancePath;
     int distanceSaved;
     float newLatitude;
     float newLongitude;
     float newAltitude;
     char array_Data[18][1000];
     char data='0';
     int distance;



void GPS_Read(){
    int i,j;
    //cleaning the array before using
    for(i=0;i<17;i++){
        for(j=0;j<999;j++){
            array_Data[i][j]='0';
        }
    }
    /*while((UART2_FR_R &0x10) !=0);
    data= (UART2_DR_R&0xFF);*/

    for(i=0;i<17;i++){
        for(j=0;array_Data[i][j]!='\0';j++){
            while((UART2_FR_R &0x10) !=0);
            array_Data[i][j]=(UART2_DR_R&0xFF);
}
    }

}


void parse(){
    int i;
    for(i=0;array_Data[i]!='\0';i++){

        int counter=i;
        if(array_Data[i][counter]=='$'){
            counter++;
            if(array_Data[i][counter]=='G'){
                counter++;

                if(array_Data[i][counter]=='P'){
                    counter++;

                    if(array_Data[i][counter]=='R'){
                        counter++;

                        if(array_Data[i][counter]=='M'){
                            counter++;
                            if(array_Data[i][counter]=='C'){
                                counter+=2;
                                int index = 0;
                                char *token=strtok(array_Data[i],comma);
                                while( token != NULL ) {
                                    strcpy(protocolValues[index], token);
                                    token = strtok(NULL,comma);
                                    index++;
                               }
                                }
                            }
                        }
                    }
                }
            }
        }
    }



float Coordinate_Adjustment(int index){
    float dummyCo;
    int integer;
    int floatpart;
    dummyCo=atof(protocolValues[index]);
    integer=dummyCo/100;
    floatpart=dummyCo-(float)integer*100;
    floatpart=floatpart/60;
    return (float)integer+floatpart;
}



void location_initlialize(){
    float dummyLat;
    int integer;
    int floatpart;
    dummyLat=atof(protocolValues[2]);
    integer=dummyLat/100;
    floatpart=dummyLat-(float)integer*100;
    floatpart=floatpart/60;
    currentLatitude=(float)integer+floatpart;

    float dummyLong;;
    dummyLong=atof(protocolValues[4]);
    integer=dummyLong/100;
    floatpart=dummyLong-(float)integer*100;
    floatpart=floatpart/60;
    currentLongitude=(float)integer+floatpart;

}


void addDistance(){

    newLatitude=Coordinate_Adjustment(2);
    newLongitude=Coordinate_Adjustment(4);
    float deltaLongitude=newLongitude-currentLongitude;
    //float deltaAltitude=newAltitude-currentAltitude;
    float deltaLatitude=newLatitude-currentLatitude;

    //using the haversine method to calculate distance b/w two points on earth

    float a= powf(sin(deltaLatitude*degToRadian/2),2)+cos(currentLatitude*degToRadian)*cos(newLatitude*degToRadian)*pow(sin(deltaLongitude*degToRadian/2),2);

    float b=2*atan2(sqrt(a),sqrt(1-a));

    distance=distance+b*earthRadius;



    //set the current co-ordinates to the new co-ordinates
    currentLongitude = newLongitude;
    //currentAltitude=newAltitude;
    currentLatitude=newLatitude;

}



void checkDistance(){
    if(distance>100){
       GPIO_PORTF_DATA_R=0x0E;
    }
}



void microDelay (int n)
    {int c, d;
       for (c = 1; c <= n; c++) {
           for (d = 1; d <= 3180; d++){
                 }
             }
    }

void milliDelay (int n)
    {int c, d;
       for (c = 1; c <= n; c++) {
           for (d = 1; d <= 3; d++){
                 }
             }
    }

void LCD_Command(char com)
{
    GPIO_PORTA_DATA_R = 0;
    GPIO_PORTB_DATA_R = com;
    GPIO_PORTA_DATA_R |= 0x80;
    microDelay(1);
    GPIO_PORTA_DATA_R = 0;
}

int i;
void LCD_Data(char data)
{
    GPIO_PORTA_DATA_R = 0x20;
    GPIO_PORTB_DATA_R=data;
    GPIO_PORTA_DATA_R |= 0x80;
    microDelay(1);
    GPIO_PORTA_DATA_R = 0;
}
void lcdInit(void)
{
    LCD_Command(0x01);
    microDelay(50);
    LCD_Command (0x38);  //work on 8 bits lcd
    microDelay(50);
    LCD_Command (0x0F);  //display on, cursor on
    microDelay(50);
    LCD_Command (0x06);  //wakeup
    microDelay(50);
    LCD_Command (0x01);  //clear display screen
    milliDelay(5);  //shifting cursor to the right
}





int main(){
    init();
    lcdInit();

    while(1){
        GPS_Read();
        parse();
        if(GPIO_PORTF_DATA_R&&0x01){
        location_initlialize();
        }
    addDistance();
    checkDistance();

        LCD_Data(distance);
      }

    }
