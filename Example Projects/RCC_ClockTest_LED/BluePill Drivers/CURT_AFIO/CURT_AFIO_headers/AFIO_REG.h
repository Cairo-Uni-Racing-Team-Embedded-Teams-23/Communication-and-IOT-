/*************************************************************************************************
 * [MODULE_NAME]:  AFIO_REG.h
 *
 * [DATE CREATED]: 25/10/2022
 *
 * [Author]:       Hazem Montasser
 *
 * [DESCRIPTION]:  All AFIO's Registers
 ************************************************************************************************/
#ifndef AFIO_REG_H_
#define AFIO_REG_H_

/*******************************************************************************
 *                              Includes                                       *
 *******************************************************************************/

#include "../../LIB/STD_TYPES.h"

/*******************************************************************************
 *                           Type definitions                                  *
 *******************************************************************************/

/**
 * @brief Memory map for the AFIO register in STM32F103 Cortex M3
 *
 */
typedef struct
{

	volatile u32 EVCR;
	volatile u32 MAPR;
	volatile u32 EXTICR[4];
	volatile u32 MAPR2;

} AFIO_R;

/*******************************************************************************
 *                              Definitions                                    *
 *******************************************************************************/

/**
 * @brief Defines a pointer with the structure of AFIO_R to be mapped onto
 * 		the memory.
 *
 */
#define AFIO ((volatile AFIO_R *)0x40010000) /*Base Address of AFIO */

#endif
