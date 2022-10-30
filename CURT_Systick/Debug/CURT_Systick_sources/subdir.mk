################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CURT_Systick_sources/SYSTICK.c 

OBJS += \
./CURT_Systick_sources/SYSTICK.o 

C_DEPS += \
./CURT_Systick_sources/SYSTICK.d 


# Each subdirectory must supply rules for building sources it contributes
CURT_Systick_sources/%.o: ../CURT_Systick_sources/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM GNU C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m3 -mthumb -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections  -g3 -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


