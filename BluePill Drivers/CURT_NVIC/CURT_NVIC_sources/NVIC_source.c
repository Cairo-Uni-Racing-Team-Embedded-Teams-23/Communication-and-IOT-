#include "../CURT_NVIC_headers/NVIC_interface.h"
#include "../CURT_NVIC_headers/NVIC_reg.h"
#include "../CURT_NVIC_headers/NVIC_private.h"
#include "../CURT_NVIC_headers/NVIC_config.h"

inline void NVIC_enableInterrupts() {
	__asm volatile("CPSIE i");
}
inline void NVIC_disableInterrupts() {
	__asm volatile("CPSID i");
}
inline void NVIC_init() {

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

inline void NVIC_setPriorityGrouping(IRQPgroup_t priorityGroup) {
	if (!IS_NVIC_PRIORITY_GROUP(priorityGroup))
		return;
	/* Copy old register value*/
	u32 reg_val = SCB->AIRCR;
	/* Clear the vectkey & priority group fields only */
	reg_val &= ~((u32) ((0xFFFF << SCB_AIRCR_VECTKEY_POS)
			| (0x7 << SCB_AIRCR_PRIGRP_POS)));
	/* Insert vectkey value to write into the register & insert the priority value*/
	reg_val = (SCB_VECTKEY << SCB_AIRCR_VECTKEY_POS)
			| ((priorityGroup & 0x7UL) << SCB_AIRCR_PRIGRP_POS);
	SCB->AIRCR = reg_val;
}

inline void NVIC_enableIRQ(IRQn_t IRQn) {
	if (IRQn >= 0) {
		NVIC->ISER[(((u32) IRQn) >> 5UL)] = (u32) (1 << (IRQn & 0x1FUL));
	}
}

inline void NVIC_disableIRQ(IRQn_t IRQn) {
	if (IRQn >= 0) {
		NVIC->ICER[(((u32) IRQn) >> 5UL)] = (u32) (1 << (IRQn & 0x1FUL));
	}
}

inline u32 getEnableIRQ(IRQn_t IRQn) {
	if (IRQn >= 0) {
		return (NVIC->ICER[(((u32) IRQn) >> 5UL)] & (u32) (1 << IRQn & 0x1FUL))
				!= 0;
	}
	return 0;
}

inline u32 getActiveIRQ(IRQn_t IRQn) {
	if (IRQn >= 0) {
		return (NVIC->IABR[(((u32) IRQn) >> 5UL)] & (u32) (1 << IRQn & 0x1FUL))
				!= 0;
	}
	return 0;
}

inline void NVIC_setPriority(IRQn_t IRQn, u32 priority) {

	if (IRQn < 0) {
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
		SCB->SHP[(((u32) IRQn & 0xFUL) - 4UL)] = (u32) (priority
				<< (8 - NVIC_PRIORITY_BITS));
	} else {
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
		NVIC->IP[IRQn] = (u32) (priority << (8 - NVIC_PRIORITY_BITS));
	}
}

inline u32 NVIC_getPriority(IRQn_t IRQn) {
	/* Shift back by NVIC priority bits as the most significant bits are
	 the actual priority*/
	if (IRQn < 0) {
		return SCB->SHP[(((u32) IRQn & 0xFUL) - 4UL)]
				>> (8 - NVIC_PRIORITY_BITS);
	} else {
		/* Shift back by NVIC priority bits as the most significant bits are
		 the actual priority*/
		return NVIC->IP[IRQn] >> (8 - NVIC_PRIORITY_BITS);
	}
}

inline void NVIC_setPendingIRQ(IRQn_t IRQn) {
	if (IRQn >= 0) {
		NVIC->ISPR[(((u32) IRQn) >> 5UL)] = (u32) (1 << IRQn & 0x1FUL);
	}
}

inline u32 NVIC_getPendingIRQ(IRQn_t IRQn) {
	if (IRQn >= 0) {
		return (NVIC->ISPR[(((u32) IRQn) >> 5UL)] & (u32) (1 << IRQn & 0x1FUL))
				!= 0;
	}
	return 0;
}

inline void NVIC_clearPendingIRQ(IRQn_t IRQn) {
	if (IRQn >= 0) {
		NVIC->ICPR[(((u32) IRQn) >> 5UL)] = (u32) (1 << IRQn & 0x1FUL);
	}
}
