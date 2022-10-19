# CURT Communications & IoT 2023 

## Overview

This is a RCC driver implementation for the STM32F103C8 based on ARM Cortex-M3. It contains basic functions start system clock, start or stop clock on AHB, APB1, APB2 buses.
## RCC Driver documentation

### File information
- In CURT_RCC_headers
	1. RCC_interface.h: Contains API functions for using the RCC driver
	2. RCC_private.h: Contains some definitions and registers used internally within the source
	3. RCC_reg: Defines register adresses
	4. RCC_config.h: Pre-build configuration file
- In CURT_RCC_srouces
	1. RCC_SOURCE.c: Source code for the RCC driver

### How to use this driver

#### Pre-build configuration

#### RCC_CLOCK_TYPE

The main system clock that is used for the core. Multiple options are available based on the hardware configuration (external crystal/internal RC/PLL):
```c
RCC_HSE_CRYSTAL        ;High speed Crystal on the external Pin

RCC_HSE_RC             ;High speed RC oscillator on the External pin

RCC_HSI                ;High speed RC oscillator Interanl

RCC_PLL                ;Phase Lock Loop

```

##### RCC_PLL_INPUT 
This is the PLL input clock. The available options for this are:
```c
RCC_PLL_IN_HSI_DIV_2
RCC_PLL_IN_HSE_DIV_2
RCC_PLL_IN_HSE
```

##### RCC_PLL_MUL_VAL
It is the PLL multiplication factor whether it is fed from HSE or HSI. The available options are selected from an enumuration:
```c
RCC_PLLMUL_4    /*PLL input clock x4;*/
RCC_PLLMUL_5    /*PLL input clock x5*/
RCC_PLLMUL_6    /*PLL input clock x6*/
RCC_PLLMUL_6_5  /* PLL input clock x6.5*/
RCC_PLLMUL_7    /* PLL input clock x7*/
RCC_PLLMUL_8    /* PLL input clock x8*/
RCC_PLLMUL_9    /* PLL input clock x9*/
*```


#### Steps

1. Initialize system clock. This selects the clock for the core based on the selected clock from the pre-build configuration file in RCC_config.h. 

```c
RCC_voidInitSysClock();
```

2. Start or stop the clock for a peripheral on the system buses
```c
RCC_voidEnableClock(APB2, 4);

RCC_voidDisableClock(AB1, 12);
```
#### Notes