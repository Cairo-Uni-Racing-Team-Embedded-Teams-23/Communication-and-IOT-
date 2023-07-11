/**
 * @file NVIC_source.c
 * @author Hazem Montasser
 * @brief NVIC driver source file.
 * @version 0.1
 * @date 2022-11-10
 *
 * @copyright Copyright (c) 2022
 *
 */

/*******************************************************************************
 *                        Includes                                             *
 *******************************************************************************/

#include "../CURT_NVIC_headers/NVIC_interface.h"
#include "../CURT_NVIC_headers/NVIC_reg.h"
#include "../CURT_NVIC_headers/NVIC_private.h"
#include "../CURT_NVIC_headers/NVIC_config.h"

/*******************************************************************************
 *                       Public functions defintions                           *
 *******************************************************************************/
/*
 *	A very common theme in algorithms in this driver is a a lot of shifting &
 *  IRQ number manipulation to reach the correct position in the register.
 *
 *  IRQn
 *  0-31  ISER[0] ICER[0] ISPR[0] ICPR[0] IABR[0]
 *  32-63 ISER[1] ICER[1] ISPR[1] ICPR[1] IABR[1]
 *  64-67 ISER[2] ICER[2] ISPR[2] ICPR[2] IABR[2]
 *	Therefore, to reach the correct index based on IRQn, we
 *	can notice that each register index depends on the IRQn by the following relation:
 *		IRQn < 32 -> bit6,5 = 00 Ex.: IRQn = 23 = 0b 0 [00] 10111
 * 		IRQn < 64 -> bit6,5 = 01 Ex.: IRQn = 47 = 0b 0 [01] 01111
 * 		IRQn < 68 -> bit6,5 = 10 Ex.: IRQn = 65=  0b 0 [10] 00001
 * Using that relation, we only need to shift the IRQn by 5 bits to obtain the correct
 * index.
 *
 * More notes:
 * - Masking with 1F because IRQn value must be 7 bits not more
 * - Shifting priority by 8 - NVIC_PRIORITY_BITS because NVIC implements its priority
 * 		in the most significant bits like in the case of STM32, only the higher
 * 		4 bits are used.
 *
 */

void NVIC_enableInterrupts()
{
	__asm volatile("CPSIE i");
}
void NVIC_disableInterrupts()
{
	__asm volatile("CPSID i");
}
void NVIC_init()
{

#if NVIC_VECTOR_TABLE_LOC == NVIC_VECTOR_TABLE_CODE
	/* Clear the first 8 bits of the table offset & bit 29 = 0 for code vector table*/
	u32 table_offset = (NVIC_VECTOR_TABLE_OFFSET & 0x000FFF00 << 9);
	SCB->VTOR = table_offset;
#elif NVIC_VECTOR_TABLE_LOC == NVIC_VECTOR_TABLE_SRAM
	/* Clear the first 8 bits of the table offset & bit 29 = 1 for SRAM vector table*/
	u32 table_offset = (NVIC_VECTOR_TABLE_OFFSET & 0x000FFF00 << 9) | (1 << 29);
	SCB->VTOR = table_offset;
#else
#error "[ERROR] Incorrect vector table configuration selected. See NVIC_config.h."
#endif
}

void NVIC_setPriorityGrouping(IRQPgroup_t priorityGroup)
{
	if (!IS_NVIC_PRIORITY_GROUP(priorityGroup))
		return;
	/* Copy old register value*/
	u32 reg_val = SCB->AIRCR;
	/* Clear the vectkey & priority group fields only */
	reg_val &= ~((u32)((0xFFFF << SCB_AIRCR_VECTKEY_POS) | (0x7 << SCB_AIRCR_PRIGRP_POS)));
	/* Insert vectkey value to write into the register & insert the priority value*/
	reg_val = (SCB_VECTKEY << SCB_AIRCR_VECTKEY_POS) | ((priorityGroup & 0x7UL) << SCB_AIRCR_PRIGRP_POS);
	SCB->AIRCR = reg_val;
}

void NVIC_enableIRQ(IRQn_t IRQn)
{
	if (IRQn >= 0)
	{
		NVIC->ISER[(((u32)IRQn) >> 5UL)] = (u32)(1 << (IRQn & 0x1FUL));
	}
}

