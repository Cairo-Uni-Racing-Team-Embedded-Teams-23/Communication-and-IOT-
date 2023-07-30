/**
 * @file NVIC_config.h
 * @author Hazem Montasser
 * @brief Configuration file for the NVIC driver.
 * @version 0.1
 * @date 2022-11-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/*******************************************************************************
 *                        Includes                                             *
 *******************************************************************************/

#include "NVIC_private.h"

/*******************************************************************************
 *                       Definitions                                           *
 *******************************************************************************/

/**
 * @brief Defines the vector table location
 *  Available values:
 *              NVIC_VECTOR_TABLE_CODE
 *              NVIC_VECTOR_TABLE_SRAM
 */
#define NVIC_VECTOR_TABLE_LOC (NVIC_VECTOR_TABLE_CODE)

/**
 * @brief Defines the vector table address offset
 * @note The address must be aligned to 128 bits, so
 *  the least significant 8 bits will be masked to
 *  be aligned correctly.
 */
#define NVIC_VECTOR_TABLE_OFFSET (0x00000000)