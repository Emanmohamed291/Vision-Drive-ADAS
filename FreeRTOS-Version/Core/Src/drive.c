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
#define MAX_RPM 					//why we need this ??
#define TYRE_CIRC 0.15

#define MAX_SPEED ((MAX_RPM)*(TYRE_CIRC)*0.06)

#define DRIVING_MOTOR	0
#define STEERING_MOTOR 	1

//#define TRIG2_PIN GPIO_PIN_3
//#define TRIG2_PORT GPIOB
//#define TRIG1_PIN GPIO_PIN_15
//#define TRIG1_PORT GPIOA

//extern TIM_HandleTypeDef htim2;

//int32_t IC_Val1 = 0;
//uint32_t IC_Val2 = 0;
//uint32_t Difference = 0;
//uint8_t Is_First_Captured = 0;  // is the first value captured ?
//
//uint8_t Distance1  = 0;
//uint8_t Distance2  = 0;
//static uint8_t Is_First_Captured_CH1 = 0; // flag for channel 1 first capture
//static uint32_t IC_Val1_CH1 = 0, IC_Val2_CH1 = 0, Difference_CH1 = 0;
//float Distance_CH1 = 0.0f;
//static uint8_t Is_First_Captured_CH2 = 0; // flag for channel 1 first capture
//static uint32_t IC_Val1_CH2 = 0, IC_Val2_CH2 = 0, Difference_CH2 = 0;
//float Distance_CH2 = 0.0f;

typedef enum
{
	idle 		= 0xFF,
	forward 	= 'F',
	backward 	= 'B',
	steer_right = 'R',
	steer_left	= 'L',
	fwd_left	= 'G',
	fwd_right   = 'I',
	back_left   = 'H',
	back_right	= 'J',
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

		vTaskDelay(pdMS_TO_TICKS(10));
	}
}

void drive_task(void)
{
	//int steer_counter = 0;

	//DCMotorInit();
	//DCMotor_Start(DRIVING_MOTOR);
	DCMotor_SetSpeed(STEERING_MOTOR, 100);
	BL_ReadAsync(&(CarInfo.DriverInput));

	while(1)
	{
		switch(CarInfo.DriverInput)
		{
		case idle:
			break;

		case forward:

			DCMotor_StartForward(DRIVING_MOTOR);
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
			DCMotor_SetSpeed(STEERING_MOTOR, 100);
			DCMotor_StartForward(STEERING_MOTOR);
			//steer_counter++;
			CarInfo.DriverInput=idle;
			break;

		case steer_left:
			DCMotor_SetSpeed(STEERING_MOTOR, 100);
			DCMotor_StartReverse(STEERING_MOTOR);
			//steer_counter++;
			CarInfo.DriverInput=idle;
			break;

		case speed_100: CarInfo.DriverInput = ':';
		case speed_0:
		case speed_10:
		case speed_20:
		case speed_30:
		case speed_40:
		case speed_50:
		case speed_60:
		case speed_70:
		case speed_80:
		case speed_90: CarInfo.speed = (CarInfo.DriverInput - '0')*10;
			DCMotor_SetSpeed(DRIVING_MOTOR, CarInfo.speed);
			CarInfo.DriverInput=idle;
//			CarInfo.DriverInput += 10;
//			if(CarInfo.DriverInput >= 100) CarInfo.DriverInput %= 100;
			break;

		case fwd_left:  DCMotor_StartReverse(STEERING_MOTOR); DCMotor_StartForward(DRIVING_MOTOR); break;
		case fwd_right: DCMotor_StartForward(STEERING_MOTOR); DCMotor_StartForward(DRIVING_MOTOR); break;
		case back_left: DCMotor_StartReverse(STEERING_MOTOR); DCMotor_StartReverse(DRIVING_MOTOR); break;
		case back_right:DCMotor_StartForward(STEERING_MOTOR); DCMotor_StartReverse(DRIVING_MOTOR); break;

		case stop:
			DCMotor_Stop(STEERING_MOTOR);
			DCMotor_Stop(DRIVING_MOTOR);
			CarInfo.DriverInput=idle;
			break;

		default: break;
		}

		vTaskDelay(pdMS_TO_TICKS(2));
	}
}

