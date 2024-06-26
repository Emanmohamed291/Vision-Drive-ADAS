
/**
*
* @file    : DC Motor (using H-Bridge) Driver Header File (HAL)
* @author  : Alaa Ghita
* @date    : May 2024
* @version : 1.0v
*
*/

#ifndef _DCMOTOR_H
#define _DCMOTOR_H

/*Includes*/
#include "stm32f1xx_hal.h"
#include "DCMotor_cfg.h"
#include "ErrorStatus.h"
/**********/

/*Defines*/
/*********/

/*Types*/
typedef unsigned char        uint8_t;
typedef unsigned long        uint32_t;
typedef unsigned short       uint16_t;


typedef struct
{
    uint32_t Pin;
    uint32_t * Port;
}DCMotorPins_t;

typedef enum
{
	Channel_1=0,
	Channel_2=4,
	Channel_3=8,
	Channel_4=12,
}Enable_Tim_Channel;

typedef enum
{
	Timer_1,
	Timer_2,
	Timer_3,
	Timer_4,
}Enable_Tim;

typedef struct
{
    DCMotorPins_t Input_1;
    DCMotorPins_t Input_2;
    Enable_Tim Enable_Timer;
    Enable_Tim_Channel Enable_Channel;
}DCMotorcfg_t;

typedef enum
{
    DCM_ErrorStatus_OK,
    DCM_ErrorStatus_NotOK,
    DCM_ErrorStatus_InvalidConfig,
    DCM_ErrorStatus_InvalidParam,
}DCMotorErrorStatus_t;
/*********/



/*APIs*/
enuErrorStatus_t DCMotor_Init(void);
enuErrorStatus_t DCMotor_Start(uint32_t Copy_u32DCMotor);
enuErrorStatus_t DCMotor_Stop(uint32_t Copy_u32DCMotor);
enuErrorStatus_t DCMotor_StartForward(uint32_t Copy_u32DCMotor);
enuErrorStatus_t DCMotor_StartReverse(uint32_t Copy_u32DCMotor);
enuErrorStatus_t DCMotor_SetSpeed(uint32_t Copy_u32DCMotor, uint32_t Copy_u32SpeedPercentage);
enuErrorStatus_t DCMotor_GetSpeedPrecentage(uint32_t Copy_u32DCMotor, uint32_t * Add_pu32Speed);
/******/

#endif /*_DCMOTOR_H*/
