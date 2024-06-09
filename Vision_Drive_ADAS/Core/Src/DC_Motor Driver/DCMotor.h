/**
* 
* @file    : DC Motor (using H-Bridge) Driver Header File (HAL)
* @author  : Alaa Ghita
* @date    : May 2024
* @version : 0.1v
* 
*/

#ifndef _DCMOTOR_H
#define _DCMOTOR_H

/*Includes*/
#include "stm32f1xx_hal_def.h"    /*Not so sure if it's exactly this file or not*/
#include "DCMotor_cfg.h"
/**********/

/*Defines*/
typedef unsigned char        uint8_t;
typedef unsigned long        uint32_t;
typedef unsigned short       uint16_t;

typedef enum
{
    Input_1,
    Input_2,
    Enable_Pin,
    _DCM_Pins_num
}DCMotorConnectedPins_t;

typedef struct
{
    uint32_t Pin;
    uint32_t Port;
}DCMotorPins_t;

typedef struct
{
    DCMotorPins_t Input_1;
    DCMotorPins_t Input_2;
    DCMotorPins_t Enable_Pin;   
    uint32_t DCMotor_Speed;
    /*uint32_t DCMotor_Direction; */
}DCMotorcfg_t;

typedef enum
{
    DCM_ErrorStatus_OK,
    DCM_ErrorStatus_NotOK,
    DCM_ErrorStatus_InvalidConfig,
    DCM_ErrorStatus_InvalidParam,
}DCMotorErrorStatus_t;
/*********/

/*Types*/
/*******/

/*APIs*/
DCMotorErrorStatus_t DCMotor_Init(void);
DCMotorErrorStatus_t DCMotor_Start(uint32_t Copy_u32DCMotor);
DCMotorErrorStatus_t DCMotor_Stop(uint32_t Copy_u32DCMotor);
DCMotorErrorStatus_t DCMotor_ReverseDirection(uint32_t Copy_u32DCMotor);
DCMotorErrorStatus_t DCMotor_SetSpeed(uint32_t Copy_u32DCMotor, uint32_t Copy_u32SpeedPercentage);
/******/

#endif /*_DCMOTOR_H*/