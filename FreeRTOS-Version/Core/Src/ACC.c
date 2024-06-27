/**
*
* @file    : Adaptive Cruise Control Module Source File (HAL)
* @author  : Alaa Ghita
* @date    : June 2024
* @version : 0.1v
*
*/

/************************************************Includes************************************************/
#include "ACC.h"
#include "HAL/DCMotor.h"
#include "HAL/DCMotor_cfg.h"
#include "ultrasonic.h"
#include "cmsis_os.h"
#include "task.h"
/********************************************************************************************************/



/************************************************Defines*************************************************/
#define IS_VALID_MODE(MODE)					(((MODE) == Cruise_Control) || ((MODE)==Adaptive_Cruise_Control))
//the inputed speed must be a percentage (TILL NOW CAUSE I DON'T KNOW WHAT IS THE WRITE DECISION:<)
#define IS_VALID_SPEED(SPEED)				((SPEED)<=100)
//Limits to the allowed Distance between the 2 cars
#define IS_VALID_DISTANCE(DISTANCE)			(((DISTANCE)>=5) && ((DISTANCE)<=50))
/********************************************************************************************************/



/************************************************Types***************************************************/
typedef enum
{
	ACC_OFF,
	ACC_ON
}enuACC_State;
/********************************************************************************************************/



/************************************************Variables***********************************************/
uint32_t Max_Speed = 70;
uint32_t Min_Distance = 10;
enuACC_State ACC_State = ACC_ON;
enuACC_Modes ACC_Mode = Adaptive_Cruise_Control;
extern TaskHandle_t Distance1_Measure;
extern float Distance_CH1;
extern float Distance_CH2;
/********************************************************************************************************/



/*****************************************Static Functions Prototype*************************************/
/********************************************************************************************************/



/*********************************************APIs Implementation****************************************/
enuErrorStatus_t ACC_SetMode(enuACC_Modes Copy_enuMode)
{
	enuErrorStatus_t Ret_enuErrorStatus = enuErrorStatus_Ok;
	if(!IS_VALID_MODE(Copy_enuMode))
	{
		Ret_enuErrorStatus = enuErrorStatus_InvalidParameter;
	}
	else
	{
		ACC_Mode = Copy_enuMode;
	}

	return Ret_enuErrorStatus;
}

enuErrorStatus_t ACC_SetMaxSpeed(uint16_t Copy_u16MaxSpeed)
{
	enuErrorStatus_t Ret_enuErrorStatus = enuErrorStatus_Ok;
	if(!IS_VALID_SPEED(Copy_u16MaxSpeed))
	{
		Ret_enuErrorStatus = enuErrorStatus_InvalidParameter;
	}
	else
	{
		Max_Speed = Copy_u16MaxSpeed;
	}

	return Ret_enuErrorStatus;
}

enuErrorStatus_t ACC_SetMinDistance(uint16_t Copy_u16MinDistance)
{
	enuErrorStatus_t Ret_enuErrorStatus = enuErrorStatus_Ok;
	if(!IS_VALID_DISTANCE(Copy_u16MinDistance))
	{
		Ret_enuErrorStatus = enuErrorStatus_InvalidParameter;
	}
	else
	{
		Min_Distance = Copy_u16MinDistance;
	}

	return Ret_enuErrorStatus;
}

void ACC_Satrt(void)
{
	ACC_State = ACC_ON;
}

void ACC_Stop(void)
{
	ACC_State = ACC_OFF;
}

void CruiseControl_Task(void const * argument)
{
  /* USER CODE BEGIN CruiseControl_Task */
  /* Infinite loop */
  for(;;)
  {
	switch(ACC_State)
	{
	case(ACC_ON):
		uint32_t Current_Speed;
		//float Current_Distance = 0.0;
		if(DCMotor_GetSpeedPrecentage(DRIVING_MOTOR, &Current_Speed)==enuErrorStatus_Ok)
		{
			switch(ACC_Mode)
			{
			case(Cruise_Control):
				if(Distance1_Measure != NULL)
				{
					vTaskSuspend(Distance1_Measure);
				}
				if(Current_Speed>Max_Speed && (Current_Speed>10))
				{
					//while(Current_Speed>(Max_Speed-1))
					//{
						Current_Speed--;
						DCMotor_SetSpeed(DRIVING_MOTOR, Current_Speed);
						//DCMotor_GetSpeedPrecentage(DRIVING_MOTOR, &Current_Speed);
					//}
				}
			break;
			case(Adaptive_Cruise_Control):
				if(Distance1_Measure != NULL)
				{
					vTaskResume(Distance1_Measure);
				}
				if((Distance_CH1<Min_Distance) && (Current_Speed>10))
				{
					//while((Distance_CH1<(Min_Distance+1))&&Current_Speed)
					//{
						Current_Speed-=5;
						DCMotor_SetSpeed(DRIVING_MOTOR, Current_Speed);
						//DCMotor_GetSpeedPrecentage(DRIVING_MOTOR, &Current_Speed);
					//}
				}
				else if(Current_Speed>Max_Speed)
				{
					//while(Current_Speed>(Max_Speed-5))
					//{
						Current_Speed-=5;
						DCMotor_SetSpeed(DRIVING_MOTOR, Current_Speed);
						//DCMotor_GetSpeedPrecentage(DRIVING_MOTOR, &Current_Speed);
					//}
				}
			break;
			}
		}
		break;
	case(ACC_OFF):
		/*Do Nothing!*/
		if(Distance1_Measure != NULL)
		{
			vTaskSuspend(Distance1_Measure);
		}
		break;
	}
    osDelay(1); //This delay is in ms
  }
  /* USER CODE END CruiseControl_Task */
}
/********************************************************************************************************/

