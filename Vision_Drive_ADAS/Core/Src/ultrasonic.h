/*
 * ultrasonic.h
 *
 *  Created on: Jun 21, 2024
 *      Author: My Self
 */

#ifndef SRC_ULTRASONIC_H_
#define SRC_ULTRASONIC_H_


#include "stm32f1xx_hal.h"

#define LED1_Pin GPIO_PIN_0
#define LED1_GPIO_Port GPIOA
#define LED2_Pin GPIO_PIN_1
#define LED2_GPIO_Port GPIOA
#define Trig1_Pin GPIO_PIN_12
#define Trig1_GPIO_Port GPIOB
#define Trig2_Pin GPIO_PIN_13
#define Trig2_GPIO_Port GPIOB
#define Echo1_Pin GPIO_PIN_8
#define Echo1_GPIO_Port GPIOA
#define Echo2_Pin GPIO_PIN_9
#define Echo2_GPIO_Port GPIOA

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;



float HCSR04_Read_ch1();
float HCSR04_Read_ch2();


#endif /* SRC_ULTRASONIC_H_ */
