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

#include "SYSTICK_INTERFACE.h"
#include "SYSTICK_REG.h"
#include "SYSTICK_CONFG.h"

static u8 STK_modeOfInterval=0;
static void(*STK_callBack)(void);


void STK_init (void){

}

void STK_stopInterval        (void){

}

u32 STK_getElapsedTime(void) {

	
}
u32 STK_getRemainingTime(void) {

	
}

void STK_setBusyWait( u32 Ticks )
{
	

void STK_setIntervalSingle   ( u32 Ticks, void (*ptr)(void) ){


    

}
void STK_setIntervalPeriodic ( u32 Ticks, void (*ptr)(void) ){



}

void SysTick_Handler (void) {


}
