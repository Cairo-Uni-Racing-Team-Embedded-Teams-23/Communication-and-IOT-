/*******************************************************************************
 *																				*
 * 	Module			: RCC											     		*
 *																				*
 * 	File Name		: RCC_private.h												*
 *																				*
 * 	Author			: Hazem Montasser										*
 *																				*
 *	Date 			: 12/10/2022												*
 *																				*
 *	Version			: v1.0														*
 * 																				*
 *******************************************************************************/
#ifndef RCC_PRIVATE_H
#define RCC_PRIVATE_H

#include "../../LIB/STD_TYPES.h"

typedef struct
{
  volatile u32 CR;
  volatile u32 CFGR;
  volatile u32 CIR;
  volatile u32 APB2RSTR;
  volatile u32 APB1RSTR;
  volatile u32 AHBENR;
  volatile u32 APB2ENR;
  volatile u32 APB1ENR;
  volatile u32 BDCR;
  volatile u32 CSR;

} RCC_TypeDef;

#define RCC_BASE_ADDRESS 0x40021000

#define RCC ((RCC_TypeDef *)(RCC_BASE_ADDRESS))

/* RCC Control Register bit positions*/
#define RCC_CR_PLL (24)
#define RCC_CR_HSEBYP (18)
#define RCC_CR_HSEON (16)
#define RCC_CR_HSI (0)

/* RCC Configuration register bit positions*/
#define RCC_CFGR_PLLMUL (18)
#define RCC_CFGR_PLLSRC (16)
#define RCC_CFGR_PLLXTPRE (17)

/*




      Configuration Options Macros



*/

// ---------------- PLL Input Multiplication Factor ----------------------------

/**
 * @brief Enum for available PLL multiplication factors.
 */
typedef enum
{
  RCC_PLLMUL_4 = 0b0010,   /*< PLL Input clock x4*/
  RCC_PLLMUL_5 = 0b0011,   /*< PLL Input clock x5*/
  RCC_PLLMUL_6 = 0b0100,   /*< PLL Input clock x6*/
  RCC_PLLMUL_6_5 = 0b1101, /*< PLL Input clock x6.5*/
  RCC_PLLMUL_7 = 0b0101,   /*< PLL Input clock x7*/
  RCC_PLLMUL_8 = 0b0110,   /*< PLL Input clock x8*/
  RCC_PLLMUL_9 = 0b0111,   /*< PLL Input clock x9*/
} RCC_PLLMULValueType;

// ---------------- Clock Type -----------------------------------------------

#define RCC_HSE_CRYSTAL 0
#define RCC_HSE_RC 1
#define RCC_HSI 2
#define RCC_PLL 3

// ---------------- PLL Input --------------------------------------------------

#define RCC_PLL_IN_HSI_DIV_2 0
#define RCC_PLL_IN_HSE_DIV_2 1
#define RCC_PLL_IN_HSE 2

// ------------------------------------------------------------------------------

#endif
