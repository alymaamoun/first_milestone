#include "ConfigMain.c"
void Distance_Check(double distance){
if(distance>=100.0){
    GPIO_PORTF_DATA_R=0X02;
}
else
    GPIO_PORTF_DATA_R=0X00;
}