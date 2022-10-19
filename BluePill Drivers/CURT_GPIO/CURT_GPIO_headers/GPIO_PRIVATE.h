/*************************************************************************************************
 * [MODULE_NAME]:  GPIO_PRIVATE.h
 *
 * [DATE CREATED]: Aug12, 2021
 *
 * [Author]:       Bassem Metwali
 *
 * [DESCRIPTION]:  Private file for GPIO which cannot be accessible by any USER
 ************************************************************************************************/
#ifndef GPIO_PRIVATE_H_
#define GPIO_PRIVATE_H_

#include "../../CURT_RCC/CURT_RCC_headers/RCC_interface.h"

#define GPIO_BUS                 (APB2)
#define GPIO_ALT_FUNCTION_BUS_ID (1)
#define GPIOA_BUS_ID             (2)
#define GPIOB_BUS_ID             (3)
#define GPIOC_BUS_ID             (4)
#define GPIOD_BUS_ID             (5)
#define GPIOE_BUS_ID             (6)

#define GPIOA_MAX_PINS (16)
#define GPIOB_MAX_PINS (16)
#define GPIOC_MAX_PINS (16)

#endif