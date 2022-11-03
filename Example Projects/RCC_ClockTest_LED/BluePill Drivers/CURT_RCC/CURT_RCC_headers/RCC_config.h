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
				 RCC_HSI				;High speed RC oscillator Interanl
				 RCC_PLL             	;Phase Lock Loop
	*/

#define RCC_CLOCK_TYPE RCC_PLL

/* Options :


				RCC_PLL_IN_HSI_DIV_2
				RCC_PLL_IN_HSE_DIV_2
				RCC_PLL_IN_HSE


	*/

#if RCC_CLOCK_TYPE == RCC_PLL
#define RCC_PLL_INPUT RCC_PLL_IN_HSE
#endif

/* Options :

	RCC PLL values:
		RCC_PLLMUL_4	; PLL input clock x4;
		RCC_PLLMUL_5	; PLL input clock x5
		RCC_PLLMUL_6	; PLL input clock x6
		RCC_PLLMUL_6_5	; PLL input clock x6.5
		RCC_PLLMUL_7  	; PLL input clock x7
		RCC_PLLMUL_8  	; PLL input clock x8
		RCC_PLLMUL_9  	; PLL input clock x9
*/

#if RCC_CLOCK_TYPE == RCC_PLL
#define RCC_PLL_MUL_VAL RCC_PLLMUL_4
#endif

#endif
