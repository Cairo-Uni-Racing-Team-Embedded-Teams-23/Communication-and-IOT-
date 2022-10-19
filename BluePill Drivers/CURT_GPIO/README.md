# CURT Communications & IoT 2023 

## Overview

This is a GPIO driver implementation for the STM32F103C8 based on ARM Cortex-M3. It contains basic functions like set pin, get pin, setup pin/port.
## GPIO Driver documentation

### File information
- In CURT_GPIO_headers
	1. GPIO_INTERFACE.h: Contains API functions for using the GPIO driver
	2. GPIO_PRIVATE.h: Contains some definitions and registers used internally within the source
	3. GPIO_REG.h: Defines register adresses
	4. GPIO_CONFIG.h: Pre-build configuration file
- In CURT_GPIO_srouces
	1. GPIO_SOURCE.c: Source code for the GPIO driver

### How to use this driver

#### Steps

1. Initialize port clock
```c
GPIO_enablePortClock(GPIO_PortA);
```
2. Initialize the pin or port using one of the 16 modes in the GPIO_INTERFACE.h
```c
GPIO_setupPinMode(GPIO_PortA,5,INPUT_PULLUP_PULLDOWN); /* Init pin 5 for input using pulldown config*/
GPIO_setupPortMode(GPIO_PortB,OUTPUT_SPEED_10MHZ_AFOD); /* Init PORT B for output using 10MHz speed and alternate function open drain config*/
```
3. Get or set pins or ports
```c
GPIO_writePort(GPIO_PortB,0xFAB2); /* Write the value 0xFAB2 to PORT B*/

GPIO_togglePinValue(GPIO_PortB,PIN3);  /* Toggle pin 3 on PORT B*/

GPIO_setPinValue(GPIO_PortA, PIN5, LOGIC_HIGH);  /* Write high logic to PORT A*/

uint8 pin_state = GPIO_getPinValue(GPIO_PortA, PIN14);  /* Read the value of pin 14 from PORT A*/
uint16 port_val = GPIO_getPort(GPIO_PortC, PIN14);  /* Read the value PORT C*/
```

#### Notes

- When a pin or port is configured as INPUT_PULLUP_PULLDOWN, writing 0 to that pin or port will activate the internal weak **pull-down** resistor.

- When a pin or port is configured as INPUT_PULLUP_PULLDOWN, writing 1 to that pin or port will activate the internal weak **pull-up** resistor.
