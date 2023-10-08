/*******************************************************************************
 *
 * 	Module			: NVIC
 *
 * 	File Name		: NVIC_INTERFACE.h
 *
 * 	Author			: Abdelrahman Assem
 *
 *	Date 			:
 *
 *	Version			: v1.0
 *
 *******************************************************************************/

#ifndef NVIC_INTERFACE_H_
#define NVIC_INTERFACE_H_

#include "STD_TYPES.h"

/*******************************************************************************
 *                        Functions Prototypes                                 *
 *******************************************************************************/

void NVIC_Init(void);
void NVIC_SetPriority(u8 peripheral_interrupt_id,u8 priority);
void NVIC_EnableInterrupt(u8 peripheral_interrupt_id);
void NVIC_DisableInterrupt(u8 peripheral_interrupt_id);
void NVIC_SetPendingFlag(u8 peripheral_interrupt_id);
void NVIC_ClearPendingFlag(u8 peripheral_interrupt_id);
u8 NVIC_GetActiveFlag(u8 peripheral_interrupt_id);



#endif /* NVIC_INTERFACE_H_ */
