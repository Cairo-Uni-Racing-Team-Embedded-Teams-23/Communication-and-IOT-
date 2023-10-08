/*******************************************************************************
 *
 * 	Module			: NVIC
 *
 * 	File Name		: NVIC_source.c
 *
 * 	Author			: Abdelrahman Assem
 *
 *	Date 			:
 *
 *	Version			: v1.0
 *
 *******************************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "NVIC_INTERFACE.h"
#include "NVIC_CONFIG.h"
#include "NVIC_PRIVATE.h"


void NVIC_Init(void)
{
	/*Set the SCB_AIRCR with the desired group and sub description*/
	SCB_AIRCR = NVIC_GROUP_SUB_DESCRIPTION;
}
void NVIC_SetPriority(u8 peripheral_interrupt_id,u8 priority)
{
	/*Check whether the id entered is within range or not*/
#if(peripheral_interrupt_id < 60)
	/*Give the priority to the desired peripheral interrupt*/
	NVIC_IPR[peripheral_interrupt_id] = priority;
#else
#error "INVALID PEREPHIRAL ID"
#endif
}
void NVIC_EnableInterrupt(u8 peripheral_interrupt_id)
{
	/*Check whether the id entered is within range or not*/
#if(peripheral_interrupt_id < 60)
	/*Choose to operate on which ISER register*/
	if(peripheral_interrupt_id <= 31)
	{
		/*Enable the interrupt*/
		SET_BIT(NVIC_ISER0,peripheral_interrupt_id);
	}
	else
	{
		/*Reduce the value by 32 to set the corresponding interrupt in ISER1*/
		peripheral_interrupt_id -= 32;
		/*Enable the interrupt*/
		SET_BIT(NVIC_ISER1,peripheral_interrupt_id);
	}
#else
#error "INVALID PEREPHIRAL ID"
#endif
}
void NVIC_DisableInterrupt(u8 peripheral_interrupt_id)
{
	/*Check whether the id entered is within range or not*/
#if(peripheral_interrupt_id < 60)
	/*Choose to operate on which ICER register*/
	if(peripheral_interrupt_id <= 31)
	{
		/*Disable the interrupt*/
		SET_BIT(NVIC_ICER0,peripheral_interrupt_id);
	}
	else
	{
		/*Reduce the value by 32 to clear the corresponding interrupt in ISER1*/
		peripheral_interrupt_id -= 32;
		/*Disable the interrupt*/
		SET_BIT(NVIC_ICER1,peripheral_interrupt_id);
	}
#else
#error "INVALID PEREPHIRAL ID"
#endif
}
void NVIC_SetPendingFlag(u8 peripheral_interrupt_id)
{
	/*Check whether the id entered is within range or not*/
#if(peripheral_interrupt_id < 60)
	/*Choose to operate on which ISPR register*/
	if(peripheral_interrupt_id <= 31)
	{
		/*Set the pending flag*/
		SET_BIT(NVIC_ISPR0,peripheral_interrupt_id);
	}
	else
	{
		/*Reduce the value by 32 to clear the corresponding interrupt in ISPR1*/
		peripheral_interrupt_id -= 32;
		/*Set the pending flag*/
		SET_BIT(NVIC_ISPR1,peripheral_interrupt_id);
	}
#else
#error "INVALID PEREPHIRAL ID"
#endif
}

void NVIC_ClearPendingFlag(u8 peripheral_interrupt_id)
{
	/*Check whether the id entered is within range or not*/
#if(peripheral_interrupt_id < 60)
	/*Choose to operate on which ISPR register*/
	if(peripheral_interrupt_id <= 31)
	{
		/*Clear the pending flag*/
		SET_BIT(NVIC_ICPR0,peripheral_interrupt_id);
	}
	else
	{
		/*Reduce the value by 32 to clear the corresponding interrupt in ISPR1*/
		peripheral_interrupt_id -= 32;
		/*Clear the pending flag*/
		SET_BIT(NVIC_ICPR1,peripheral_interrupt_id);
	}
#else
#error "INVALID PEREPHIRAL ID"
#endif
}

u8 NVIC_GetActiveFlag(u8 peripheral_interrupt_id)
{
	/*Check whether the id entered is within range or not*/
#if(peripheral_interrupt_id < 60)
	/*Local variable to store status of the interrupt*/
	u8 interrupt_status = 0;
	/*Choose to operate on which IABR register*/
	if(peripheral_interrupt_id <= 31)
	{
		/*Get the status of the peripheral interrupt status*/
		interrupt_status = GET_BIT(NVIC_IABR0,peripheral_interrupt_id);
	}
	else
	{
		/*Reduce the value by 32 to get the status of the peripheral interrupt status IABR1*/
		peripheral_interrupt_id -= 32;
		/*Get the status of the peripheral interrupt status*/
		interrupt_status = GET_BIT(NVIC_IABR1,peripheral_interrupt_id);
	}
	return interrupt_status;
#else
#error "INVALID PEREPHIRAL ID"
	return interrupt_status;
#endif

}

