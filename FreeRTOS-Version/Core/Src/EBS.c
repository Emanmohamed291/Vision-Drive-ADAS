/*
 * EBS.c
 *
 *  Created on: Jun 27, 2024
 *      Author: Alaa
 */

#include "ultrasonic.h"
#include "HAL/DCMotor_cfg.h"
#include "HAL/DCMotor.h"

#define MINIMUM_DISTANCE	25	//Minimum distance in cm

void braking_task(void)
{
	if(MINIMUM_DISTANCE >= Distance_CH1)
	{
		DCMotor_Stop(STEERING_MOTOR);
		DCMotor_Stop(DRIVING_MOTOR);
	}
}


