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


/* RCC_CR bits description */
typedef enum{
	HSION,
	HSIRDY,
	HSITRIM0=3,
	HSITRIM1,
	HSITRIM2,
	HSITRIM3,
	HSITRIM4,
	HSICAL0,
	HSICAL1,
	HSICAL2,
	HSICAL3,
	HSICAL4,
	HSICAL5,
	HSICAL6,
	HSICAL7,
	HSEON,
	HSERDY,
	HSEBYP,
	CSSON,
	PLLON=24,
	PLLRDY
}RCC_CR;

/* RCC_CFGR bits description */
typedef enum{
	SW0,
	SW1,
	SWS0,
	SWS1,
	HPRE0,
	HPRE1,
	HPRE2,
	HPRE3,
	PPRE10,
	PPRE11,
	PPRE12,
	PPRE20,
	PPRE21,
	PPRE22,
	ADCPRE0,
	ADCPRE1,
	PLLSRC,
	PLLXTPRE,
	PLLMUL0,
	PLLMUL1,
	PLLMUL2,
	PLLMUL3,
	USBPRE,
	MCO0=24,
	MCO1,
	MCO2
}RCC_CFGR;

/* RCC_CIR bits description */
typedef enum{
	LSIRDYF,
	LSERDYF,
	HSIRDYF,
	HSERDYF,
	PLLRDYF,
	CSSF=7,
	LSIRDYIE,
	LSERDYIE,
	HSIRDYIE,
	HSERDYIE,
	PLLRDYIE,
	LSIRDYC=16,
	LSERDYC,
	HSIRDYC,
	HSERDYC,
	PLLRDYC,
	CSSC=23
}RCC_CIR;

/* RCC_BDCR bits description */
typedef enum{
	LSEON,
	LSERDY,
	LSEBYP,
	RTCSEL0=8,
	RTCSEL1,
	RTCEN=15,
	BDRST
}RCC_BDCR;

/* RCC_CSR bits description */
typedef enum{
	LSION,
	LSIRDY,
	RMVF=24,
	PINRSTF=26,
	PORRSTF,
	SETRSTF,
	IWDGRSTF,
	WWDGRSTF,
	LPWRRSTF
}RCC_CSR;


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
