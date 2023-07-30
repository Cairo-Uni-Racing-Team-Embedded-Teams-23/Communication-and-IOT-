/**
 * @file USART_config.h
 * @author Hazem Montasser (h4z3m.private@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-07-26
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef USART_CONFIG_H
#define USART_CONFIG_H

/*******************************************************************************
 *                              Includes                                       *
 *******************************************************************************/

#include "../../LIB/STD_TYPES.h"

/*******************************************************************************
 *                              Includes                                       *
 *******************************************************************************/

#ifdef USE_HAL_DRIVER
extern u32 SystemCoreClock;
#define F_CPU (SystemCoreClock)
#else
#include "../../CURT_RCC/CURT_RCC_headers/RCC_interface.h"
#define F_CPU (RCC_getSystemCoreClock())
#endif
#endif
