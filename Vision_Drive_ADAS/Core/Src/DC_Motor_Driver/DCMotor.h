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
#include "DCMotor_cfg.h"
/**********/

/*Defines*/
//typedef unsigned long			uint32_t;
#define USED			0x0001UL
#define NOT_USED		0x0000UL

/*********/

/*Types*/

/*
typedef unsigned char        uint8_t;
typedef unsigned long        uint32_t;
typedef unsigned short       uint16_t;
*/

typedef struct
{
    uint32_t Pin;
    uint32_t * Port;
}DCMotorPins_t;

typedef enum
{
	Channel_1,
	Channel_2,
	Channel_3,
	Channel_4,
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
DCMotorErrorStatus_t DCMotor_Init(void);
DCMotorErrorStatus_t DCMotor_Start(uint32_t Copy_u32DCMotor);
DCMotorErrorStatus_t DCMotor_Stop(uint32_t Copy_u32DCMotor);
DCMotorErrorStatus_t DCMotor_StartForward(uint32_t Copy_u32DCMotor);
DCMotorErrorStatus_t DCMotor_StartReverse(uint32_t Copy_u32DCMotor);
DCMotorErrorStatus_t DCMotor_SetSpeed(uint32_t Copy_u32DCMotor, uint32_t Copy_u32SpeedPercentage);
/******/

#endif /*_DCMOTOR_H*/
