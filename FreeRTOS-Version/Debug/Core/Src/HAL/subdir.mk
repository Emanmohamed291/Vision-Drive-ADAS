################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/HAL/DCMotor.c \
../Core/Src/HAL/DCMotor_cfg.c \
../Core/Src/HAL/bluetooth.c 

OBJS += \
./Core/Src/HAL/DCMotor.o \
./Core/Src/HAL/DCMotor_cfg.o \
./Core/Src/HAL/bluetooth.o 

C_DEPS += \
./Core/Src/HAL/DCMotor.d \
./Core/Src/HAL/DCMotor_cfg.d \
./Core/Src/HAL/bluetooth.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/HAL/%.o Core/Src/HAL/%.su Core/Src/HAL/%.cyclo: ../Core/Src/HAL/%.c Core/Src/HAL/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2 -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-HAL

clean-Core-2f-Src-2f-HAL:
	-$(RM) ./Core/Src/HAL/DCMotor.cyclo ./Core/Src/HAL/DCMotor.d ./Core/Src/HAL/DCMotor.o ./Core/Src/HAL/DCMotor.su ./Core/Src/HAL/DCMotor_cfg.cyclo ./Core/Src/HAL/DCMotor_cfg.d ./Core/Src/HAL/DCMotor_cfg.o ./Core/Src/HAL/DCMotor_cfg.su ./Core/Src/HAL/bluetooth.cyclo ./Core/Src/HAL/bluetooth.d ./Core/Src/HAL/bluetooth.o ./Core/Src/HAL/bluetooth.su

.PHONY: clean-Core-2f-Src-2f-HAL

