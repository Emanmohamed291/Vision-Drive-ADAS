/**
* 
* @file    : DC Motor (using H-Bridge) Driver Source File (HAL)
* @author  : Alaa Ghita
* @date    : May 2024
* @version : 1.0v
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

/*******/

/*Variables*/
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;

extern const DCMotorcfg_t DCMotors[_DCMotors_num];

static uint32_t Motor_Speed[_DCMotors_num] = {MAX_SPEED/2,MAX_SPEED/2};
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
    	switch (DCMotors[Copy_u32DCMotor].Enable_Timer)
    	{
    		/*case Timer_1:
    			__HAL_TIM_SET_COMPARE(&htim1,DCMotors[Copy_u32DCMotor].Enable_Channel, Motor_Speed[Copy_u32DCMotor]);
    			HAL_TIM_PWM_Start(&htim1, DCMotors[Copy_u32DCMotor].Enable_Channel);
    			break;
    		case Timer_2:
    		    __HAL_TIM_SET_COMPARE(&htim2,DCMotors[Copy_u32DCMotor].Enable_Channel, Motor_Speed[Copy_u32DCMotor]);
    			HAL_TIM_PWM_Start(&htim2, DCMotors[Copy_u32DCMotor].Enable_Channel);
    		    break;*/
    		case Timer_3:
    		    __HAL_TIM_SET_COMPARE(&htim3,DCMotors[Copy_u32DCMotor].Enable_Channel, Motor_Speed[Copy_u32DCMotor]);
    		    HAL_TIM_PWM_Start(&htim3, DCMotors[Copy_u32DCMotor].Enable_Channel);
    		    break;
    		/*case Timer_4:
    		    __HAL_TIM_SET_COMPARE(&htim4,DCMotors[Copy_u32DCMotor].Enable_Channel, Motor_Speed[Copy_u32DCMotor]);
    		    HAL_TIM_PWM_Start(&htim4, DCMotors[Copy_u32DCMotor].Enable_Channel);
    		    break;*/
    		default:
    			Ret_ErrorStatus = DCM_ErrorStatus_NotOK;
    	}
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
    	switch (DCMotors[Copy_u32DCMotor].Enable_Timer)
    	{
    		/*case Timer_1:
    			HAL_TIM_PWM_Stop(&htim1, DCMotors[Copy_u32DCMotor].Enable_Channel);
    			break;
    		case Timer_2:
    			HAL_TIM_PWM_Stop(&htim2, DCMotors[Copy_u32DCMotor].Enable_Channel);
    		    break;*/
    		case Timer_3:
    			HAL_TIM_PWM_Stop(&htim3, DCMotors[Copy_u32DCMotor].Enable_Channel);
    		    break;
    		/*case Timer_4:
    			HAL_TIM_PWM_Stop(&htim4, DCMotors[Copy_u32DCMotor].Enable_Channel);
    		    break;*/
    		default:
    			Ret_ErrorStatus = DCM_ErrorStatus_NotOK;
    	}

    }
    return Ret_ErrorStatus;
}


DCMotorErrorStatus_t DCMotor_StartForward(uint32_t Copy_u32DCMotor)
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

	    	switch (DCMotors[Copy_u32DCMotor].Enable_Timer)
	    	{
	    		/*case Timer_1:
	    			__HAL_TIM_SET_COMPARE(&htim1,DCMotors[Copy_u32DCMotor].Enable_Channel, Motor_Speed[Copy_u32DCMotor]);
	    			HAL_TIM_PWM_Start(&htim1, DCMotors[Copy_u32DCMotor].Enable_Channel);
	    			break;
	    		case Timer_2:
	    		    __HAL_TIM_SET_COMPARE(&htim2,DCMotors[Copy_u32DCMotor].Enable_Channel, Motor_Speed[Copy_u32DCMotor]);
	    			HAL_TIM_PWM_Start(&htim2, DCMotors[Copy_u32DCMotor].Enable_Channel);
	    		    break;*/
	    		case Timer_3:
	    		    __HAL_TIM_SET_COMPARE(&htim3,DCMotors[Copy_u32DCMotor].Enable_Channel, Motor_Speed[Copy_u32DCMotor]);
	    		    HAL_TIM_PWM_Start(&htim3, DCMotors[Copy_u32DCMotor].Enable_Channel);
	    		    break;
	    		/*case Timer_4:
	    		    __HAL_TIM_SET_COMPARE(&htim4,DCMotors[Copy_u32DCMotor].Enable_Channel, Motor_Speed[Copy_u32DCMotor]);
	    		    HAL_TIM_PWM_Start(&htim4, DCMotors[Copy_u32DCMotor].Enable_Channel);
	    		    break;*/
	    		default:
	    			Ret_ErrorStatus = DCM_ErrorStatus_NotOK;
	    	}

	    }
	    return Ret_ErrorStatus;
}

