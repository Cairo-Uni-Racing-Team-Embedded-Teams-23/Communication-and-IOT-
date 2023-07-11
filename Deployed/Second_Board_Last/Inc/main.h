/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#define BRAKES_PRESSURE_Pin GPIO_PIN_1
#define BRAKES_PRESSURE_GPIO_Port GPIOA
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
#define BREAKES_ANGLE_Pin GPIO_PIN_0
#define BREAKES_ANGLE_GPIO_Port GPIOA
#define BRAKES_PRESSURE_Pin GPIO_PIN_1
#define BRAKES_PRESSURE_GPIO_Port GPIOA
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

ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;
UART_HandleTypeDef huart2;

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
