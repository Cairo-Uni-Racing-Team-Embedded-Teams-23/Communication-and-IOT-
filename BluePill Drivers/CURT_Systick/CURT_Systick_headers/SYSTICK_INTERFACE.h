/*************************************************************************************************
 * [MODULE_NAME]:  SYSTICK_INTERFACE.h
 *
 * [DATE CREATED]: 
 *
 * [Author]:        
 *
 * [DESCRIPTION]:  All # Defines to be used by User & Function's prototype
 ************************************************************************************************/

#ifndef SYSTICK_INTERFACE_H_
#define SYSTICK_INTERFACE_H_
#include "../../LIB/STD_TYPES.h"

#define STK_SRC_AHB             0
#define STK_SRC_AHB_8           1

#define STK_MAX_PRELOAD_VALUE (0x00FFFFFFU)
#define STK_MIN_PRELOAD_VALUE (0x00000001U)

#define STK_COUNTFLAG_READY (0U)

typedef enum {

	ENABLE = 0, TICKINT, CLKSOURCE, COUNTFLAG = 16
} CTRL_Reg;

typedef enum {
	SysTick_ClockSource_AHB, SysTick_ClockSource_AHB_8
} SysTick_ClockSource;

typedef enum {
	SysTick_IntervalMode_Single = 1,
	SysTick_IntervalMode_Period = 2,
	SysTick_IntervalMode_NotSpecified = 3
} SysTick_IntervalMode;

void STK_init(void);
void STK_stopInterval(void);

u32 STK_getElapsedTime(void);
u32 STK_getRemainingTime(void);

void STK_setBusyWait(u32 Ticks);

void STK_setIntervalSingle(u32 Ticks, void (*copy_ptr)(void));
void STK_setIntervalPeriodic(u32 Ticks, void (*copy_ptr)(void));

#endif
