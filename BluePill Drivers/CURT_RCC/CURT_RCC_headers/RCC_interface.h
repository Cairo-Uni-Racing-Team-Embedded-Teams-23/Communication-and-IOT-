/*******************************************************************************
 *																				*
 * 	Module			: RCC														*
 *																				*
 * 	File Name		: RCC_interface.h											*
 *																				*
 * 	Author			: Hazem Montasser   										*
 *																				*
 *	Date 			: 12/10/2022												*
 *																				*
 *	Version			: v1.0														*
 * 																				*
 *******************************************************************************/

#ifndef RCC_INTERFACE_H
#define RCC_INTERFACE_H

#include "../../LIB/STD_TYPES.h"

typedef enum {
	AHB, APB1, APB2
} RCC_Bus;

typedef enum {
	RCC_APB1_TIM2EN = 0,
	RCC_APB1_TIM3EN = 1,
	RCC_APB1_TIM4EN = 2,
	RCC_APB1_TIM5EN = 3,
	RCC_APB1_TIM6EN = 4,
	RCC_APB1_TIM7EN = 5,
	RCC_APB1_TIM12EN = 6,
	RCC_APB1_TIM13EN = 7,
	RCC_APB1_TIM14EN = 8,
	RCC_APB1_WWDGEN = 11,
	RCC_APB1_SPI2EN = 14,
	RCC_APB1_SPI3EN = 15,
	RCC_APB1_USART2EN = 17,
	RCC_APB1_USART3EN = 18,
	RCC_APB1_USART4EN = 19,
	RCC_APB1_USART5EN = 20,
	RCC_APB1_I2C1EN = 21,
	RCC_APB1_I2C2EN = 22,
	RCC_APB1_USBEN = 23,
	RCC_APB1_CANEN = 25,
	RCC_APB1_BKPEN = 27,
	RCC_APB1_PWREN = 28,
	RCC_APB1_DACEN = 29
} RCC_APB1;

typedef enum {
	RCC_APB2_AFIOEN = 0,
	RCC_APB2_IOPAEN = 2,
	RCC_APB2_IOPBEN = 3,
	RCC_APB2_IOPCEN = 4,
	RCC_APB2_IOPDEN = 5,
	RCC_APB2_IOPEEN = 6,
	RCC_APB2_IOPFEN = 7,
	RCC_APB2_IOPGEN = 8,
	RCC_APB2_ADC1EN = 9,
	RCC_APB2_ADC2EN = 10,
	RCC_APB2_TIM1EN = 11,
	RCC_APB2_SPI1EN = 12,
	RCC_APB2_TIM8EN = 13,
	RCC_APB2_USART1EN = 14,
	RCC_APB2_ADC3EN = 15,
	RCC_APB2_TIM9EN = 19,
	RCC_APB2_TIM10EN = 20,
	RCC_APB2_TIM11EN = 21,

} RCC_APB2;

void RCC_voidInitSysClock(void);

void RCC_voidEnableClock(RCC_Bus Copy_u8BusId, u8 Copy_u8PerId);

void RCC_voidDisableClock(RCC_Bus Copy_u8BusId, u8 Copy_u8PerId);

#endif