/* ultrasonic task fo blind spot detection */
//void HCSR04_1_Read_task(void * pvParameters)
//{
//	//uint8_t Data = 0;
//	while(1)
//	{
//		HAL_GPIO_WritePin(TRIG1_PORT, TRIG1_PIN, GPIO_PIN_SET);  // pull the TRIG pin HIGH
//		vTaskDelay(pdMS_TO_TICKS(1));  // wait for 10 us
//		HAL_GPIO_WritePin(TRIG1_PORT, TRIG1_PIN, GPIO_PIN_RESET);  // pull the TRIG pin low
//
//		__HAL_TIM_ENABLE_IT(&htim2, TIM_IT_CC1);
//		vTaskDelay(pdMS_TO_TICKS(100));
//	}
//}
///* ultrasonic task fo blind spot detection */
//void HCSR04_2_Read_task(void * pvParameters)
//{
//	//uint8_t Data = 0;
//	while(1)
//	{
//		HAL_GPIO_WritePin(TRIG2_PORT, TRIG2_PIN, GPIO_PIN_SET);  // pull the TRIG pin HIGH
//		vTaskDelay(pdMS_TO_TICKS(1));  // wait for 10 us
//		HAL_GPIO_WritePin(TRIG2_PORT, TRIG2_PIN, GPIO_PIN_RESET);  // pull the TRIG pin low
//
//		__HAL_TIM_ENABLE_IT(&htim2, TIM_IT_CC1);
//		vTaskDelay(pdMS_TO_TICKS(100));
//	}
//}
//
///* ultrasonic task fo blind spot detection */
//void blind_spot_task(void * pvParameters)
//{
//	//uint8_t Data = 0;
//	while(1)
//	{
//		if(Distance_CH1 >10){
//		//  HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
//		//	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
//		}
//		else{
//		//	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
//		//  HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
//		}
//		if(Distance_CH2 >10){
//			//  HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
//		}
//		else{
//			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
//		//  HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
//		}
//		vTaskDelay(pdMS_TO_TICKS(120));
//	}
//}
//
//// Let's write the callback function
//
//
//void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
//{
//	// Channel 1 handling
//	if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)  // if the interrupt source is channel1
//	{
////		static uint8_t Is_First_Captured_CH1 = 0; // flag for channel 1 first capture
////		static uint32_t IC_Val1_CH1 = 0, IC_Val2_CH1 = 0, Difference_CH1 = 0;
//
//
//		if (Is_First_Captured_CH1 == 0) // if the first value is not captured
//		{
//			IC_Val1_CH1 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1); // read the first value
//			Is_First_Captured_CH1 = 1;  // set the first captured as true
//			// Now change the polarity to falling edge
//			__HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_FALLING);
//		}
//		else if (Is_First_Captured_CH1 == 1)   // if the first is already captured
//		{
//			IC_Val2_CH1 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);  // read second value
//			__HAL_TIM_SET_COUNTER(htim, 0);  // reset the counter
//
//			if (IC_Val2_CH1 > IC_Val1_CH1)
//			{
//				Difference_CH1 = IC_Val2_CH1 - IC_Val1_CH1;
//			}
//			else if (IC_Val1_CH1 > IC_Val2_CH1)
//			{
//				Difference_CH1 = (0xffff - IC_Val1_CH1) + IC_Val2_CH1;
//			}
//
//			Distance_CH1 = Difference_CH1 * .034 / 2;
//			Is_First_Captured_CH1 = 0; // set it back to false
//
//			// set polarity to rising edge
//			__HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_RISING);
//			__HAL_TIM_DISABLE_IT(&htim2, TIM_IT_CC1);
//		}
//	}
//
//	// Channel 2 handling
//	if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)  // if the interrupt source is channel2
//	{
////		static uint8_t Is_First_Captured_CH2 = 0; // flag for channel 2 first capture
////		static uint32_t IC_Val1_CH2 = 0, IC_Val2_CH2 = 0, Difference_CH2 = 0;
//
//		if (Is_First_Captured_CH2 == 0) // if the first value is not captured
//		{
//			IC_Val1_CH2 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2); // read the first value
//			Is_First_Captured_CH2 = 1;  // set the first captured as true
//			// Now change the polarity to falling edge
//			__HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_2, TIM_INPUTCHANNELPOLARITY_FALLING);
//		}
//		else if (Is_First_Captured_CH2 == 1)   // if the first is already captured
//		{
//			IC_Val2_CH2 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);  // read second value
//			__HAL_TIM_SET_COUNTER(htim, 0);  // reset the counter
//
//			if (IC_Val2_CH2 > IC_Val1_CH2)
//			{
//				Difference_CH2 = IC_Val2_CH2 - IC_Val1_CH2;
//			}
//			else if (IC_Val1_CH2 > IC_Val2_CH2)
//			{
//				Difference_CH2 = (0xffff - IC_Val1_CH2) + IC_Val2_CH2;
//			}
//
//			Distance_CH2 = Difference_CH2 * .034 / 2;
//			Is_First_Captured_CH2 = 0; // set it back to false
//
//			// set polarity to rising edge
//			__HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_2, TIM_INPUTCHANNELPOLARITY_RISING);
//			__HAL_TIM_DISABLE_IT(&htim2, TIM_IT_CC2);
//		}
//	}
//}
//
