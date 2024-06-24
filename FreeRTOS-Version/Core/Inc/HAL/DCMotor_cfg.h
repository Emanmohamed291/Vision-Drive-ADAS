/**
* 
* @file    : DC Motor (using H-Bridge) Driver Configuration Header File (HAL)
* @author  : Alaa Ghita
* @date    : May 2024
* @version : 1.0v
* 
*/

#ifndef _DCMOTOR_CFG_H
#define _DCMOTOR_CFG_H

#include	"DCMotor.h"

#define SYS_CORE_FREQUENCY      16000000UL

typedef enum
{
	DRIVING_MOTOR,
    STEERING_MOTOR,
    _DCMotors_num      /*Must Keep it as it is*/
}DCMotors_t;

#define TIMER_1 			NOT_USED
#define TIMER_2 			NOT_USED
#define TIMER_3 			USED
#define TIMER_4 			NOT_USED




#endif /*_DCMOTOR_CFG_H*/
