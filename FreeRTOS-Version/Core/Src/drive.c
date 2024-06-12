/*
 * drive.c
 *
 *  Created on: Jun 8, 2024
 *      Author: workstation
 */

/*===========================================================================================================*/
/*												    Includes	 										     */
/*===========================================================================================================*/
#include "HAL/DCMotor.h"

#include "cmsis_os.h"
#include "task.h"
#include "HAL/bluetooth.h"

/*===========================================================================================================*/
/*												     Macros		 										     */
/*===========================================================================================================*/
#define MAX_RPM 5000
#define TYRE_CIRC 0.15

#define MAX_SPEED ((MAX_RPM)*(TYRE_CIRC)*0.06)

#define DRIVING_MOTOR	0
#define STEERING_MOTOR 	1

typedef enum
{
	idle 		= 0xFF,
	forward 	= 'F',
	backward 	= 'B',
	steer_right = 'R',
	steer_left	= 'L',
	speed_0     = '0',
	speed_10    = '1',
	speed_20    = '2',
	speed_30    = '3',
	speed_40    = '4',
	speed_50    = '5',
	speed_60    = '6',
	speed_70    = '7',
	speed_80    = '8',
	speed_90    = '9',
	speed_100   = 'q',
	stop		= 'S',
	stop_all	= 'D'
}Drive_States;

struct CarState
{
	uint8_t DriverInput;
	int dir;
	int speed;
	Drive_States last_state;

};


struct CarState CarInfo = {0, forward, 0, idle};

void get_data_task(void * pvParameters)
{
	//uint8_t Data = 0;
	while(1)
	{
		CarInfo.DriverInput = BL_ReadByteSync();
		//HAL_USART_Receive(&husart1, &Data, 1, 1);
		//HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
		vTaskDelay(pdMS_TO_TICKS(10));
	}
}

void drive_task(void)
{
	int steer_counter = 0;

	//DCMotorInit();
	//DCMotor_Start(DRIVING_MOTOR);
	DCMotor_SetSpeed(STEERING_MOTOR, 50);

	while(1)
	{
		switch(CarInfo.DriverInput)
		{
		case idle:
			if(steer_counter > 0)
			{
				steer_counter = 0;
				DCMotor_Stop(STEERING_MOTOR);
			}
			break;

		case forward:
			if((CarInfo.last_state == steer_right) || (CarInfo.last_state == steer_left))
			{
				DCMotor_Stop(STEERING_MOTOR);
			}
			DCMotor_Start(DRIVING_MOTOR);
			CarInfo.DriverInput = idle;
			break;

		case backward:
			if((CarInfo.last_state == steer_right) || (CarInfo.last_state == steer_left))
			{
				DCMotor_Stop(STEERING_MOTOR);
			}
			DCMotor_StartReverse(DRIVING_MOTOR);
			//DCMotor_Start(DRIVING_MOTOR);
			CarInfo.DriverInput = idle;
			break;

		case steer_right:
			DCMotor_StartReverse(STEERING_MOTOR);
			steer_counter++;
			CarInfo.DriverInput=idle;
			break;

		case steer_left:
			DCMotor_Start(STEERING_MOTOR);
			steer_counter++;
			CarInfo.DriverInput=idle;
			break;

		case speed_100: CarInfo.DriverInput = 100;
		case speed_0:
		case speed_10:
		case speed_20:
		case speed_30:
		case speed_40:
		case speed_50:
		case speed_60:
		case speed_70:
		case speed_80:
		case speed_90:
			DCMotor_SetSpeed(DRIVING_MOTOR, CarInfo.DriverInput);
			CarInfo.speed = CarInfo.DriverInput;
			CarInfo.DriverInput=idle;
//			CarInfo.DriverInput += 10;
//			if(CarInfo.DriverInput >= 100) CarInfo.DriverInput %= 100;
			break;

		case stop:
			DCMotor_Stop(DRIVING_MOTOR);
			DCMotor_Stop(STEERING_MOTOR);
			CarInfo.DriverInput=idle;
			break;

		default: break;
		}

		vTaskDelay(pdMS_TO_TICKS(2));
	}
}
