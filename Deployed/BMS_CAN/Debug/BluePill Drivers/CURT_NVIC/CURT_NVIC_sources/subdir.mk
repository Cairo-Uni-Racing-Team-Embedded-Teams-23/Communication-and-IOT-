################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/h4z3m/Desktop/Files/College/CURT/STM32F103C8_Drivers/CURT23_Comm_iot/BluePill\ Drivers/CURT_NVIC/CURT_NVIC_sources/NVIC_source.c 

OBJS += \
./BluePill\ Drivers/CURT_NVIC/CURT_NVIC_sources/NVIC_source.o 

C_DEPS += \
./BluePill\ Drivers/CURT_NVIC/CURT_NVIC_sources/NVIC_source.d 


# Each subdirectory must supply rules for building sources it contributes
BluePill\ Drivers/CURT_NVIC/CURT_NVIC_sources/NVIC_source.o: C:/Users/h4z3m/Desktop/Files/College/CURT/STM32F103C8_Drivers/CURT23_Comm_iot/BluePill\ Drivers/CURT_NVIC/CURT_NVIC_sources/NVIC_source.c BluePill\ Drivers/CURT_NVIC/CURT_NVIC_sources/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -I"C:/Users/h4z3m/Desktop/Files/College/CURT/STM32F103C8_Drivers/CURT23_Comm_iot/BluePill Drivers" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"BluePill Drivers/CURT_NVIC/CURT_NVIC_sources/NVIC_source.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-BluePill-20-Drivers-2f-CURT_NVIC-2f-CURT_NVIC_sources

clean-BluePill-20-Drivers-2f-CURT_NVIC-2f-CURT_NVIC_sources:
	-$(RM) ./BluePill\ Drivers/CURT_NVIC/CURT_NVIC_sources/NVIC_source.cyclo ./BluePill\ Drivers/CURT_NVIC/CURT_NVIC_sources/NVIC_source.d ./BluePill\ Drivers/CURT_NVIC/CURT_NVIC_sources/NVIC_source.o ./BluePill\ Drivers/CURT_NVIC/CURT_NVIC_sources/NVIC_source.su

.PHONY: clean-BluePill-20-Drivers-2f-CURT_NVIC-2f-CURT_NVIC_sources

