/**
 * @file CRC_private.h
 * @author Hazem Montasser (h4z3m.private@gmail.com)
 * @brief  Header file which defines private macros & definitions used in the driver source
 * @version 0.1
 * @date 2023-08-14
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef CRC_PRIVATE_H
#define CRC_PRIVATE_H

/*******************************************************************************
 *                              Includes                                       *
 *******************************************************************************/

#include "../../LIB/STD_TYPES.h"

/*******************************************************************************
 *                              Definitions                                    *
 *******************************************************************************/

#define CRC_BASE_ADDRESS (0x40023000)

/*******************************************************************************
 *                              Type definitions                               *
 *******************************************************************************/

/**
 * @brief CRC registers
 *
 */
typedef struct {
	volatile u32 DR;
	volatile u32 IDR;
	volatile u32 CR;

} CRC_Typedef;

#define CRC ((CRC_Typedef *)CRC_BASE_ADDRESS)

#endif