DCMotorErrorStatus_t DCMotor_StartReverse(uint32_t Copy_u32DCMotor)
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


    	switch (DCMotors[Copy_u32DCMotor].Enable_Timer)
    	{
    		/*case Timer_1:
    			__HAL_TIM_SET_COMPARE(&htim1,DCMotors[Copy_u32DCMotor].Enable_Channel, Motor_Speed[Copy_u32DCMotor]);
    			HAL_TIM_PWM_Start(&htim1, DCMotors[Copy_u32DCMotor].Enable_Channel);
    			break;
    		case Timer_2:
    		    __HAL_TIM_SET_COMPARE(&htim2,DCMotors[Copy_u32DCMotor].Enable_Channel, Motor_Speed[Copy_u32DCMotor]);
    			HAL_TIM_PWM_Start(&htim2, DCMotors[Copy_u32DCMotor].Enable_Channel);
    		    break;*/
    		case Timer_3:
    		    __HAL_TIM_SET_COMPARE(&htim3,DCMotors[Copy_u32DCMotor].Enable_Channel, Motor_Speed[Copy_u32DCMotor]);
    		    HAL_TIM_PWM_Start(&htim3, DCMotors[Copy_u32DCMotor].Enable_Channel);
    		    break;
    		/*case Timer_4:
    		    __HAL_TIM_SET_COMPARE(&htim4,DCMotors[Copy_u32DCMotor].Enable_Channel, Motor_Speed[Copy_u32DCMotor]);
    		    HAL_TIM_PWM_Start(&htim4, DCMotors[Copy_u32DCMotor].Enable_Channel);
    		    break;*/
    		default:
    			Ret_ErrorStatus = DCM_ErrorStatus_NotOK;
    	}

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
    	switch (DCMotors[Copy_u32DCMotor].Enable_Timer)
    	{
    		/*case Timer_1:
    			Motor_Speed[Copy_u32DCMotor] = (MAX_SPEED*Copy_u32SpeedPercentage)/100;
    			__HAL_TIM_SET_COMPARE(&htim1,DCMotors[Copy_u32DCMotor].Enable_Channel, Motor_Speed[Copy_u32DCMotor]);
    			break;
    		case Timer_2:
    			Motor_Speed[Copy_u32DCMotor] = (MAX_SPEED*Copy_u32SpeedPercentage)/100;
    			__HAL_TIM_SET_COMPARE(&htim2,DCMotors[Copy_u32DCMotor].Enable_Channel, Motor_Speed[Copy_u32DCMotor]);
    		    break;*/
    		case Timer_3:
    			Motor_Speed[Copy_u32DCMotor] = (MAX_SPEED*Copy_u32SpeedPercentage)/100;
    			__HAL_TIM_SET_COMPARE(&htim3,DCMotors[Copy_u32DCMotor].Enable_Channel, Motor_Speed[Copy_u32DCMotor]);
    		    break;
    		/*case Timer_4:
    			Motor_Speed[Copy_u32DCMotor] = (MAX_SPEED*Copy_u32SpeedPercentage)/100;
    			__HAL_TIM_SET_COMPARE(&htim4,DCMotors[Copy_u32DCMotor].Enable_Channel, Motor_Speed[Copy_u32DCMotor]);
    		    break;*/
    		default:
    			Ret_ErrorStatus = DCM_ErrorStatus_NotOK;
    	}

    }
    return Ret_ErrorStatus;
}


/*********************/
