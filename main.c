void LCD_Command(char com)
{
    GPIO_PORTA_DATA_R = 0;
    GPIO_PORTB_DATA_R = com;
    GPIO_PORTA_DATA_R |= 0x80;
    microDelay(1);
    GPIO_PORTA_DATA_R = 0;
}

void LCD_Data(char data)
{
    GPIO_PORTA_DATA_R = 0x20;
    GPIO_PORTB_DATA_R=data;
    GPIO_PORTA_DATA_R |= 0x80;
    microDelay(1);
    GPIO_PORTA_DATA_R = 0;
}
