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

#define STK_SRC_AHB             0
#define STK_SRC_AHB_8           1

#define STK_SINGLE_INTERVAL     1
#define STK_PERIOD_INTERVAL     2

typedef enum{

	ENABLE0       ,
	TICKINT      ,
	CLKSOURCE    ,
	COUNTFLAG=16
}CTRL;

void STK_init                (void);
void STK_stopInterval        (void);

u32  STK_getElapsedTime       (void);
u32  STK_getRemainingTime     (void);

void STK_setBusyWait         ( u32 Ticks );

void STK_setIntervalSingle   ( u32 Ticks, void (*copy_ptr)(void) );
void STK_setIntervalPeriodic ( u32 Ticks, void (*copy_ptr)(void) );

#endif
