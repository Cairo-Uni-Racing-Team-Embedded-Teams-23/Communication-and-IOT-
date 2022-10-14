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

typedef struct{

	volatile uint32 CRL  ;
	volatile uint32 CRH  ;
	volatile uint32 IDR  ;
	volatile uint32 ODR  ;
	volatile uint32 BSRR ;
	volatile uint32 BRR  ;
	volatile uint32 LCKR ;

}GPIO;

#define GPIOA ((volatile GPIO*)0x40010800)
#define GPIOB ((volatile GPIO*)0x40010C00)
#define GPIOC ((volatile GPIO*)0x40011000)



#endif
