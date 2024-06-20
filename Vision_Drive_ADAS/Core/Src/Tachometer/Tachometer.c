/**
*
* @file    : Tachometer Driver Header File (HAL)
* @author  : Alaa Ghita
* @date    : June 2024
* @version : 0.1v
*
*/


/*Includes*/
#include "stm32f1xx_hal.h"
/*********/

/*Defines*/
#define HOLES_NO            12
/*********/

/*Types*/
/*******/

/*Variables*/
extern TIM_HandleTypeDef htim2;
static uint32_t Counted_Holes = 0;
uint32_t Speed = 0;
uint32_t rpm = 0;
static uint32_t count = 0;
static uint32_t Prev_Counted_Holes= 0;
/***********/

/*Static Functions Prototypes*/
/****************************/


/*APIs Implementation*/

/*
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	Counted_Holes++;
}
*/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if (GPIO_Pin == GPIO_PIN_12)
	{
		Counted_Holes++;
	}
}

void Tachometer_Start(void)
{
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
	 HAL_TIM_Base_Start_IT(&htim2);
}

void Tachometer_Stop(void)
{
	HAL_NVIC_DisableIRQ(EXTI15_10_IRQn);
	HAL_TIM_Base_Stop_IT(&htim2);
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	count++;
	if (count == 1000)
	{	// Comes Every 1 Sec
	    Speed = Counted_Holes - Prev_Counted_Holes; // Tick per second
	    rpm = Speed * 60 / HOLES_NO; // Revolutions Per Minute
	    Prev_Counted_Holes = Counted_Holes;
	    count = 0;
	}
}

uint32_t Tachometer_Get_rpm(void)
{
	return rpm;
}
/*********************/
