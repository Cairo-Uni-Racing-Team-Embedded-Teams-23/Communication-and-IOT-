/**
 * @file NVIC_private.h
 * @author Hazem Montasser
 * @brief Header file which defines private macros & definitions used in the driver source
 * @version 0.1
 * @date 2022-11-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/*******************************************************************************
 *                        Includes                                             *
 *******************************************************************************/

#include "../../LIB/STD_TYPES.h"

/*******************************************************************************
 *                       Definitions                                           *
 *******************************************************************************/

/**
 * @brief Defines the number of priority bits used in the STM32F10x MCU
 *
 */
#define NVIC_PRIORITY_BITS (4U)

/**
 * @brief Directives used in NVIC_config.h to specify the vector table location
 *
 */
#define NVIC_VECTOR_TABLE_CODE (1U)
#define NVIC_VECTOR_TABLE_SRAM (0U)

/**
 * @brief Macro for checking if the priority group is valid
 *
 */

#define IS_NVIC_PRIORITY_GROUP(pri_g) (pri_g >= 3U || pri_g <= 7)

/**
 * @brief Vector key used to access SCB AIRCR register
 *
 */
#define SCB_VECTKEY (0x5FA)

/**
 * @brief SCB AIRCR bit positions
 *
 */
#define SCB_AIRCR_VECTKEY_POS (16U)
#define SCB_AIRCR_PRIGRP_POS (8U)
