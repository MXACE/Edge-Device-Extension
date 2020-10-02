#include "main.h"
#include <string.h>
#include "COM.h"
#include <stdio.h>

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart6;

void COM_TX(char string[])
{
	HAL_UART_Transmit(&huart6, (uint8_t *)string, strlen(string), 2000);
}	
void RS_TX(char string[])
{
	HAL_UART_Transmit(&huart1, (uint8_t *)string, strlen(string), 1000);
}
