################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/h4z3m/Desktop/Files/College/CURT/STM32F103C8_Drivers/CURT23_Comm_iot/BluePill\ Drivers/CURT_GPIO/CURT_GPIO_sources/GPIO_SOURCE.c 

OBJS += \
./BluePill\ Drivers/CURT_GPIO/CURT_GPIO_sources/GPIO_SOURCE.o 

C_DEPS += \
./BluePill\ Drivers/CURT_GPIO/CURT_GPIO_sources/GPIO_SOURCE.d 


# Each subdirectory must supply rules for building sources it contributes
BluePill\ Drivers/CURT_GPIO/CURT_GPIO_sources/GPIO_SOURCE.o: C:/Users/h4z3m/Desktop/Files/College/CURT/STM32F103C8_Drivers/CURT23_Comm_iot/BluePill\ Drivers/CURT_GPIO/CURT_GPIO_sources/GPIO_SOURCE.c BluePill\ Drivers/CURT_GPIO/CURT_GPIO_sources/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I../Inc -I"C:/Users/h4z3m/Desktop/Files/College/CURT/STM32F103C8_Drivers/CURT23_Comm_iot/BluePill Drivers" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"BluePill Drivers/CURT_GPIO/CURT_GPIO_sources/GPIO_SOURCE.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-BluePill-20-Drivers-2f-CURT_GPIO-2f-CURT_GPIO_sources

clean-BluePill-20-Drivers-2f-CURT_GPIO-2f-CURT_GPIO_sources:
	-$(RM) ./BluePill\ Drivers/CURT_GPIO/CURT_GPIO_sources/GPIO_SOURCE.cyclo ./BluePill\ Drivers/CURT_GPIO/CURT_GPIO_sources/GPIO_SOURCE.d ./BluePill\ Drivers/CURT_GPIO/CURT_GPIO_sources/GPIO_SOURCE.o ./BluePill\ Drivers/CURT_GPIO/CURT_GPIO_sources/GPIO_SOURCE.su

.PHONY: clean-BluePill-20-Drivers-2f-CURT_GPIO-2f-CURT_GPIO_sources

