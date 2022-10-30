 /*******************************************************************************
 *																				*
 * 	Module			: RCC      													*
 *																				*
 * 	File Name		: RCC_config.h												*		
 *																				*	
 * 	Author			: ******************										*
 *																				*
 *	Date 			: 12/10/2022												*
 *																				*
 *	Version			: v1.0														*
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
				 
#define RCC_CLOCK_TYPE  RCC_PLL


/* Options :    


				RCC_PLL_IN_HSI_DIV_2
				RCC_PLL_IN_HSE_DIV_2
				RCC_PLL_IN_HSE       
				
	
	*/

				



#if RCC_CLOCK_TYPE == RCC_PLL
	#define RCC_PLL_INPUT  RCC_PLL_IN_HSI_DIV_2
#endif



#if RCC_CLOCK_TYPE == RCC_PLL
	#define RCC_PLL_MUL_VAL    2
#endif




#endif