/**
* 
* @file    : DC Motor (using H-Bridge) Driver Source File (HAL)
* @author  : Alaa Ghita
* @date    : May 2024
* @version : 0.1v
* 
*/

/*Includes*/
#include "DCMotor.h"
#include "DCMotor_cfg.h"
#include "stm32f1xx_hal_gpio.h"
#include "stm32f1xx_hal_tim.h"
#include "stm32f103xb.h"
/**********/

/*Defines*/

/* Check if the peripheral is a valid TIM instance */
#define IS_TIM_ALL_PERIPH(PERIPH) \
    (((PERIPH) == TIM1) || \
     ((PERIPH) == TIM2) || \
     ((PERIPH) == TIM3) || \
     ((PERIPH) == TIM4) || \
     ((PERIPH) == TIM5) || \
     ((PERIPH) == TIM6) || \
     ((PERIPH) == TIM7) || \
     ((PERIPH) == TIM8))

/* Check if the prescaler reload mode is valid */
#define IS_TIM_PRESCALER_RELOAD(RELOAD) \
    (((RELOAD) == TIM_PSCReloadMode_Update) || \
     ((RELOAD) == TIM_PSCReloadMode_Immediate))

/* Prescaler reload mode constants */
#define TIM_PSCReloadMode_Update ((uint16_t)0x0000)
#define TIM_PSCReloadMode_Immediate ((uint16_t)0x0001)
/*********/

/*Types*/
/*******/

/*Variables*/
extern const DCMotorcfg_t DCMotors[_DCMotors_num];
/***********/

/*Static Functions Prototyes*/
void Set_PWM_Frequency(TIM_TypeDef* TIMx, uint32_t frequency);
void Set_PWM_DutyCycle(TIM_TypeDef* TIMx, uint8_t dutyCycle);
void TIM_PrescalerConfig(TIM_TypeDef* TIMx, uint16_t Prescaler, uint16_t TIM_PSCReloadMode);
void TIM_SetCompare1(TIM_TypeDef* TIMx, uint32_t Compare1);
/****************************/

/*APIs Implementation*/
DCMotorErrorStatus_t DCMotor_Init(void)
{
    DCMotorErrorStatus_t Ret_ErrorStatus = DCM_ErrorStatus_OK;
    GPIO_InitTypeDef Loc_CurrentPin;
    uint32_t Loc_u32Counter_1;
    Loc_CurrentPin.Mode = GPIO_MODE_OUTPUT_PP;
    Loc_CurrentPin.Pull = GPIO_NOPULL;
    Loc_CurrentPin.Speed = GPIO_SPEED_FREQ_HIGH;
    for(Loc_u32Counter_1 = 0; Loc_u32Counter_1 < _DCMotors_num-1; Loc_u32Counter_1++)
    {
        Loc_CurrentPin.Pin = DCMotors[Loc_u32Counter_1].Input_1.Pin;
        HAL_GPIO_Init(DCMotors[Loc_u32Counter_1].Input_1.Port, &Loc_CurrentPin);
        Loc_CurrentPin.Pin = DCMotors[Loc_u32Counter_1].Input_2.Pin;
        HAL_GPIO_Init(DCMotors[Loc_u32Counter_1].Input_2.Port, &Loc_CurrentPin);
    }
    // // Initialize Timer 1 for PWM generation
    // TIM_Base_InitTypeDef TIM_TimeBaseInitStruct;
    // TIM_TimeBaseInitStruct.Prescaler = 71; // Set prescaler value
    // TIM_TimeBaseInitStruct.Period = 999; // Set auto-reload value (period)
    // TIM_TimeBaseInitStruct.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    // TIM_TimeBaseInitStruct.CounterMode = TIM_COUNTERMODE_UP;
    // TIM_Base_SetConfig(TIM_CHANNEL_1, &TIM_TimeBaseInitStruct);
    
    // // Calculate duty cycle value for 70%
    // uint16_t dutyCycle = 0.7 * TIM_TimeBaseInitStruct.Period;
    
    // // Configure PWM output channel
    // TIM_OC_InitTypeDef TIM_OCInitStruct;
    // TIM_OCInitStruct.OCMode = TIM_OCMODE_PWM1;
    // TIM_OCInitStruct.OCIdleState = TIM_OCIDLESTATE_SET;
    // TIM_OCInitStruct.Pulse = dutyCycle;
    // TIM_OCInitStruct.OCPolarity = TIM_OCPOLARITY_HIGH;
    // HAL_TIM_OC_ConfigChannel(NULL, &TIM_OCInitStruct,TIM_CHANNEL_1);
    // Loc_CurrentPin.Pin = DCMotors[Loc_u32Counter_1].Enable_Pin.Pin;
    // HAL_GPIO_Init(DCMotors[Loc_u32Counter_1].Enable_Pin.Port, &Loc_CurrentPin);


    return Ret_ErrorStatus;
}


