/*
 * USART_ptivate.h
 *
 *  Created on: Nov 15, 2022
 *      Author: yasmi
 */

#ifndef USART_PTIVATE_H_
#define USART_PTIVATE_H_

#include "STD_TYPES.h"

/* peripheral bus and enable pin for RCC */
#define USART1_BUS           APB2
#define USART1_ENABLE_PIN    14

#define USART2_BUS           APB1
#define USART2_ENABLE_PIN    17

#define USART3_BUS           APB1
#define USART3_ENABLE_PIN    18

/* USART base address value */
#define USART1_BASE_ADDRESS    0x40013800
#define USART2_BASE_ADDRESS    0x40004400
#define USART3_BASE_ADDRESS    0x40004800

typedef struct{

	volatile u32 USART_SR;
	volatile u32 USART_DR;
	volatile u32 USART_BRR;
	volatile u32 USART_CR1;
	volatile u32 USART_CR2;
	volatile u32 USART_CR3;
	volatile u32 USART_GTPR;

}USART_typedef;

#define USART1 ((USART_typedef*)(USART1_BASE_ADDRESS))
#define USART2 ((USART_typedef*)(USART2_BASE_ADDRESS))
#define USART3 ((USART_typedef*)(USART3_BASE_ADDRESS))

/****************USART registers bit definitions**************/
typedef enum{
	PE,FE,NE,ORE,IDE,RXNE,TC,TXE,LBD,CTS
}USART_SR;

typedef enum{
	SBK,RWU,RE,TE,IDLEIE,RXNEIE,TCIE,TXEIE,PEIE,PS,PCE,WAKE,M,UE
}USART_CR1;


#endif /* USART_PTIVATE_H_ */
