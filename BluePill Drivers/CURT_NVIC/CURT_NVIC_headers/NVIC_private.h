#include "../../LIB/STD_TYPES.h"

/**
 * @brief Defines the number of priority bits used in the STM32F10x MCU
 *
 */
#define NVIC_PRIORITY_BITS (4U)


#define NVIC_VECTOR_TABLE_CODE (1U)
#define NVIC_VECTOR_TABLE_SRAM (0U)


#define IS_NVIC_PRIORITY_GROUP(pri_g) (pri_g == 0U || pri_g == 1U || pri_g == 2U || pri_g == 3U)

#define SCB_VECTKEY (0x5FA)

#define SCB_AIRCR_VECTKEY_POS   (16U)
#define SCB_AIRCR_PRIGRP_POS    (8U)
