/*******************************************************************************
 *																				*
 * 	Module			: RCC														*
 *																				*
 * 	File Name		: RCC_source.c												*		
 *																				*	
 * 	Author			: *******************										*
 *																				*
 *	Date 			: 12/10/2022												*
 *																				*
 *	Version			: v1.0														*
 * 																				*
 *******************************************************************************/


#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "RCC_private.h"
#include "RCC_config.h"
#include "RCC_interface.h"


/*******************************************************************************
 *	Author :
 *	Function Name :
 *	Function Description :
 *
 *
 *******************************************************************************/

void RCC_voidInitSysClock(void){

#if   (RCC_CLOCK_TYPE == RCC_HSE_CRYSTAL)

	CLR_BIT(RCC->CR,HSEBYP);

	SET_BIT(RCC->CR,HSEON);  /* enable HSE crystal */

	while(!GET_BIT(RCC->CR,HSERDY));  /* wait until HSE clock is stable */

	/*  adjust the system clock switch */
	SET_BIT(RCC->CFGR, SW0);
	CLR_BIT(RCC->CFGR, SW1);

#elif (RCC_CLOCK_TYPE == RCC_HSE_RC)

	SET_BIT(RCC->CR,HSEBYP);

	SET_BIT(RCC->CR,HSEON); /* enable HSE RC clock is used */
	while(!GET_BIT(RCC->CR,HSERDY)); /* wait until HSE clock is stable */

	/*  adjust the system clock switch */
	SET_BIT(RCC->CFGR, SW0);
	CLR_BIT(RCC->CFGR, SW1);


#elif (RCC_CLOCK_TYPE == RCC_HSI)
	SET_BIT(RCC->CR,HSION);  /* enable 8MHz internal clock */

	while(!GET_BIT(RCC->CR,HSIRDY)); /* wait until HSE clock is stable */

	/*  adjust the system clock switch */
	CLR_BIT(RCC->CFGR, SW0);
	CLR_BIT(RCC->CFGR, SW1);

#elif (RCC_CLOCK_TYPE == RCC_PLL)

#if   (RCC_PLL_INPUT == RCC_PLL_IN_HSI_DIV_2)
	CLR_BIT(RCC->CFGR,PLLSRC);  /* choose HSI/2 clk as input to PLL */

#elif (RCC_PLL_INPUT == RCC_PLL_IN_HSE_DIV_2)
	SET_BIT(RCC->CFGR, PLLSRC); /* choose HSE as input to PLL */
	SET_BIT(RCC->CFGR, PLLXTPRE); /* HSE is divided by 2 */

#elif (RCC_PLL_INPUT == RCC_PLL_IN_HSE)
	SET_BIT(RCC->CFGR, PLLSRC);/* choose HSE as input to PLL */
	CLR_BIT(RCC->CFGR, PLLXTPRE);
#else
#error "INVALID PLL INPUT OPTION"
#endif

	/* adjust the multiplication factor */
	u32 multiplier = RCC_PLL_MUL_VAL - 2  ;  /* the MUL factor is smaller than PLLMUL[0:3] value by 2 */
	RCC->CFGR = (RCC->CFGR & 0xFFC3FFFF) | (multiplier<<PLLMUL0);

	/* select PLL as system clock: */
	SET_BIT(RCC->CR, PLLON); /* enable PLL clock */
	while(!GET_BIT(RCC->CR, PLLRDY)); /* wait until clock is stable */

	/*  adjust the system clock switch */
	SET_BIT(RCC->CFGR, SW1);
	CLR_BIT(RCC->CFGR, SW0);

#else
#error "INVALID SYSTEM CLOCK OPTION"
#endif
}

/*******************************************************************************
 *	Author :
 *	Function Name :
 *	Function Description :
 *
 *
 *******************************************************************************/

void RCC_voidEnableClock(u8 Copy_u8BusId, u8 Copy_u8PerId){
	if(Copy_u8PerId <= 31)
	{
		switch(Copy_u8BusId)
		{
		case AHB:
			SET_BIT(RCC->AHBENR, Copy_u8PerId);
			break;
		case APB1:
			SET_BIT(RCC->APB1ENR, Copy_u8PerId);
			break;
		case APB2:
			SET_BIT(RCC->APB2ENR, Copy_u8PerId);
		}
	}
	else
	{
		/*  error : beneath the number of supported peripherals  */
	}
}

/*******************************************************************************
 *	Author :
 *	Function Name :
 *	Function Description :
 *
 *
 *******************************************************************************/

void RCC_voidDisableClock(u8 Copy_u8BusId, u8 Copy_u8PerId){
	if(Copy_u8PerId <= 31)
	{
		switch(Copy_u8BusId)
		{
		case AHB:
			CLR_BIT(RCC->AHBENR, Copy_u8PerId);
			break;
		case APB1:
			CLR_BIT(RCC->APB1ENR, Copy_u8PerId);
			break;
		case APB2:
			CLR_BIT(RCC->APB2ENR, Copy_u8PerId);
		}
	}
	else
	{
		/*  error : beneath the number of supported peripherals  */
	}

}



