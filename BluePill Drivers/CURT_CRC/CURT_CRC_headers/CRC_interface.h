/**
 * @file CRC_interface.h
 * @author Hazem Montasser (h4z3m.private@gmail.com)
 * @brief Header file for the CRC driver
 * @version 0.1
 * @date 2023-08-14
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef CRC_INTERFACE_H_
#define CRC_INTERFACE_H_

/*******************************************************************************
 *                              Includes                                       *
 *******************************************************************************/

#include <stdint.h>

/*******************************************************************************
 *                         Public functions prototypes                         *
 *******************************************************************************/

/**
 * @brief Initialize CRC and starts its clock
 *
 */
void CRC_init();

/**
 * @brief Calculate CRC from the input data
 *
 * @param a_data_in Input data to run CRC on
 * @param size      Size of the input data in words (uint32_t)
 * @return uint32_t CRC result
 */
uint32_t CRC_calculate(uint32_t *a_data_in, uint32_t size);

#endif
