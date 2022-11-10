# CURT Communications & IoT 2023 

# GPIO Driver by Hazem Montasser
## Overview

This is a GPIO driver implementation for the STM32F103C8 based on ARM Cortex-M3. It contains basic functions like set pin, get pin, setup pin/port. The driver uses the RCC driver for the GPIO_enablePortClock function to enable the clock for any port.

## GPIO Driver documentation

### File information
- In CURT_GPIO_headers
	1. **GPIO_INTERFACE.h**: Contains API functions for using the GPIO driver
	2. **GPIO_PRIVATE.h**: Contains some definitions and registers used internally within the source
	3. **GPIO_REG.h**: Defines register adresses
	4. **GPIO_CONFIG.h**: Pre-build configuration file
- In CURT_GPIO_srouces
	1. **GPIO_SOURCE.c**: Source code for the GPIO driver

### How to use this driver

#### Steps

1. Initialize port clock (assuming system clock has been already set-up correctly)
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
4. Locking GPIO pins/ports
Any pin in the STM32F103C8 can be locked and cannot be modified till the next system reset. This lock prevents any accidental modification on the value of the pin or its configuration.
```c
GPIO_lockPin(GPIO_PortA, PIN5);  /* Locks pin 5 on PORT A*/
GPIO_lockPin(GPIO_PortC, PIN3|PIN2|PIN9);  /* Locks pins 2,3,9 on PORT C*/
GPIO_lockPort(GPIO_PortB);  /* Locks all 16 pins on PORT B */
```

#### Notes

##### Using GPIO_setPinValue and GPIO_writePort when configured as input

- When a pin or port is configured as _INPUT_PULLUP_PULLDOWN_, writing 0 to that pin or port will activate the internal weak **pull-down** resistor.

- When a pin or port is configured as _INPUT_PULLUP_PULLDOWN_, writing 1 to that pin or port will activate the internal weak **pull-up** resistor.

##### Using GPIO_setPortValue_H_L and GPIO_setPortDirection_H_L
- If the position is **NOT** _GPIO_LOW_PORT_, then it is assumed that the higher half of the port is implied.
- These functions are used to configure one half of a specified port.
- When GPIO_setPortValue_H_L is used to set a value on the lower port, only the first 8 bits of the value is used.
Example:
```c
/* Set the lower pins (0-7) of port A to be output push-pull 10MHz*/
GPIO_setPortDirection_H_L(GPIO_PortA, GPIO_LOW_PORT, OUTPUT_SPEED_10MHZ_PP);

/* Write the value 'FF' to pins (8-15) on PORTA, note that lower part of the value is not written*/
GPIO_setPortValue_H_L(GPIO_PortA, GPIO_HIGH_PORT, 0xFFAD);

```