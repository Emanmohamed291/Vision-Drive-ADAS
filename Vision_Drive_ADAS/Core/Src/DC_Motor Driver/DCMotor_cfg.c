/**
* 
* @file    : DC Motor (using H-Bridge) Driver Configuration Source File (HAL)
* @author  : Alaa Ghita
* @date    : May 2024
* @version : 0.1v
* 
*/


/*Includes*/
#include "stm32f1xx_hal.h"
#include "DCMotor.h"
#include "DCMotor_cfg.h"
//#include "stm32f103xb.h"
/**********/

/*Defines*/
/*********/

/*Types*/
/*******/

/*Variables*/
const DCMotorcfg_t DCMotors[_DCMotors_num] = 
{
    [DCMotor_1] = {.Input_1.Pin = GPIO_PIN_1,
                   .Input_1.Port = GPIOA,
                   .Input_2.Pin = GPIO_PIN_2,
                   .Input_2.Port = GPIOA,
                   .Enable_Pin.Pin = GPIO_PIN_4,
                   .Enable_Pin.Port = GPIOA,
                   .DCMotor_Speed = 70},

    [DCMotor_2] = {.Input_1.Pin = GPIO_PIN_3, 
                   .Input_1.Port = GPIOA,
                   .Input_2.Pin = GPIO_PIN_4, 
                   .Input_2.Port = GPIOA,
                   .Enable_Pin.Pin = GPIO_PIN_5,
                   .Enable_Pin.Port = GPIOA,
                   .DCMotor_Speed = 70},
};
/***********/

/*Static Functions Prototyes*/
/****************************/

/*APIs Implementation*/
/*********************/
