/*
 * servo.c
 *
 *  Created on: Jun 21, 2024
 *      Author: Eman
 */


#include "ultrasonic.h"

static uint8_t Is_First_Captured_CH1 = 0; // flag for channel 1 first capture
static uint32_t IC_Val1_CH1 = 0, IC_Val2_CH1 = 0, Difference_CH1 = 0;
float Distance_CH1 = 0.0f;
static uint8_t Is_First_Captured_CH2 = 0; // flag for channel 1 first capture
static uint32_t IC_Val1_CH2 = 0, IC_Val2_CH2 = 0, Difference_CH2 = 0;
float Distance_CH2 = 0.0f;

void Delay(uint16_t delay){
	__HAL_TIM_SET_COUNTER(&htim2, 0);
	while(__HAL_TIM_GET_COUNTER(&htim2) < delay);
}

#define TRIG_PIN GPIO_PIN_9
#define TRIG_PORT GPIOA

// Let's write the callback function

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM1) // Check if the interrupt source is TIM1
    {
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1) // Channel 1
        {
            if (Is_First_Captured_CH1 == 0)
            {
                IC_Val1_CH1 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
                Is_First_Captured_CH1 = 1;
                __HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_FALLING);
            }
            else
            {
                IC_Val2_CH1 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
                Difference_CH1 = IC_Val2_CH1 > IC_Val1_CH1 ? IC_Val2_CH1 - IC_Val1_CH1 : (0xFFFF - IC_Val1_CH1) + IC_Val2_CH1;
                Distance_CH1 = Difference_CH1 * 0.034 / 2;
                Is_First_Captured_CH1 = 0;
                __HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_RISING);
                __HAL_TIM_DISABLE_IT(htim, TIM_IT_CC1);
            }
        }

        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2) // Channel 2
        {
            if (Is_First_Captured_CH2 == 0)
            {
                IC_Val1_CH2 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);
                Is_First_Captured_CH2 = 1;
                __HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_2, TIM_INPUTCHANNELPOLARITY_FALLING);
            }
            else
            {
                IC_Val2_CH2 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);
                Difference_CH2 = IC_Val2_CH2 > IC_Val1_CH2 ? IC_Val2_CH2 - IC_Val1_CH2 : (0xFFFF - IC_Val1_CH2) + IC_Val2_CH2;
                Distance_CH2 = Difference_CH2 * 0.034 / 2;
                Is_First_Captured_CH2 = 0;
                __HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_2, TIM_INPUTCHANNELPOLARITY_RISING);
                __HAL_TIM_DISABLE_IT(htim, TIM_IT_CC2);
            }
        }
    }
}


float HCSR04_Read_ch1 (void)
{
	HAL_GPIO_WritePin(Trig1_GPIO_Port, Trig1_Pin, GPIO_PIN_SET);  // pull the TRIG pin HIGH
	Delay(10);  // wait for 10 us
	HAL_GPIO_WritePin(Trig1_GPIO_Port, Trig1_Pin, GPIO_PIN_RESET);  // pull the TRIG pin low

	__HAL_TIM_ENABLE_IT(&htim1, TIM_IT_CC1);
	return Distance_CH1;
}
float HCSR04_Read_ch2 (void)
{
	HAL_GPIO_WritePin(Trig2_GPIO_Port, Trig2_Pin, GPIO_PIN_SET);  // pull the TRIG pin HIGH
	Delay(10);  // wait for 10 us
	HAL_GPIO_WritePin(Trig2_GPIO_Port, Trig2_Pin, GPIO_PIN_RESET);  // pull the TRIG pin low

	__HAL_TIM_ENABLE_IT(&htim1, TIM_IT_CC2);
	return Distance_CH1;
}