DCMotorErrorStatus_t DCMotor_Start(uint32_t Copy_u32DCMotor)
{
    DCMotorErrorStatus_t Ret_ErrorStatus = DCM_ErrorStatus_OK;
    // Example usage: Set initial frequency and duty cycle
    Set_PWM_Frequency(TIM_CHANNEL_1, 10000); // Set PWM frequency to 1kHz
    Set_PWM_DutyCycle(TIM_CHANNEL_1, 70); // Set duty cycle to 70%
    HAL_GPIO_WritePin(DCMotors[Copy_u32DCMotor].Input_1.Port, DCMotors[Copy_u32DCMotor].Input_1.Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(DCMotors[Copy_u32DCMotor].Input_2.Port, DCMotors[Copy_u32DCMotor].Input_2.Pin, GPIO_PIN_RESET);

    return Ret_ErrorStatus;
}


DCMotorErrorStatus_t DCMotor_Stop(uint32_t Copy_u32DCMotor)
{
    DCMotorErrorStatus_t Ret_ErrorStatus = DCM_ErrorStatus_OK;
    /*Generate 0 signal in the PWM pin*/
    Set_PWM_DutyCycle(TIM_CHANNEL_2, 0);
    return Ret_ErrorStatus;
}


DCMotorErrorStatus_t DCMotor_ReverseDirection(uint32_t Copy_u32DCMotor)
{
    DCMotorErrorStatus_t Ret_ErrorStatus = DCM_ErrorStatus_OK;
    HAL_GPIO_WritePin(DCMotors[Copy_u32DCMotor].Input_1.Port, DCMotors[Copy_u32DCMotor].Input_1.Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(DCMotors[Copy_u32DCMotor].Input_2.Port, DCMotors[Copy_u32DCMotor].Input_2.Pin, GPIO_PIN_SET);
    return Ret_ErrorStatus;
}


DCMotorErrorStatus_t DCMotor_SetSpeed(uint32_t Copy_u32DCMotor, uint32_t Copy_u32SpeedPercentage)
{
    DCMotorErrorStatus_t Ret_ErrorStatus = DCM_ErrorStatus_OK;
    Set_PWM_Frequency(TIM_CHANNEL_2, 1000); // Set PWM frequency to 1kHz
    Set_PWM_DutyCycle(TIM_CHANNEL_2, Copy_u32SpeedPercentage); // Set duty cycle to 50%
    return Ret_ErrorStatus;
}

// Function to set the PWM frequency
void Set_PWM_Frequency(TIM_TypeDef* TIMx, uint32_t frequency) {
    uint16_t prescaler = (SYS_CORE_FREQUENCY / frequency) - 1;
    TIM_PrescalerConfig(TIMx, prescaler, TIM_PSCReloadMode_Update);
}

// Function to set the PWM duty cycle (in percentage)
void Set_PWM_DutyCycle(TIM_TypeDef* TIMx, uint8_t dutyCycle) {
    if (dutyCycle > 100) dutyCycle = 100; // Limit duty cycle to 100%
    uint16_t period = TIMx->ARR; // Read the current period value
    uint16_t pulse = (dutyCycle * period) / 100;
    TIM_SetCompare1(TIMx, pulse);
}

/**
  * @brief  Configures the TIM Prescaler.
  * @param  TIMx: where x can be 1 to 8 to select the TIM peripheral.
  * @param  Prescaler: specifies the Prescaler Register value
  * @param  TIM_PSCReloadMode: specifies the TIM Prescaler Reload mode.
  *   This parameter can be one of the following values:
  *     @arg TIM_PSCReloadMode_Update: The Prescaler is loaded at the update event.
  *     @arg TIM_PSCReloadMode_Immediate: The Prescaler is loaded immediately.
  * @retval None
  */
void TIM_PrescalerConfig(TIM_TypeDef* TIMx, uint16_t Prescaler, uint16_t TIM_PSCReloadMode) {
    /* Check the parameters */
    // assert_param(IS_TIM_ALL_PERIPH(TIMx));
    // assert_param(IS_TIM_PRESCALER_RELOAD(TIM_PSCReloadMode));

    /* Set the prescaler value */
    TIMx->PSC = Prescaler;

    /* Set or reset the UG bit to update the prescaler value immediately */
    if (TIM_PSCReloadMode == TIM_PSCReloadMode_Immediate) {
        /* Generate an update event to update the prescaler value immediately */
        TIMx->EGR = TIM_PSCReloadMode_Immediate;
    }
}

/**
  * @brief  Sets the TIMx Capture Compare1 Register value.
  * @param  TIMx: where x can be 1 to 17 to select the TIM peripheral.
  * @param  Compare1: specifies the Capture Compare1 register new value.
  * @retval None
  */
void TIM_SetCompare1(TIM_TypeDef* TIMx, uint32_t Compare1)
{
    /* Check the parameters */
    // assert_param(IS_TIM_ALL_PERIPH(TIMx));
    
    /* Set the Capture Compare1 Register value */
    TIMx->CCR1 = Compare1;
}



/*********************/