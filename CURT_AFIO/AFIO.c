/*************************************************************************************************
 * [MODULE_NAME]:  AFIO_Prog.c
 *
 * [DATE CREATED]: 10/30/2022
 *
 * [Author]:   yasmine sayed
 *
 * [DESCRIPTION]:  AFIO Program
 ************************************************************************************************/

/* Include LIB Files */

#include "AFIO_INTERFACE.h"
#include "AFIO_REG.h"
#include "AFIO_PRIVATE.h"

/* include RCC interface file */
#include "RCC_interface.h"


void AFIO_setEXTIConfiguration( u8 EXTI_Line , u8 PortMap )
{
	/* selecting source input for EXTI_LINE external interrupt */
	if      (EXTI_Line<4)
	{
		AFIO->EXTICR[0] = (AFIO->EXTICR[0] & ~(0b1111)<<(EXTI_Line*4)) | (PortMap<<(EXTI_Line*4)) ;
	}
	else if (EXTI_Line<8)
	{
		AFIO->EXTICR[1] = (AFIO->EXTICR[1] & ~(0b1111)<<((EXTI_Line-4)*4)) | (PortMap<<((EXTI_Line-4)*4)) ;
	}
	else if (EXTI_Line<12)
	{
		AFIO->EXTICR[2] = (AFIO->EXTICR[2] & ~(0b1111)<<((EXTI_Line-8)*4)) | (PortMap<<((EXTI_Line-8)*4)) ;
	}
	else if (EXTI_Line<16)
	{
		AFIO->EXTICR[3] = (AFIO->EXTICR[3] & ~(0b1111)<<((EXTI_Line-12)*4)) | (PortMap<<((EXTI_Line-12)*4)) ;
	}

}


void AFIO_enableClock (void) {

	/* Enable AFIO Clock */
	RCC_voidEnableClock(AFIO_BUS,AFIO_EN_BIT);

}
