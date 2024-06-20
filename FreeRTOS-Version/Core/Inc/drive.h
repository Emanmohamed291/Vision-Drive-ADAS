/*
 * drive.h
 *
 *  Created on: Jun 8, 2024
 *      Author: workstation
 */

#ifndef INC_DRIVE_H_
#define INC_DRIVE_H_

void get_data_task(void * pvParameters);
void drive_task(void * pvParameters);
void HCSR04_1_Read_task(void * pvParameters);
void HCSR04_2_Read_task(void * pvParameters);
void blind_spot_task(void * pvParameters);

#endif /* INC_DRIVE_H_ */
