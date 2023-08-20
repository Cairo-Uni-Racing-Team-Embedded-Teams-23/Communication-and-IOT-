/**
 * @file CRC_source.c
 * @author Hazem Montasser (h4z3m.private@gmail.com)
 * @brief Source file for the CRC driver
 * @version 0.1
 * @date 2023-08-14
 *
 * @copyright Copyright (c) 2023
 *
 */

/*******************************************************************************
 *                              Includes                                       *
 *******************************************************************************/

#include "../../CURT_RCC/CURT_RCC_headers/RCC_private.h"
#include "../../LIB/BIT_MATH.h"
#include "../CURT_CRC_headers/CRC_interface.h"
#include "../CURT_CRC_headers/CRC_private.h"

/*******************************************************************************
 *                         Private Functions Prototypes                        *
 *******************************************************************************/

/**
 * @brief Reset the CRC registers to start a new calculation
 *
 */
static void CRC_reset();

/**
 * @fn uint32_t CRC_reverseWordBytes(uint32_t)
 * @brief Reversed the bytes in a single word
 *
 * @param word
 * @return	Reversed word
 */
static uint32_t CRC_reverseWordBytes(uint32_t word);

/*******************************************************************************
 *                         Private Functions                                   *
 *******************************************************************************/

static void CRC_reset() {
	/* Reset CRC */
	SET_BIT(CRC->CR, 0);
}
static uint32_t CRC_reverseWordBytes(uint32_t word) {
	uint8_t *bytePtr = (uint8_t*) &word;
	return (((uint32_t) bytePtr[0]) << 24) | (((uint32_t) bytePtr[1]) << 16)
			| (((uint32_t) bytePtr[2]) << 8) | ((uint32_t) bytePtr[3]);
}
/*******************************************************************************
 *                         Public Functions                                    *
 *******************************************************************************/

void CRC_init() {
	/* Start the CRC clock  */
	SET_BIT(RCC->AHBENR, 6);
	CRC_reset();
}

uint32_t CRC_calculate(uint32_t *a_data_in, uint32_t size) {
	CRC_reset();

	for (uint32_t i = 0; i < size; i++) {
		CRC->DR = CRC_reverseWordBytes(a_data_in[i]);
	}

	return (CRC->DR);
}
