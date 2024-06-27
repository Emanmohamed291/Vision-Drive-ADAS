/*
 * bluetooth.h
 *
 *  Created on: Jun 8, 2024
 *      Author: workstation
 */

#ifndef INC_HAL_BLUETOOTH_H_
#define INC_HAL_BLUETOOTH_H_

#include "usart.h"

uint8_t BL_ReadByteSync();
void BL_ReadAsync(uint8_t* data);

#endif /* INC_HAL_BLUETOOTH_H_ */
