/*******************************************************************************
 *																				*
 * 	Module		: RCC   														*
 *																				*
 * 	File Name	: RCC_source.c  												*
 *																				*
 * 	Author		: Hazem Montasser   										    *
 *																				*
 *	Date 		: 12/10/2022    												*
 *																				*
 *	Version		: v1.0  														*
 * 																				*
 *******************************************************************************/

#include "../../CURT_GPIO/CURT_GPIO_headers/GPIO_INTERFACE.h"
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "../CURT_RCC_headers/RCC_config.h"
#include "../CURT_RCC_headers/RCC_interface.h"
#include "../CURT_RCC_headers/RCC_private.h"

/*******************************************************************************
 *	Author :    Hazem Montasser
 *	Function Name : RCC_voidInitSysClock
 *	Function Description : Initializes the system core clock based on the pre-build
 *  configuration settings in RCC_config.h.
 *
 *******************************************************************************/

void RCC_voidInitSysClock(void)
{
	/* Reset registers in-case they contain garbage or configuration from other code*/
	RCC->CR = 0;
	RCC->CFGR = 0;
	/* Determine clock source selected from RCC_config.h */
#if RCC_CLOCK_TYPE == RCC_PLL

	/* Specify PLL multiplication factor and PLL source (HSI/2) or clock from PREDIV1 (HSE/1 or HSE/2)*/
	u32 mul_val = 0xFFC3FFFF;
	RCC->CFGR &= mul_val;
	mul_val = RCC_PLL_MUL_VAL << RCC_CFGR_PLLMUL;
	RCC->CFGR |= mul_val;

#if RCC_PLL_INPUT == RCC_PLL_IN_HSE

	SET_BIT(RCC->CFGR, RCC_CFGR_PLLSRC);
	CLR_BIT(RCC->CFGR, RCC_CFGR_PLLXTPRE);

#elif RCC_PLL_INPUT == RCC_PLL_IN_HSE_DIV_2
	SET_BIT(RCC->CFGR, RCC_CFGR_PLLSRC);
	SET_BIT(RCC->CFGR, RCC_CFGR_PLLXTPRE);
	/* Enable HSE*/
	SET_BIT(RCC->CR, RCC_CR_HSEON);
	while (!GET_BIT(RCC->CR, 17))
		;
#elif RCC_PLL_INPUT == RCC_PLL_IN_HSI_DIV_2
	CLEAR_BIT(RCC->CFGR, RCC_CFGR_PLLSRC);
#endif

	/* Enable PLL in Control register */
	SET_BIT(RCC->CR, 24);

	/* Wait for PLL ready flag */
	while (GET_BIT(RCC->CR, 25) == 0)
		;

	/* Set SWS[1] for PLL */
	SET_BIT(RCC->CFGR, 1);

#elif RCC_CLOCK_TYPE == RCC_HSE_CRYSTAL

	/* Specify clock source used in Control register is HSE crystal so no bypass*/
	SET_BIT(RCC->CR, RCC_CR_HSEON);

	SET_BIT(RCC->CFGR, 0);
	while (!GET_BIT(RCC->CR, 17))
		;
	/* Set SWS[1] for HSE */
	SET_BIT(RCC->CFGR, 0);
#elif RCC_CLOCK_TYPE == RCC_HSE_RC

	/* Specify clock source used in Control register is HSE RC so we need to bypass the XTAL1 pin*/
	SET_BIT(RCC->CR, RCC_CR_HSEBYP);
	SET_BIT(RCC->CR, RCC_CR_HSEON);
	while (!GET_BIT(RCC->CR, 17))
		;
	/* Set SWS[1] for HSE */
	SET_BIT(RCC->CFGR, 0);
#elif RCC_CLOCK_TYPE == RCC_HSI

	/* Enable internal HSI RC clock */
	SET_BIT(RCC->CR, RCC_CR_HSI);
	while (!GET_BIT(RCC->CR, 1))
		;
#else
#error "[ERROR] Incorrect clock source selected. Please refer to RCC_config.h"
#endif
}

/*******************************************************************************
 *	Author :    Hazem Montasser
 *	Function Name : RCC_voidEnableClock
 *	Function Description :  Enables the clock for a specified peripheral based
 *  on the bus and peripheral ID. Function returns if the peripheral ID exceeds
 *  31.
 *******************************************************************************/

