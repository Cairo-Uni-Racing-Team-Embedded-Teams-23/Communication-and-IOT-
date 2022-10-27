/*************************************************************************************************
 * [MODULE_NAME]:  SYSTICK_Prog.c
 *
 * [DATE CREATED]: 
 *
 * [Author]:      
 *
 * [DESCRIPTION]:  SYSTICK Program
 ************************************************************************************************/

/* include lib Files */

#include "../CURT_Systick_headers/SYSTICK_INTERFACE.h"
#include "../CURT_Systick_headers/SYSTICK_REG.h"
#include "../CURT_Systick_headers/SYSTICK_CONFG.h"
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

static volatile u8 STK_modeOfInterval = 0;
static volatile void (*STK_callBack)(void)=NULLPTR;
static volatile u32 STK_ticksGoal = 0;
static volatile u32 STK_ticks = 0;

void STK_init(void) {

	/* Stop system timer as we are configuring it*/
	SYSTICK->CTRL = 0;
	/* CLKSOURCE
	 * 0: AHB/8
	 * 1: AHB
	 * */
#if STK_CLK_SRC == STK_SRC_AHB_8

#elif STK_CLK_SRC == STK_SRC_AHB

	SET_BIT(SYSTICK->CTRL,CLKSOURCE);

#else
#error "[ERROR] SysTick clock source is incorrectly configured. Please refer to SysTick_CONFIG.h"
#endif
	/* Pre-load the timer with the max value initially */
	SYSTICK->LOAD = STK_MAX_PRELOAD_VALUE;

	/* Reset system timer callback*/
	STK_callBack = NULLPTR;

	/* No mode selected */
	STK_modeOfInterval = SysTick_IntervalMode_NotSpecified;

	/* Reset ticks variable */
	STK_ticks = 0;

}

void STK_stopInterval(void) {

	/* Stop the timer */
	CLR_BIT(SYSTICK->CTRL, 0);

	/* Disable systick interrupt */
	CLR_BIT(SYSTICK->CTRL, TICKINT);

	/* No mode selected */
	STK_modeOfInterval = SysTick_IntervalMode_NotSpecified;

	/* Reset system timer callback*/
	STK_callBack = NULLPTR;

}

u32 STK_getElapsedTime(void) {
	return (u32) (STK_ticks);

}

u32 STK_getRemainingTime(void) {
	return (u32) (STK_ticksGoal - STK_ticks);
}

void STK_setBusyWait(u32 Ticks) {
	/* Stop the timer */
	CLR_BIT(SYSTICK->CTRL, 0);

	/* Disable systick interrupt */
	CLR_BIT(SYSTICK->CTRL, TICKINT);

	/* Start SysTick */
	SET_BIT(SYSTICK->CTRL, 0);
	for (u32 timer_ticks = 0; timer_ticks < Ticks; ++timer_ticks) {

		/* Busy wait on the COUNTFLAG until it is 1 which means the counter has reset*/
		while (!GET_BIT(SYSTICK->CTRL, COUNTFLAG))
			;
	}

}

void STK_setIntervalSingle(u32 Ticks, void (*ptr)(void)) {

	/* Set callback when interval is over */
	STK_callBack = ptr;

	/* Set interval mode to single */
	STK_modeOfInterval = SysTick_IntervalMode_Single;

}

void STK_setIntervalPeriodic(u32 Ticks, void (*ptr)(void)) {

	/* Set callback when interval is over */
	STK_callBack = ptr;

	/* Set interval mode to period */
	STK_modeOfInterval = SysTick_IntervalMode_Period;

	/* Set the ticks variable to a global private variable */
	STK_ticksGoal = Ticks;

	/* Enable interrupt on every tick */
	SET_BIT(SYSTICK->CTRL, TICKINT);

	/* Start SysTick */
	SET_BIT(SYSTICK->CTRL, 0);
}

void SysTick_Handler(void) {

	/* Increment ticks */
	++STK_ticks;

	/* Reset the mode of interval to non specified if it was configured as single interval interrupt
	 * then stop the timer */
	if (STK_modeOfInterval == SysTick_IntervalMode_Single
			&& STK_ticks == STK_ticksGoal) {
		STK_stopInterval();
	}
	/* Callback notification for the user */
	(*STK_callBack)();
}
