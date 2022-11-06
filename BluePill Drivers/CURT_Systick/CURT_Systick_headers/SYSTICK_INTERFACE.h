/*************************************************************************************************
 * [MODULE_NAME]:  SYSTICK_INTERFACE.h
 *
 * [DATE CREATED]: 25/10/2022
 *
 * [Author]:       Hazem Montasser
 *
 * [DESCRIPTION]:  All # Defines to be used by User & Function's prototype
 ************************************************************************************************/

#ifndef SYSTICK_INTERFACE_H_
#define SYSTICK_INTERFACE_H_
#include "../../LIB/STD_TYPES.h"

/*******************************************************************************
 *                              Includes                                       *
 *******************************************************************************/

#include "../../LIB/STD_TYPES.h"

/*******************************************************************************
 *                              Definitions                                    *
 *******************************************************************************/

#define STK_SRC_AHB 			1
#define STK_SRC_AHB_8 			0

#define STK_MAX_PRELOAD_VALUE 	(0x00FFFFFFU)
#define STK_MIN_PRELOAD_VALUE 	(0x00000001U)

#define STK_COUNTFLAG_READY 	(0U)

/*******************************************************************************
 *                              Type definitions                               *
 *******************************************************************************/

/**
 * @brief	Bit positions in the Systick CTRL register
 *
 */
typedef enum
{

	ENABLE1 = 0,
	TICKINT,
	CLKSOURCE,
	COUNTFLAG = 16
} CTRL_Reg;

/**
 * @brief Enum used to choose interval mode for the timer.
 *
 */
typedef enum
{
	SysTick_IntervalMode_Single = 1,
	SysTick_IntervalMode_Period = 2,
	SysTick_IntervalMode_NotSpecified = 3
} SysTick_IntervalMode;


/*******************************************************************************
 *                         Public functions prototypes                         *
 *******************************************************************************/

/**
 * @brief Initializes the Systick by selecting the clock source,
 * 		loading a pre-load value into the LOAD register,
 * 		and setting default values (nulls) for the private global
 * 		variables
 * 
 *	STK_modeOfInterval = SysTick_IntervalMode_NotSpecified
 *	STK_callBack       = NULLPTR
 *  STK_ticks          = 0
 */
void STK_init(void);

/**
 * @brief Stops the timer and disables its interrupt as well as
 * 		resetting the private global variables
 * 
 *	STK_modeOfInterval = SysTick_IntervalMode_NotSpecified
 *	STK_callBack       = NULLPTR
 */
void STK_stopInterval(void);

/**
 * @brief Gets the elapsed time since a single/periodic timer
 * 		interval was started. If the interval was stopped,
 * 		the return value can be garbage.
 *
 * @return u32	Time elapsed since the start of the timer interval
 */
u32 STK_getElapsedTime(void);


/**
 * @brief Gets the remaining time until the next interrupt if
 * 		the timer was started in single/periodic mode.
 * 		If the interval was stopped, the return value can
 * 		be garbage.
 *
 * @return u32	Remaining time till next interrupt
 */
u32 STK_getRemainingTime(void);

/**
 * @brief Starts the timer with the maximum value and waits for the
 * 		timer to reach zero for Ticks number of times. Loops on the
 * 		COUNTFLAG every tick to check if the counter reset.
 *
 * @param Ticks Timer ticks to wait for
 */
void STK_setBusyWait(u32 Ticks);
/**
 * @brief Sets up the timer with the specified number of ticks and
 *		attaches the interrupt to the systick interrupt. The interrupt
 * 		interval is single, so the callback function is called and the interval
 *		stops.

 * - If the function pointer is null, the function does nothing and returns.
 *
 * @param Ticks		Timer ticks to wait for until the interrupt
 * @param ptr		Function pointer of the callback function
 */
void STK_setIntervalSingle(u32 Ticks, void (*ptr)(void));

/**
 * @brief Sets up the timer with the specified number of ticks and
 *		attaches the interrupt to the systick interrupt. The interrupt
 * 		interval is periodic, so the callback function is 
 * 		every Ticks until the STK_stopInterval functions is called.
 * 
 * - If the function pointer is null, the function does nothing and returns.
 *
 * @param Ticks		Timer ticks to wait for until the interrupt
 * @param ptr		Function pointer of the callback function
 */
void STK_setIntervalPeriodic(u32 Ticks, void (*ptr)(void));

#endif
