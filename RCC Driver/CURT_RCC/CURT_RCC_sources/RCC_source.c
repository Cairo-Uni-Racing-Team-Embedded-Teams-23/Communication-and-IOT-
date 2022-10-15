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


#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "RCC_private.h"
#include "RCC_config.h"
#include "RCC_interface.h"


 /*******************************************************************************
 *	Author :
 *	Function Name : RCC_voidInitSysClock
 *	Function Description :
 *	Initialize and set the micro-controller system clock
 *	Choose the clock depending on HSI,HSE,PLL
 *
 *******************************************************************************/
 
 // 
 
 void Hamamda(void)
{
#if   (RCC_CLOCK_TYPE == RCC_HSE_CRYSTAL)

	/*do not bypass external oscillator*/
	CLR_BIT(RCC->CR,HSEBYP);

	/* enable HSE crystal */
	SET_BIT(RCC->CR,HSEON);

	/* wait until HSE clock is stable */
	while(!GET_BIT(RCC->CR,HSERDY));

	/*adjust the system clock switch */
	SET_BIT(RCC->CFGR, SW0);
	CLR_BIT(RCC->CFGR, SW1);

#elif (RCC_CLOCK_TYPE == RCC_HSE_RC)

	/*bypass external oscillator*/
	SET_BIT(RCC->CR,HSEBYP);

	/* enable HSE RC clock is used */
	SET_BIT(RCC->CR,HSEON);

	/* wait until HSE clock is stable */
	while(!GET_BIT(RCC->CR,HSERDY));

	/*  adjust the system clock switch */
	SET_BIT(RCC->CFGR, SW0);
	CLR_BIT(RCC->CFGR, SW1);


#elif (RCC_CLOCK_TYPE == RCC_HSI)

	/* enable 8MHz internal clock */
	SET_BIT(RCC->CR,HSION);

	/* wait until HSE clock is stable */
	while(!GET_BIT(RCC->CR,HSIRDY));

	/*  adjust the system clock switch */
	CLR_BIT(RCC->CFGR, SW0);
	CLR_BIT(RCC->CFGR, SW1);

#elif (RCC_CLOCK_TYPE == RCC_PLL)

#if   (RCC_PLL_INPUT == RCC_PLL_IN_HSI_DIV_2)

	/* choose HSI/2 clk as input to PLL */
	CLR_BIT(RCC->CFGR,PLLSRC);

#elif (RCC_PLL_INPUT == RCC_PLL_IN_HSE_DIV_2)

	/* choose HSE as input to PLL */
	SET_BIT(RCC->CFGR, PLLSRC);

	/* HSE is divided by 2 */
	SET_BIT(RCC->CFGR, PLLXTPRE);

#elif (RCC_PLL_INPUT == RCC_PLL_IN_HSE)

	/* choose HSE as input to PLL */
	SET_BIT(RCC->CFGR, PLLSRC);

	/*HSE is not divided by 2*/
	CLR_BIT(RCC->CFGR, PLLXTPRE);
#else
#error "INVALID PLL INPUT OPTION"
#endif

	/* adjust the multiplication factor */
	u32 multiplier = RCC_PLL_MUL_VAL - 2  ;  /* the MUL factor is smaller than PLLMUL[0:3] value by 2 */
	RCC->CFGR = (RCC->CFGR & 0xFFC3FFFF) | (multiplier<<PLLMUL0);

/* select PLL as system clock: */
	/* enable PLL clock */
	SET_BIT(RCC->CR, PLLON);

	/* wait until clock is stable */
	while(!GET_BIT(RCC->CR, PLLRDY));

	/*  adjust the system clock switch */
	SET_BIT(RCC->CFGR, SW1);
	CLR_BIT(RCC->CFGR, SW0);

#else
#error "INVALID SYSTEM CLOCK OPTION"
#endif
}