void RCC_voidEnableClock(RCC_Bus Copy_u8BusId, u8 Copy_u8PerId)
{
	/* Invalid peripheral ID*/
	if (Copy_u8PerId > 31)
		return;
	/* Enable clock based on the selected bus*/
	switch (Copy_u8BusId)
	{
	case APB1:
		/* Start clock for peripheral*/
		SET_BIT(RCC->APB1ENR, Copy_u8PerId);
		break;
	case APB2:
		/* Start clock for peripheral*/
		SET_BIT(RCC->APB2ENR, Copy_u8PerId);
		break;
	case AHB:
		/* Start clock for peripheral*/
		SET_BIT(RCC->AHBENR, Copy_u8PerId);
		break;
	default:
		break;
	}
}

/*******************************************************************************
 *	Author :    Hazem Montasser
 *	Function Name : RCC_voidDisableClock
 *	Function Description :  Disables the clock for a specified peripheral based
 *  on the bus and peripheral ID. Function returns if the peripheral ID exceeds
 *  31.
 *******************************************************************************/

void RCC_voidDisableClock(RCC_Bus Copy_u8BusId, u8 Copy_u8PerId)
{
	/* Invalid peripheral ID*/
	if (Copy_u8PerId > 31)
		return;

	switch (Copy_u8BusId)
	{
	case APB1:
		/* Stop clock for peripheral*/
		CLR_BIT(RCC->APB1ENR, Copy_u8PerId);
		break;
	case APB2:
		/* Stop clock for peripheral*/
		CLR_BIT(RCC->APB2ENR, Copy_u8PerId);
		break;
	case AHB:
		/* Stop clock for peripheral*/
		CLR_BIT(RCC->AHBENR, Copy_u8PerId);
		break;
	default:
		break;
	}
}

void RCC_configMCO(RCC_MCOOutput mco_mode)
{
	/* If mode is disable, then disable clock and return*/
	if (mco_mode == RCC_MCO_Src_Disable)
	{
		RCC_voidDisableClock(APB2, RCC_APB2_AFIOEN);
		/* Clear 3 MCO o/p bits*/
		RCC->CFGR &= ~((0b111) << 24);
	}

	/* Enable AFIO peripheral clock before setting up pin */
	RCC_voidEnableClock(APB2, RCC_APB2_AFIOEN);
	/* Setup MCO pin */
	GPIO_setupPinMode(GPIO_PortA, PIN8, OUTPUT_SPEED_50MHZ_AFPP);
	/* Clear 3 MCO o/p bits*/
	RCC->CFGR &= ~((0b111) << 24);
	/* Insert 3 MCO mode bits */
	RCC->CFGR |= ((mco_mode & 0x07) << 24);
}

RCC_SystemClockSource_t RCC_getSystemCoreSource()
{
	switch ((RCC->CFGR >> RCC_CFGR_SWS) & 0b11)
	{
	case 0:
		return RCC_SystemClockSource_HSI;
		break;
	case 1:
		return RCC_SystemClockSource_HSE;
		break;
	case 2:
		return RCC_SystemClockSource_PLL;
		break;
	case 3:
	default:
		return RCC_SystemClockSource_NA;
	}
}

u32 RCC_getSystemCoreClock()
{
	switch ((RCC->CFGR >> RCC_CFGR_SWS) & 0b11)
	{
	case 0:
		return RCC_HSI_VALUE;
		break;
	case 1:
		return RCC_HSE_VALUE;
		break;
	case 2:
		if (GET_BIT(RCC->CFGR, RCC_CFGR_PLLSRC) == 0)
		{
			/* PLL source is HSI/2 */
			return ((u32)RCC_HSI_VALUE / 2);
		}
		else
		{
			/* PLL source is HSE*/
			u32 l_PREDIV1 = CHK_BIT(RCC->CFGR, RCC_CFGR_PLLXTPRE) ? 2 : 1;
			u32 l_PLLMUL_value = ((RCC->CFGR >> RCC_CFGR_PLLMUL) & (0b1111));

			return (RCC_HSE_VALUE * (l_PLLMUL_value + 2)) / l_PREDIV1;
		}
		break;
	case 3:
	default:
		return 0;
	}
}
