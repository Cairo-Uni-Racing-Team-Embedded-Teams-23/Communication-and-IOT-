 /*******************************************************************************
 *																				*
 * 	Module			: RCC														*
 *																				*
 * 	File Name		: RCC_interface.h											*		
 *																				*	
 * 	Author			: ******************										*
 *																				*
 *	Date 			: 12/10/2022												*
 *																				*
 *	Version			: v1.0														*
 * 																				*
 *******************************************************************************/

#ifndef RCC_INTERFACE_H
#define RCC_INTERFACE_H 

#include "STD_TYPES.h"


typedef enum {
	AHB,
	APB1,
	APB2	
}RCC_Bus;



void RCC_voidInitSysClock(void);
void RCC_voidEnableClock(RCC_Bus Copy_u8BusId, u8 Copy_u8PerId);
void RCC_voidDisableClock(RCC_Bus Copy_u8BusId, u8 Copy_u8PerId);

#endif
