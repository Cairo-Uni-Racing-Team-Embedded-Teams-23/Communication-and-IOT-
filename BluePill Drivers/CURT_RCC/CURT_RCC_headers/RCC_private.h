 /*******************************************************************************
 *																				*
 * 	Module			: RCC											     		*
 *																				*
 * 	File Name		: RCC_private.h												*		
 *																				*	
 * 	Author			: *******************										*
 *																				*
 *	Date 			: 12/10/2022												*
 *																				*
 *	Version			: v1.0														*
 * 																				*
 *******************************************************************************/
#ifndef RCC_PRIVATE_H
#define RCC_PRIVATE_H


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

#define RCC ((RCC_TypeDef *) (RCC_BASE_ADDRESS))




/*




			Configuration Options Macros 



*/


// ---------------- Clock Type -----------------------------------------------


#define RCC_HSE_CRYSTAL            0
#define RCC_HSE_RC                 1
#define	RCC_HSI                    2
#define	RCC_PLL                    3



// ---------------- PLL Input -------------------------------------------------- 


#define RCC_PLL_IN_HSI_DIV_2       0
#define RCC_PLL_IN_HSE_DIV_2       1
#define RCC_PLL_IN_HSE             2
	

// ------------------------------------------------------------------------------


#endif  
