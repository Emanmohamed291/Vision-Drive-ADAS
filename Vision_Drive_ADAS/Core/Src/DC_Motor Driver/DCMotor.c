/**
* 
* @file    : DC Motor (using H-Bridge) Driver Source File (HAL)
* @author  : Alaa Ghita
* @date    : May 2024
* @version : 0.1v
* 
*/

/*Includes*/

//#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal.h"
//#include "stm32f103xb.h"

#include "DCMotor.h"
#include "DCMotor_cfg.h"
/**********/

/*Defines*/

#define MAX_SPEED		10000

#define IS_VALID_MOTOR(MOTOR)	((MOTOR) < _DCMotors_num)
/*********/

/*Types*/
extern TIM_HandleTypeDef htim3;
/*******/

/*Variables*/
extern const DCMotorcfg_t DCMotors[_DCMotors_num];
/***********/

/*Static Functions Prototypes*/
/****************************/

/*APIs Implementation*/

DCMotorErrorStatus_t DCMotor_Start(uint32_t Copy_u32DCMotor)
{
    DCMotorErrorStatus_t Ret_ErrorStatus = DCM_ErrorStatus_OK;
    if(IS_VALID_MOTOR(Copy_u32DCMotor) == 0)
    {
    	Ret_ErrorStatus = DCM_ErrorStatus_NotOK;
    }
    else
    {
    	HAL_GPIO_WritePin((GPIO_TypeDef *)DCMotors[Copy_u32DCMotor].Input_1.Port, DCMotors[Copy_u32DCMotor].Input_1.Pin, GPIO_PIN_SET);
    	HAL_GPIO_WritePin((GPIO_TypeDef *)DCMotors[Copy_u32DCMotor].Input_2.Port, DCMotors[Copy_u32DCMotor].Input_2.Pin, GPIO_PIN_RESET);
    	TIM3->CCR1 = MAX_SPEED/2;
    	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
    	//__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1, MAX_SPEED/2);
    }
    return Ret_ErrorStatus;
}



DCMotorErrorStatus_t DCMotor_Stop(uint32_t Copy_u32DCMotor)
{
    DCMotorErrorStatus_t Ret_ErrorStatus = DCM_ErrorStatus_OK;
    if(IS_VALID_MOTOR(Copy_u32DCMotor) == 0)
    {
      	Ret_ErrorStatus = DCM_ErrorStatus_NotOK;
    }
    else
    {
    	HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
    }
    return Ret_ErrorStatus;
}


DCMotorErrorStatus_t DCMotor_ReverseDirection(uint32_t Copy_u32DCMotor)
{
    DCMotorErrorStatus_t Ret_ErrorStatus = DCM_ErrorStatus_OK;
    if(IS_VALID_MOTOR(Copy_u32DCMotor) == 0)
    {
        Ret_ErrorStatus = DCM_ErrorStatus_NotOK;
    }
    else
    {
    	HAL_GPIO_WritePin((GPIO_TypeDef *)DCMotors[Copy_u32DCMotor].Input_1.Port, DCMotors[Copy_u32DCMotor].Input_1.Pin, GPIO_PIN_RESET);
    	HAL_GPIO_WritePin((GPIO_TypeDef *)DCMotors[Copy_u32DCMotor].Input_2.Port, DCMotors[Copy_u32DCMotor].Input_2.Pin, GPIO_PIN_SET);
    }
    return Ret_ErrorStatus;
}


DCMotorErrorStatus_t DCMotor_SetSpeed(uint32_t Copy_u32DCMotor, uint32_t Copy_u32SpeedPercentage)
{
    DCMotorErrorStatus_t Ret_ErrorStatus = DCM_ErrorStatus_OK;
    if(IS_VALID_MOTOR(Copy_u32DCMotor) == 0)
    {
        Ret_ErrorStatus = DCM_ErrorStatus_NotOK;
    }
    else
    {
    	TIM3->CCR1 = (MAX_SPEED*Copy_u32SpeedPercentage)/100;
    	__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1, (MAX_SPEED*Copy_u32SpeedPercentage)/100);
    }
    return Ret_ErrorStatus;
}


/*********************/
