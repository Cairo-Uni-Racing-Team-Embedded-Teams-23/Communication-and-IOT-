/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "../BluePill Drivers/CURT_CAN/CURT_CAN_headers/CAN_interface.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "EVMS2.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

CAN_HandleTypeDef hcan;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_CAN_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_ADC1_Init();
	MX_USART2_UART_Init();
	MX_CAN_Init();
	/* USER CODE BEGIN 2 */
	HAL_ADCEx_Calibration_Start(&hadc1);
	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	HAL_CAN_Start(&hcan);
	CAN_RxHeaderTypeDef header = { 0 };
	unsigned char rx_data[8] = { 0 };
	//CAN_FilterTypeDef config_filter = {0, 0, 0, 0, CAN_RX_FIFO0, 0, CAN_FILTERMODE_IDMASK, CAN_FILTERSCALE_32BIT, ENABLE, 14};
	CAN_appendDeviceToBus(0x6AC, CAN_STANDARD_IDENTIFIER);
	unsigned char received_len = 0;
	//HAL_CAN_ConfigFilter(&hcan, &config_filter);
	while (1) {
		//HAL_GPIO_WritePin(GPIOC,USER_LED_Pin,GPIO_PIN_RESET);
//		if (HAL_CAN_GetRxMessage(&hcan, CAN_RX_FIFO0, &header, rx_data)
//				== HAL_OK) {
		if (CAN_receiveMessage(rx_data, &received_len, 0x6ac) == CAN_Status_OK)
//			int x = 23;
//			int y = 45;
			HAL_GPIO_WritePin(GPIOC, USER_LED_Pin, GPIO_PIN_RESET);
	}

	/* USER CODE END WHILE */

	/* USER CODE BEGIN 3 */
//		EVMS2_init();
//		LOGIC_voidControlBrakeLight();
//		LOGIC_voidControlFan();
//		LOGIC_voidControlPump();
//
//		if (isError() == ERROR) {
//			Error_Action();
//		} //end if
//		else {
//			//HAL_GPIO_WritePin(BRAKE_LIGHT_RELAY_GPIO_Port,BRAKE_LIGHT_RELAY_Pin,0);
//		} //end else
//}
/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };
RCC_PeriphCLKInitTypeDef PeriphClkInit = { 0 };

/** Initializes the CPU, AHB and APB busses clocks
 */
RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
RCC_OscInitStruct.HSEState = RCC_HSE_ON;
RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
RCC_OscInitStruct.HSIState = RCC_HSI_ON;
RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
	Error_Handler();
}
/** Initializes the CPU, AHB and APB busses clocks
 */
RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
		| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV8;

if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
	Error_Handler();
}
PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV8;
if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
	Error_Handler();
}
}

/**
 * @brief ADC1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_ADC1_Init(void) {

/* USER CODE BEGIN ADC1_Init 0 */

/* USER CODE END ADC1_Init 0 */

/* USER CODE BEGIN ADC1_Init 1 */

/* USER CODE END ADC1_Init 1 */
/** Common config
 */
hadc1.Instance = ADC1;
hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
hadc1.Init.ContinuousConvMode = DISABLE;
hadc1.Init.DiscontinuousConvMode = DISABLE;
hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
hadc1.Init.NbrOfConversion = 1;
if (HAL_ADC_Init(&hadc1) != HAL_OK) {
	Error_Handler();
}
/* USER CODE BEGIN ADC1_Init 2 */

/* USER CODE END ADC1_Init 2 */

}

/**
 * @brief CAN Initialization Function
 * @param None
 * @retval None
 */