void RCC_voidInitSysClock(void)
{
#if   (RCC_CLOCK_TYPE == RCC_HSE_CRYSTAL)

	/*do not bypass external oscillator*/
	CLR_BIT(RCC->CR,HSEBYP);

	/* enable HSE crystal */
	SET_BIT(RCC->CR,HSEON);

	/* wait until HSE clock is stable */
	while(!GET_BIT(RCC->CR,HSERDY));

	/*adjust the system clock switch */
	SET_BIT(RCC->CFGR, SW0);
	CLR_BIT(RCC->CFGR, SW1);

#elif (RCC_CLOCK_TYPE == RCC_HSE_RC)

	/*bypass external oscillator*/
	SET_BIT(RCC->CR,HSEBYP);

	/* enable HSE RC clock is used */
	SET_BIT(RCC->CR,HSEON);

	/* wait until HSE clock is stable */
	while(!GET_BIT(RCC->CR,HSERDY));

	/*  adjust the system clock switch */
	SET_BIT(RCC->CFGR, SW0);
	CLR_BIT(RCC->CFGR, SW1);


#elif (RCC_CLOCK_TYPE == RCC_HSI)

	/* enable 8MHz internal clock */
	SET_BIT(RCC->CR,HSION);

	/* wait until HSE clock is stable */
	while(!GET_BIT(RCC->CR,HSIRDY));

	/*  adjust the system clock switch */
	CLR_BIT(RCC->CFGR, SW0);
	CLR_BIT(RCC->CFGR, SW1);

#elif (RCC_CLOCK_TYPE == RCC_PLL)

#if   (RCC_PLL_INPUT == RCC_PLL_IN_HSI_DIV_2)

	/* choose HSI/2 clk as input to PLL */
	CLR_BIT(RCC->CFGR,PLLSRC);

#elif (RCC_PLL_INPUT == RCC_PLL_IN_HSE_DIV_2)

	/* choose HSE as input to PLL */
	SET_BIT(RCC->CFGR, PLLSRC);

	/* HSE is divided by 2 */
	SET_BIT(RCC->CFGR, PLLXTPRE);

#elif (RCC_PLL_INPUT == RCC_PLL_IN_HSE)

	/* choose HSE as input to PLL */
	SET_BIT(RCC->CFGR, PLLSRC);

	/*HSE is not divided by 2*/
	CLR_BIT(RCC->CFGR, PLLXTPRE);
#else
#error "INVALID PLL INPUT OPTION"
#endif

	/* adjust the multiplication factor */
	u32 multiplier = RCC_PLL_MUL_VAL - 2  ;  /* the MUL factor is smaller than PLLMUL[0:3] value by 2 */
	RCC->CFGR = (RCC->CFGR & 0xFFC3FFFF) | (multiplier<<PLLMUL0);

/* select PLL as system clock: */
	/* enable PLL clock */
	SET_BIT(RCC->CR, PLLON);

	/* wait until clock is stable */
	while(!GET_BIT(RCC->CR, PLLRDY));

	/*  adjust the system clock switch */
	SET_BIT(RCC->CFGR, SW1);
	CLR_BIT(RCC->CFGR, SW0);

#else
#error "INVALID SYSTEM CLOCK OPTION"
#endif
}
 /*******************************************************************************
 *	Author :
 *	Function Name : RCC_voidEnableClock
 *	Function Description :
 *	Enable the clock for the chosen peripherals
 *
 *
 *******************************************************************************/

void RCC_voidEnableClock(u8 Copy_u8BusId, u8 Copy_u8PerId)
{
	if(Copy_u8PerId <= 31)
		{
			switch(Copy_u8BusId)
			{
			/*enable selected peripheral in AHBENR register*/
			case AHB:
				SET_BIT(RCC->AHBENR, Copy_u8PerId);
				break;

			/*enable selected peripheral in APB1ENR register*/
			case APB1:
				SET_BIT(RCC->APB1ENR, Copy_u8PerId);
				break;

			/*enable selected peripheral in APB2ENR register*/
			case APB2:
				SET_BIT(RCC->APB2ENR, Copy_u8PerId);
			}
		}
		else
		{
			/*  error : greater than the number of supported peripherals  */
		}
}

 /*******************************************************************************
 *	Author :
 *	Function Name : RCC_voidDisableClock
 *	Function Description :
 * Disable the clock for the chosen peripherals
 *
 *******************************************************************************/

void RCC_voidDisableClock(u8 Copy_u8BusId, u8 Copy_u8PerId)
{
	if(Copy_u8PerId <= 31)
		{
			switch(Copy_u8BusId)
			{
			/*disable selected peripheral in AHBENR register*/
			case AHB:
				CLR_BIT(RCC->AHBENR, Copy_u8PerId);
				break;

			/*disable selected peripheral in APB1ENR register*/
			case APB1:
				CLR_BIT(RCC->APB1ENR, Copy_u8PerId);
				break;

			/*disable selected peripheral in APB2ENR register*/
			case APB2:
				CLR_BIT(RCC->APB2ENR, Copy_u8PerId);
			}
		}
		else
		{
			/*  error : greater than the number of supported peripherals  */
		}
}



