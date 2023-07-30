################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include BluePill\ Drivers/CURT_USART/CURT_USART_sources/subdir.mk
-include BluePill\ Drivers/CURT_Systick/CURT_Systick_sources/subdir.mk
-include BluePill\ Drivers/CURT_RCC/CURT_RCC_sources/subdir.mk
-include BluePill\ Drivers/CURT_NVIC/CURT_NVIC_sources/subdir.mk
-include BluePill\ Drivers/CURT_GPIO/CURT_GPIO_sources/subdir.mk
-include BluePill\ Drivers/CURT_CAN/CURT_CAN_sources/subdir.mk
-include BluePill\ Drivers/CURT_AFIO/CURT_AFIO_source/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := BMS_CAN
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
BMS_CAN.elf \

MAP_FILES += \
BMS_CAN.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
BMS_CAN.list \

OBJCOPY_HEX += \
BMS_CAN.hex \

OBJCOPY_BIN += \
BMS_CAN.bin \


# All Target
all: main-build

# Main-build Target
main-build: BMS_CAN.elf secondary-outputs

# Tool invocations
BMS_CAN.elf BMS_CAN.map: $(OBJS) $(USER_OBJS) C:\Users\h4z3m\Desktop\Files\College\CURT\STM32F103C8_Drivers\CURT23_Comm_iot\Deployed\BMS_CAN\STM32F103C8TX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "BMS_CAN.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"C:\Users\h4z3m\Desktop\Files\College\CURT\STM32F103C8_Drivers\CURT23_Comm_iot\Deployed\BMS_CAN\STM32F103C8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="BMS_CAN.map" -Wl,--gc-sections -static -specs=rdimon.specs --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

BMS_CAN.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "BMS_CAN.list"
	@echo 'Finished building: $@'
	@echo ' '

BMS_CAN.hex: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "BMS_CAN.hex"
	@echo 'Finished building: $@'
	@echo ' '

BMS_CAN.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "BMS_CAN.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) BMS_CAN.bin BMS_CAN.elf BMS_CAN.hex BMS_CAN.list BMS_CAN.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