static void MX_CAN_Init(void) {

/* USER CODE BEGIN CAN_Init 0 */

/* USER CODE END CAN_Init 0 */

/* USER CODE BEGIN CAN_Init 1 */

/* USER CODE END CAN_Init 1 */
hcan.Instance = CAN1;
hcan.Init.Prescaler = 16;
hcan.Init.Mode = CAN_MODE_NORMAL;
hcan.Init.SyncJumpWidth = CAN_SJW_1TQ;
hcan.Init.TimeSeg1 = CAN_BS1_12TQ;
hcan.Init.TimeSeg2 = CAN_BS2_5TQ;
hcan.Init.TimeTriggeredMode = DISABLE;
hcan.Init.AutoBusOff = DISABLE;
hcan.Init.AutoWakeUp = DISABLE;
hcan.Init.AutoRetransmission = DISABLE;
hcan.Init.ReceiveFifoLocked = DISABLE;
hcan.Init.TransmitFifoPriority = DISABLE;
if (HAL_CAN_Init(&hcan) != HAL_OK) {
	Error_Handler();
}
/* USER CODE BEGIN CAN_Init 2 */

/* USER CODE END CAN_Init 2 */

}

/**
 * @brief USART2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_USART2_UART_Init(void) {

/* USER CODE BEGIN USART2_Init 0 */

/* USER CODE END USART2_Init 0 */

/* USER CODE BEGIN USART2_Init 1 */

/* USER CODE END USART2_Init 1 */
huart2.Instance = USART2;
huart2.Init.BaudRate = 9600;
huart2.Init.WordLength = UART_WORDLENGTH_8B;
huart2.Init.StopBits = UART_STOPBITS_1;
huart2.Init.Parity = UART_PARITY_NONE;
huart2.Init.Mode = UART_MODE_TX_RX;
huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
huart2.Init.OverSampling = UART_OVERSAMPLING_16;
if (HAL_UART_Init(&huart2) != HAL_OK) {
	Error_Handler();
}
/* USER CODE BEGIN USART2_Init 2 */

/* USER CODE END USART2_Init 2 */

}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void) {
GPIO_InitTypeDef GPIO_InitStruct = { 0 };

/* GPIO Ports Clock Enable */
__HAL_RCC_GPIOC_CLK_ENABLE()
;
__HAL_RCC_GPIOD_CLK_ENABLE()
;
__HAL_RCC_GPIOA_CLK_ENABLE()
;
__HAL_RCC_GPIOB_CLK_ENABLE()
;

/*Configure GPIO pin Output Level */
HAL_GPIO_WritePin(USER_LED_GPIO_Port, USER_LED_Pin, GPIO_PIN_SET);

/*Configure GPIO pin Output Level */
HAL_GPIO_WritePin(GPIOA,
		BRAKE_LIGHT_RELAY_Pin | FAN_RELAY_Pin | PUMP_RELAY_Pin | EVMS_RELAY_Pin,
		GPIO_PIN_RESET);

/*Configure GPIO pin : USER_LED_Pin */
GPIO_InitStruct.Pin = USER_LED_Pin;
GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
GPIO_InitStruct.Pull = GPIO_NOPULL;
GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
HAL_GPIO_Init(USER_LED_GPIO_Port, &GPIO_InitStruct);

/*Configure GPIO pins : BSPD_FB_Pin BSPD_RELAY_FB_Pin IMD_FB_Pin IMD_RELAY_FB_Pin */
GPIO_InitStruct.Pin = BSPD_FB_Pin | BSPD_RELAY_FB_Pin | IMD_FB_Pin
		| IMD_RELAY_FB_Pin;
GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
GPIO_InitStruct.Pull = GPIO_NOPULL;
HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/*Configure GPIO pin : BMS_FB_Pin */
GPIO_InitStruct.Pin = BMS_FB_Pin;
GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
GPIO_InitStruct.Pull = GPIO_NOPULL;
HAL_GPIO_Init(BMS_FB_GPIO_Port, &GPIO_InitStruct);

/*Configure GPIO pins : BRAKE_LIGHT_RELAY_Pin FAN_RELAY_Pin PUMP_RELAY_Pin EVMS_RELAY_Pin */
GPIO_InitStruct.Pin = BRAKE_LIGHT_RELAY_Pin | FAN_RELAY_Pin | PUMP_RELAY_Pin
		| EVMS_RELAY_Pin;
GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
GPIO_InitStruct.Pull = GPIO_NOPULL;
GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
/* USER CODE BEGIN Error_Handler_Debug */
/* User can add his own implementation to report the HAL error return state */

/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
/* USER CODE BEGIN 6 */
/* User can add his own implementation to report the file name and line number,
 tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
/* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