void NVIC_disableIRQ(IRQn_t IRQn)
{
	if (IRQn >= 0)
	{
		NVIC->ICER[(((u32)IRQn) >> 5UL)] = (u32)(1 << (IRQn & 0x1FUL));
	}
}

u32 getEnableIRQ(IRQn_t IRQn)
{
	if (IRQn >= 0)
	{
		return (NVIC->ICER[(((u32)IRQn) >> 5UL)] & (u32)(1 << IRQn & 0x1FUL)) != 0;
	}
	return 0;
}

u32 getActiveIRQ(IRQn_t IRQn)
{
	if (IRQn >= 0)
	{
		return (NVIC->IABR[(((u32)IRQn) >> 5UL)] & (u32)(1 << IRQn & 0x1FUL)) != 0;
	}
	return 0;
}

void NVIC_setPriority(IRQn_t IRQn, u32 priority)
{

	if (IRQn < 0)
	{
		/* For system interrupts such as systick, we must write their priority to
		 System Handler Priority array
		 - Each byte is the priority of a system interrupt
		 - The IRQn will be negative, so we must ensure it is unsigned
		 - (u32)IRQn -> Number becomes abs(IRQn)
		 - (u32)IRQn&0xF -> Mask first 4 bits as we just need those since
		 the array is from 0-15
		 - (u32)IRQn&0xF-4 -> Subtract 4 because each IRQn number corresponds to 1 byte
		 in the array of 4bytes register
		 Ex: Usage fault -> -10 -> (u32)(-10)&0xF  = 6
		 6-4 = 2 = Index of usage fault interrupt priority.
		 */
		SCB->SHP[(((u32)IRQn & 0xFUL) - 4UL)] = (u32)(priority
													  << (8 - NVIC_PRIORITY_BITS));
	}
	else
	{
		/* Priority -> value from 0-15 (STM implements only 16 priority levels)
		 The main priority field is a byte in an array of 32 bit registers: the IPRn
		 array
		 IPR0 -> IP[3] IP[2] IP[1] IP[0] -> Each IP[x] is the priority for interrupt #x
		 Example: IP[2] = (0x70) -> Priority of interrupt #2 is 7
		 To set the value in the correct field we must:
		 1. Find the correct array number
		 2. Shift the priority by 4 bits
		 3. Insert the priority into IP[y] y = IRQn
		 */
		NVIC->IP[IRQn] = (u32)(priority << (8 - NVIC_PRIORITY_BITS));
	}
}

u32 NVIC_getPriority(IRQn_t IRQn)
{
	/* Shift back by NVIC priority bits as the most significant bits are
	 the actual priority*/
	if (IRQn < 0)
	{
		return SCB->SHP[(((u32)IRQn & 0xFUL) - 4UL)] >> (8 - NVIC_PRIORITY_BITS);
	}
	else
	{
		/* Shift back by NVIC priority bits as the most significant bits are
		 the actual priority*/
		return NVIC->IP[IRQn] >> (8 - NVIC_PRIORITY_BITS);
	}
}

void NVIC_setPendingIRQ(IRQn_t IRQn)
{
	/* We can only pend non fault interrupts & maskable ones */
	if (IRQn >= 0)
	{
		/* IRQn >> 5 -> Shifting by 5 to determine in which
			array the interrupt belongs to
			Example: IRQn =
			*/
		NVIC->ISPR[(((u32)IRQn) >> 5UL)] = (u32)(1 << IRQn & 0x1FUL);
	}
}

u32 NVIC_getPendingIRQ(IRQn_t IRQn)
{
	if (IRQn >= 0)
	{
		return (NVIC->ISPR[(((u32)IRQn) >> 5UL)] & (u32)(1 << IRQn & 0x1FUL)) != 0;
	}
	return 0;
}

void NVIC_clearPendingIRQ(IRQn_t IRQn)
{
	if (IRQn >= 0)
	{
		NVIC->ICPR[(((u32)IRQn) >> 5UL)] = (u32)(1 << IRQn & 0x1FUL);
	}
}
