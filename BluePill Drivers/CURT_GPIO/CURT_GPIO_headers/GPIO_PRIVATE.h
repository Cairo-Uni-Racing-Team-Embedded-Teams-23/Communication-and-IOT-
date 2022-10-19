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

#define GPIO_ALT_FUNCTION_BUS_ID (1U)
#define GPIOA_BUS_ID             (2U)
#define GPIOB_BUS_ID             (3U)
#define GPIOC_BUS_ID             (4U)
#define GPIOD_BUS_ID             (5U)
#define GPIOE_BUS_ID             (6U)

#endif