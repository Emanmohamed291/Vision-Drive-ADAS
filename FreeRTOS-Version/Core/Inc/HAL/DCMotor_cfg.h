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

#define SYS_CORE_FREQUENCY      16000000UL

typedef enum
{
    DCMotor_1,          /*An Example*/
    DCMotor_2,          /*An Example*/
    _DCMotors_num      /*Must Keep it as it is*/
}DCMotors_t;

#endif /*_DCMOTOR_CFG_H*/
