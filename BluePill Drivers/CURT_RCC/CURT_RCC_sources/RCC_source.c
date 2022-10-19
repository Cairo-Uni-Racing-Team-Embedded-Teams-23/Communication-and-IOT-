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

#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "../CURT_RCC_headers/RCC_private.h"
#include "../CURT_RCC_headers/RCC_config.h"
#include "../CURT_RCC_headers/RCC_interface.h"

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

    /* Specify clock source used in Control register is PLL*/
    SET_BIT(RCC->CR, RCC_CR_PLL);
    /* Specify PLL multiplication factor and PLL source (HSI/2) or clock from PREDIV1 (HSE/1 or HSE/2)*/

#if RCC_PLL_INPUT == RCC_PLL_IN_HSE_DIV_2
    /* To write to PLLXTPRE*/
    RCC->CFGR = 0;
    WRITE_BIT(RCC->CFGR, RCC_CFGR_PLLXTPRE, 1);
#endif

    WRITE_BIT(RCC->CFGR, RCC_CFGR_PLLMUL, RCC_PLL_MUL_VAL);
    WRITE_BIT(RCC->CFGR, RCC_CFGR_PLLSRC, RCC_PLL_INPUT);

#elif RCC_CLOCK_TYPE == RCC_HSE_CRYSTAL

    /* Specify clock source used in Control register is HSE crystal so no bypass*/
    SET_BIT(RCC->CR, RCC_CR_HSEON);

#elif RCC_CLOCK_TYPE == RCC_HSE_RC
    /* Specify clock source used in Control register is HSE RC so we need to bypass the XTAL1 pin*/
    SET_BIT(RCC->CR, RCC_CR_HSEBYP);
    SET_BIT(RCC->CR, RCC_CR_HSEON);

#elif RCC_CLOCK_TYPE == RCC_HSI
    /* Specify clock source used in Control register is HSI RC*/
    SET_BIT(RCC->CR, RCC_CR_HSI);

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

void RCC_voidEnableClock(u8 Copy_u8BusId, u8 Copy_u8PerId)
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

void RCC_voidDisableClock(u8 Copy_u8BusId, u8 Copy_u8PerId)
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
