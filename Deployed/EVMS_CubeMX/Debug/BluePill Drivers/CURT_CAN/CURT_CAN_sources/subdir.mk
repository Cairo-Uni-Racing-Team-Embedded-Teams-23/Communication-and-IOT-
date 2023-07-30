################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BluePill\ Drivers/CURT_CAN/CURT_CAN_sources/CAN_source.c 

OBJS += \
./BluePill\ Drivers/CURT_CAN/CURT_CAN_sources/CAN_source.o 

C_DEPS += \
./BluePill\ Drivers/CURT_CAN/CURT_CAN_sources/CAN_source.d 


# Each subdirectory must supply rules for building sources it contributes
BluePill\ Drivers/CURT_CAN/CURT_CAN_sources/CAN_source.o: ../BluePill\ Drivers/CURT_CAN/CURT_CAN_sources/CAN_source.c BluePill\ Drivers/CURT_CAN/CURT_CAN_sources/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"../BluePill Drivers" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"BluePill Drivers/CURT_CAN/CURT_CAN_sources/CAN_source.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-BluePill-20-Drivers-2f-CURT_CAN-2f-CURT_CAN_sources

clean-BluePill-20-Drivers-2f-CURT_CAN-2f-CURT_CAN_sources:
	-$(RM) ./BluePill\ Drivers/CURT_CAN/CURT_CAN_sources/CAN_source.cyclo ./BluePill\ Drivers/CURT_CAN/CURT_CAN_sources/CAN_source.d ./BluePill\ Drivers/CURT_CAN/CURT_CAN_sources/CAN_source.o ./BluePill\ Drivers/CURT_CAN/CURT_CAN_sources/CAN_source.su

.PHONY: clean-BluePill-20-Drivers-2f-CURT_CAN-2f-CURT_CAN_sources

