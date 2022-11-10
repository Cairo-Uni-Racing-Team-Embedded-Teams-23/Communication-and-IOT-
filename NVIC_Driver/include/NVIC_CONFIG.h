/*******************************************************************************
 *
 * 	Module			: NVIC
 *
 * 	File Name		: NVIC_CONFIG.h
 *
 * 	Author			: Abdelrahman Assem
 *
 *	Date 			:
 *
 *	Version			: v1.0
 *
 *******************************************************************************/
#ifndef NVIC_CONFIG_H_
#define NVIC_CONFIG_H_

/*NVIC groups and subs description*/
#define NVIC_GROUP_4_SUB_0            0x05FA0300
#define NVIC_GROUP_3_SUB_1            0x05FA0400
#define NVIC_GROUP_2_SUB_2            0x05FA0500
#define NVIC_GROUP_1_SUB_3            0x05FA0600
#define NVIC_GROUP_0_SUB_4            0x05FA0700

#define NVIC_GROUP_SUB_DESCRIPTION    NVIC_GROUP_4_SUB_0

#define SCB_AIRCR                     *((volatile u32 *)0xE000ED0C)



#endif /* NVIC_CONFIG_H_ */
