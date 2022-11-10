#include "NVIC_private.h"

/**
 * @brief Defines the vector table location
 *  Available values:
 *              NVIC_VECTOR_TABLE_CODE
 *              NVIC_VECTOR_TABLE_SRAM
 */
#define NVIC_VECTOR_TABLE_LOC  (NVIC_VECTOR_TABLE_CODE)

#define NVIC_VECTOR_TABLE_OFFSET    (0x00000000)