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
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "SYSTICK_INTERFACE.h"
#include "SYSTICK_REG.h"
#include "SYSTICK_CONFG.h"


static u8 STK_modeOfInterval=0;
/* 0-->STK_setIntervalSingle is called
 * 1-->STK_setIntervalPeriodic is called
 */

static void(*STK_callBack)(void);


void STK_init (void){

	/* reset SYSTICK control register */
	SYSTICK->CTRL = 0x00000004;

	/* clear the current value */
	CLEAR_REG(SYSTICK->VAL);

	/* define the clock source */
	switch(STK_CLK_SRC)
	{
	case STK_SRC_AHB_8:
		CLR_BIT(SYSTICK->CTRL,CLKSOURCE);
		break;
	case STK_SRC_AHB:
		SET_BIT(SYSTICK->CTRL,CLKSOURCE);
	}
}

void STK_stopInterval        (void){

	SYSTICK->CTRL &= ~(1<<TICKINT) & ~(1<<ENABLE0);
}

u32 STK_getElapsedTime(void) {
	return SYSTICK->LOAD - SYSTICK->VAL;
}
u32 STK_getRemainingTime(void) {
	return SYSTICK->VAL;
}

void STK_setBusyWait( u32 Ticks ){

	/* update the RELOAD value register */
	SYSTICK->LOAD = Ticks;

	/* enable SYSTICK */
	SET_BIT(SYSTICK->CTRL, ENABLE0);

	/* PULL until counter reaches 0 */
	while(!GET_BIT(SYSTICK->CTRL,COUNTFLAG));

	/* disable SYSTICK */
	CLR_BIT(SYSTICK->CTRL, ENABLE0);

}
void STK_setIntervalSingle   ( u32 Ticks, void (*ptr)(void) ){

	/* update the RELOAD value register */
	SYSTICK->LOAD = Ticks;

	/* adjust the call back function */
	STK_callBack = *ptr;

	/* adjust the modeOfInterval flag for single mode */
	STK_modeOfInterval = 0;

	/* enable SYSTICK and SYSTICK interrupt */
	SYSTICK->CTRL |= (1<<TICKINT) | (1<<ENABLE0);

}
void STK_setIntervalPeriodic ( u32 Ticks, void (*ptr)(void) ){

	/* update the RELOAD value register */
	SYSTICK->LOAD = Ticks;

	/* adjust the call back function */
	STK_callBack = *ptr;

	/* adjust the modeOfInterval flag for periodic mode */
	STK_modeOfInterval = 1;

	/* enable SYSTICK and SYSTICK interrupt */
	SYSTICK->CTRL |= (1<<TICKINT) | (1<<ENABLE0);


}

void SysTick_Handler (void) {

	switch (STK_modeOfInterval) {

	case 0: /* single interval */
		STK_callBack();
		STK_stopInterval();
		break;

	case 1: /* periodic interval */
		STK_callBack();

	}
}

