/*************************************************************************************************
 * [MODULE_NAME]:  GPIO_REG.h
 *
 * [DATE CREATED]: 
 *
 * [Author]:       
 *
 * [DESCRIPTION]:  Registers of GPIO
 ************************************************************************************************/
#ifndef GPIO_REG_H_
#define GPIO_REG_H_


#include "STD_TYPES.h"


typedef struct{

	volatile u32 CRL  ;
	volatile u32 CRH  ;
	volatile u32 IDR  ;
	volatile u32 ODR  ;
	volatile u32 BSRR ;
	volatile u32 BRR  ;
	volatile u32 LCKR ;

}GPIO;

#define GPIOA ((volatile GPIO*)0x40010800)
#define GPIOB ((volatile GPIO*)0x40010C00)
#define GPIOC ((volatile GPIO*)0x40011000)



#endif
