/*************************************************************************************************
 * [MODULE_NAME]:  AFIO.c
 *
 * [DATE CREATED]: 25/10/2022
 *
 * [Author]:       Hazem Montasser
 *
 * [DESCRIPTION]:  Source file for the AFIO driver
 ************************************************************************************************/

/*******************************************************************************
 *                              Includes                                       *
 *******************************************************************************/

#include "../CURT_AFIO_headers/AFIO_INTERFACE.h"
#include "../CURT_AFIO_headers/AFIO_REG.h"
#include "../../CURT_RCC/CURT_RCC_headers/RCC_interface.h"

/*******************************************************************************
 *                     Public functions definitions                            *
 *******************************************************************************/

void AFIO_setEXTIConfiguration(u8 EXTI_Line, u8 PortMap)
{
	/*
	 * For the selected EXTI line:
	 * 1. Clear the 4 bits for the EXTI line we need in EXTICR.
	 * 	  Since each line has 4 bits, we shift the bits we want by 4, so we
	 *    multiply EXTI line by 4 (by shifting 2)
	 * 2. Insert the masked(we only need lower 4 bits, so we ensure we clear the upper 4)
	 *    port map bits into the 4 bits we just cleared
	 */

	/* Sanitize input since we just need the lower 4 bits anyway */
	EXTI_Line = (EXTI_Line & 0x0F);
	PortMap = (PortMap & 0x0F);

	if (EXTI_Line < AFIO_EXTI_LINE4)
	{
		AFIO->EXTICR[0] &= ~((0b1111) << (EXTI_Line << 2));
		AFIO->EXTICR[0] |= (PortMap << (EXTI_Line << 2));
	}
	else if (EXTI_Line < AFIO_EXTI_LINE8)
	{
		AFIO->EXTICR[1] &= ~((0b1111) << (EXTI_Line << 2));
		AFIO->EXTICR[1] |= (PortMap << (EXTI_Line << 2));
	}
	else if (EXTI_Line < AFIO_EXTI_LINE12)
	{
		AFIO->EXTICR[2] &= ~((0b1111) << (EXTI_Line << 2));
		AFIO->EXTICR[2] |= (PortMap << (EXTI_Line << 2));
	}
	else if (EXTI_Line <= AFIO_EXTI_LINE15)
	{
		AFIO->EXTICR[3] &= ~((0b1111) << (EXTI_Line << 2));
		AFIO->EXTICR[3] |= (PortMap << (EXTI_Line << 2));
	}
	else
	{
		return;
	}
}

void AFIO_enableClock(void)
{

	/* Enable AFIO Clock */
	RCC_voidEnableClock(APB2, RCC_APB2_AFIOEN);
}
