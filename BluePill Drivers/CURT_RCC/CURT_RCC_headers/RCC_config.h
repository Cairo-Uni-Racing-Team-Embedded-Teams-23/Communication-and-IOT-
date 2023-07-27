/*******************************************************************************
 *																				*
 * 	Module		: RCC	      													*
 *																				*
 * 	File Name	: RCC_config.h													*
 *																				*
 * 	Author		: Hazem Montasser						    					*
 *																				*
 *	Date 		: 12/10/2022													*
 *																				*
 *	Version		: v1.0															*
 * 																				*
 *******************************************************************************/

#ifndef RCC_CONFIG_H
#define RCC_CONFIG_H

#include "RCC_private.h"

/********************	Configurations ********************/

/* Options :

				 RCC_HSE_CRYSTAL     	;High speed Crystal on the external Pin
				 RCC_HSE_RC				;High speed RC oscillator on the External pin
				 RCC_HSI				;High speed RC oscillator Internal
				 RCC_PLL             	;Phase Lock Loop
	*/

#define RCC_CLOCK_TYPE RCC_PLL

/* Options :


				RCC_PLL_IN_HSI_DIV_2
				RCC_PLL_IN_HSE_DIV_2
				RCC_PLL_IN_HSE


	*/

#if RCC_CLOCK_TYPE == RCC_PLL
#define RCC_PLL_INPUT RCC_PLL_IN_HSE_DIV_2
#endif

/* Options :

	RCC PLL values:

	0000: RCC_PLLMULValue_2
	0001: RCC_PLLMULValue_3
	0010: RCC_PLLMULValue_4
	0011: RCC_PLLMULValue_5
	0100: RCC_PLLMULValue_6
	0101: RCC_PLLMULValue_7
	0110: RCC_PLLMULValue_8
	0111: RCC_PLLMULValue_9
	1000: RCC_PLLMULValue_10
	1001: RCC_PLLMULValue_11
	1010: RCC_PLLMULValue_12
	1011: RCC_PLLMULValue_13
	1100: RCC_PLLMULValue_14
	1101: RCC_PLLMULValue_15
	1110: RCC_PLLMULValue_16
	1111: RCC_PLLMULValue_16_
*/

#if RCC_CLOCK_TYPE == RCC_PLL
#define RCC_PLL_MUL_VAL RCC_PLLMULValue_3
#endif

#endif
