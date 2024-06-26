/**
*
* @file    : Adaptive Cruise Control Module Source File (HAL)
* @author  : Alaa Ghita
* @date    : June 2024
* @version : 0.1v
*
*/

/************************************************Includes************************************************/
#include "stm32f1xx_hal.h"
#include "ErrorStatus.h"
/********************************************************************************************************/



/************************************************Defines*************************************************/
/********************************************************************************************************/



/************************************************Types***************************************************/
typedef enum
{
	Cruise_Control,
	Adaptive_Cruise_Control
}enuACC_Modes;
/********************************************************************************************************/



/************************************************APIs****************************************************/
enuErrorStatus_t ACC_SetMode(enuACC_Modes Copy_enuMode);
enuErrorStatus_t ACC_SetMaxSpeed(uint16_t Copy_u16MaxSpeed);
enuErrorStatus_t ACC_SetMinDistance(uint16_t Copy_u16MinDistance);
void ACC_Satrt(void);
void ACC_Stop(void);
void CruiseControl_Task(void const * argument);
/********************************************************************************************************/






