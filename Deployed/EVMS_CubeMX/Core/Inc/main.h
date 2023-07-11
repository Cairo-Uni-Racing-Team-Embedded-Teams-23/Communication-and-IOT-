/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define USER_LED_Pin GPIO_PIN_13
#define USER_LED_GPIO_Port GPIOC
#define BRAKE_ANGLE_Pin GPIO_PIN_0
#define BRAKE_ANGLE_GPIO_Port GPIOA
#define BRAKE_PRESSURE_SENSE_Pin GPIO_PIN_1
#define BRAKE_PRESSURE_SENSE_GPIO_Port GPIOA
#define BSPD_FB_Pin GPIO_PIN_12
#define BSPD_FB_GPIO_Port GPIOB
#define BSPD_RELAY_FB_Pin GPIO_PIN_13
#define BSPD_RELAY_FB_GPIO_Port GPIOB
#define IMD_FB_Pin GPIO_PIN_14
#define IMD_FB_GPIO_Port GPIOB
#define IMD_RELAY_FB_Pin GPIO_PIN_15
#define IMD_RELAY_FB_GPIO_Port GPIOB
#define BMS_FB_Pin GPIO_PIN_8
#define BMS_FB_GPIO_Port GPIOA
#define BRAKE_LIGHT_RELAY_Pin GPIO_PIN_9
#define BRAKE_LIGHT_RELAY_GPIO_Port GPIOA
#define FAN_RELAY_Pin GPIO_PIN_10
#define FAN_RELAY_GPIO_Port GPIOA
#define PUMP_RELAY_Pin GPIO_PIN_11
#define PUMP_RELAY_GPIO_Port GPIOA
#define EVMS_RELAY_Pin GPIO_PIN_12
#define EVMS_RELAY_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
