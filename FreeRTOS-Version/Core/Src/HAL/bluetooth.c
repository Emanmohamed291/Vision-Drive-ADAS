/*
 * bluetooth.c
 *
 *  Created on: Jun 8, 2024
 *      Author: workstation
 */

#include "gpio.h"
#include "HAL/bluetooth.h"

volatile uint8_t Data[1] = {0};

uint8_t BL_ReadByteSync()
{
	uint8_t temp = 0;
	HAL_StatusTypeDef status = HAL_UART_Receive(&huart1, Data, 1, 2);
	    if (status == HAL_OK) {
	        temp = Data[0];
	    }

	if(temp == 'F')
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
	}

	if(Data[0] == 'B')
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
	}

	Data[0] = 0;
	return temp;
}



/*void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef* huart, uint16_t Size){
	if (huart->Instance == USART1){
		HAL_UART_Transmit(&huart2, Data, Size, 1000);
		if(Data[0] == 'F'){
			HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
		}
		if(Data[0] == 'B'){
				HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
			}
		HAL_UARTEx_ReceiveToIdle_IT(&huart1, Data, 1);
	}
	else if (huart->Instance == USART2){
		HAL_UART_Transmit(&huart1, Data, Size, 1000);
		HAL_UARTEx_ReceiveToIdle_IT(&huart2, Data, 1);
	}
	HAL_UARTEx_ReceiveToIdle_IT(huart, Data, 1);

}*/
