# CURT Communications & IoT 2023 
# SysTick Driver by Hazem Montasser
## Overview

This is a SysTick timer driver implementation for the STM32F103C8 based on ARM Cortex-M3. The SysTick is a 24-bit count-down timer which rolls over to a pre-loaded value once it hits zero. It can be used for simple delay functions or in RTOS and scheduling functions to give periodic alarms.

This driver implements both polling and interrupt techniques for using the timer. There are 2 interrupt modes which can be used as alarms or periodic interrupts as well as busy-wait delay.

# SysTick Driver documentation

### File information
- In CURT_Systick_headers
	1. **SYSTICK_interface.h**: Contains API functions for using the Systick driver
	2. **SYSTICK_private.h**: Contains some definitions and registers used internally within the source
	3. **SYSTICK_reg**: Defines register adresses
	4. **SYSTICK_config.h**: Pre-build configuration file
- In CURT_Systick_sources
	1. **SYSTICK_SOURCE.c**: Source code for the SysTick driver

### How to use this driver

#### Pre-build configuration
#### STK_CLK_SRC
This configuration specifies the clock source for the Systick timer. There are 2 options available:
```c
STK_SRC_AHB      /* Timer source is the AHB clock   */
STK_SRC_AHB_8    /* Timer source is the AHB/8 clock */
```

#### Steps

1. Assuming that the core/system clock has been initialized correctly, the timer clock can be initialized through the init function as shown

```c
STK_init();
```
_The timer is now ready for usage, but at this point, it is halted and has a preload value initialized to the maximum value of 0x00FFFFFF. This function also resets the private variables and the callback function to null._

2. Use to implement a busy wait/blocking delay
```c
STK_setBusyWait(300);  /* Wait for 300 ticks*/
```

3. Use as a single or periodic interrupt. This immediately starts the timer for the specified amount of ticks and attaches the given callback function to the Systick interrupt handler.

_It must be noted that the callback function executes under the Systick_Handler ISR context, so there could be risk of errors or infinite loops if the callback function provided relies on other interrupts with lower priority than the Systick handler._
```c
/* Call 'myCallbackFunc' after 500 ticks */
STK_setIntervalSingle(500, myCallbackFunc)

/* Call 'myCallbackFunc' every 500 ticks */
STK_setIntervalPeriodic(500, myCallbackFunc)
```

4. If the timer is running in periodic mode, we can stop the periodic interrupts using the stop interval function
```c
STK_stopInterval();
```

5. If the timer has been started in the single or periodic modes, we can get elapsed tick count since then or the remaining ticks till the next interrupt.
```c
u32 ticksRemaining = STK_getRemainingTime();

u32 ticksElapsed = STK_ElapsedTime();
```

#### Notes

- A 'tick' definition here refers to a complete countdown of the timer from the value `0x00FFFFFF` to `0x00000000`. Therefore, if used for a millisecond delay function, the correct number of ticks needs to be calculated according to the maximum pre-load value & the frequency of the timer.
- The provided callback function should be as small as possible as it executes under the context of the Systick_Handler.
- The provided callback function must not rely on other interrupts with lower priority than the Systick interrupt.
- If the **core** clock is halted for any reason, the Systick timer also halts as it is a core peripheral.

#### TODO
- Add a function to setup Systick priority in NVIC (??)
- Add a function to change the LOAD value
- Add a function to calibrate the timer
- Allow for more than 1 attached interrupt in any mode
