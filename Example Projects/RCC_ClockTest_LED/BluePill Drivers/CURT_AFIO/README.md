# CURT Communications & IoT 2023 
# AFIO Driver by Hazem Montasser
## Overview

This is the AFIO driver for STM32F103C8 based on Cortex M3. It contains basic functions for setting up external interrupts on any port.

# AFIO Driver documentation

### File information
- In CURT_AFIO_headers
	1. **AFIO_interface.h**: Contains API functions for using the AFIO driver
	2. **AFIO_private.h**: Contains some definitions and registers used internally within the source
	3. **AFIO_reg**: Defines register adresses
	4. **AFIO_config.h**: Pre-build configuration file
- In CURT_AFIO_sources
	1. **AFIO_SOURCE.c**: Source code for the AFIO driver

### How to use this driver

#### Pre-build configuration

N/A

#### Steps

1. Assuming that the core/system clock has been initialized correctly, the AFIO peripheral clock can be initialized through the init function as shown

```c
AFIO_enableClock();
```

2. Setup external interrupt configuration for pins 
```c
/* Maps Pin 11 on Port B to an external interrupt*/
AFIO_setEXTIConfiguration(AFIO_EXTI_LINE11, AFIO_PORTB); 

/* Maps Pin 3 on Port A to an external interrupt*/
AFIO_setEXTIConfiguration(AFIO_EXTI_LINE3, AFIO_PORTA); 

```
