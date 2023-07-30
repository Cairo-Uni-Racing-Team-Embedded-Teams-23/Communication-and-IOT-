/*******************************************************************************
 *																				                                     *
 * 	Module			: RCC											     		                             *
 *																				                                     *
 * 	File Name		: RCC_private.h											                         	 *
 *																				                                     *
 * 	Author			: Hazem Montasser										                           *
 *																				                                     *
 *	Date 			  : 12/10/2022											                             *
 *																				                                     *
 *	Version			: v1.0														                             *
 * 																				                                     *
 *******************************************************************************/
#ifndef RCC_PRIVATE_H
#define RCC_PRIVATE_H

/*******************************************************************************
 *                              Includes                                       *
 *******************************************************************************/

#include "../../LIB/STD_TYPES.h"

#define RCC_BASE_ADDRESS 0x40021000

#define RCC ((RCC_TypeDef *)(RCC_BASE_ADDRESS))

#define RCC_HSI_VALUE (8000000UL)
#define RCC_HSE_VALUE (16000000UL)
/* RCC Control Register bit positions*/
#define RCC_CR_PLL (24)
#define RCC_CR_HSEBYP (18)
#define RCC_CR_HSEON (16)
#define RCC_CR_HSI (0)

/* RCC Configuration register bit positions*/
#define RCC_CFGR_PLLMUL (18)
#define RCC_CFGR_PLLSRC (16)
#define RCC_CFGR_PLLXTPRE (17)
#define RCC_CFGR_SWS (2)

/*
      Configuration Options Macros
*/

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

/*******************************************************************************
 *                              Type definitions                               *
 *******************************************************************************/

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

// ---------------- PLL Input Multiplication Factor ----------------------------

/**
 * @brief Enum for available PLL multiplication factors.
 */
typedef enum
{
  RCC_PLLMULValue_2 = 0000,
  RCC_PLLMULValue_3 = 0001,
  RCC_PLLMULValue_4 = 0010,
  RCC_PLLMULValue_5 = 0011,
  RCC_PLLMULValue_6 = 0100,
  RCC_PLLMULValue_7 = 0101,
  RCC_PLLMULValue_8 = 0110,
  RCC_PLLMULValue_9 = 0111,
  RCC_PLLMULValue_10 = 1000,
  RCC_PLLMULValue_11 = 1001,
  RCC_PLLMULValue_12 = 1010,
  RCC_PLLMULValue_13 = 1011,
  RCC_PLLMULValue_14 = 1100,
  RCC_PLLMULValue_15 = 1101,
  RCC_PLLMULValue_16 = 1110,
  RCC_PLLMULValue_16_ = 1111
} RCC_PLLMULValueType;

#endif
