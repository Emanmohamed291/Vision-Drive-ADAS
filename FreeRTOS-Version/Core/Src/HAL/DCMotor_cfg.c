/**
* 
* @file    : DC Motor (using H-Bridge) Driver Configuration Source File (HAL)
* @author  : Alaa Ghita
* @date    : May 2024
* @version : 1.0v
* 
*/


/*Includes*/
#include "stm32f1xx_hal.h"
#include "DCMotor.h"
#include "DCMotor_cfg.h"
/**********/

/*Defines*/
/*********/

/*Types*/
/*******/

/*Variables*/
const DCMotorcfg_t DCMotors[_DCMotors_num] = 
{
    [DRIVING_MOTOR] = {.Input_1.Pin = GPIO_PIN_1,
                   .Input_1.Port = GPIOA,
                   .Input_2.Pin = GPIO_PIN_2,
                   .Input_2.Port = GPIOA,
                   .Enable_Timer = Timer_3,
                   .Enable_Channel = Channel_1},

    [STEERING_MOTOR] = {.Input_1.Pin = GPIO_PIN_3,
                   .Input_1.Port = GPIOA,
                   .Input_2.Pin = GPIO_PIN_4, 
                   .Input_2.Port = GPIOA,
				   .Enable_Timer = Timer_3,
				   .Enable_Channel = Channel_2},
};
/***********/

/*Static Functions Prototypes*/
/****************************/

/*APIs Implementation*/
/*********************/
