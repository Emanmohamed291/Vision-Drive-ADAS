/*
 * ultrasonic.h
 *
 *  Created on: Jun 21, 2024
 *      Author: My Self
 */

#ifndef SRC_ULTRASONIC_H_
#define SRC_ULTRASONIC_H_


#include "stm32f1xx_hal.h"

#define Trig1_Pin GPIO_PIN_12
#define Trig1_GPIO_Port GPIOB

extern TIM_HandleTypeDef htim1;



float HCSR04_Read_ch1();
float HCSR04_Read_ch2();


#endif /* SRC_ULTRASONIC_H_ */
