/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>

#include "../BluePill Drivers/CURT_GPIO/CURT_GPIO_headers/GPIO_INTERFACE.h"
#include "../BluePill Drivers/CURT_RCC/CURT_RCC_headers/RCC_interface.h"
#include "../BluePill Drivers/CURT_Systick/CURT_Systick_headers/SYSTICK_INTERFACE.h"
#include "../BluePill Drivers/CURT_NVIC/CURT_NVIC_headers/NVIC_interface.h"
#include "../BluePill Drivers/CURT_CAN/CURT_CAN_headers/CAN_interface.h"
#define CAN_FILTER_MASK
int main(void) {

	/** No filter **/
#ifdef CAN_NO_FILTERS
	can_filter.FilterIdLowR1 = 0;
	can_filter.FilterIdHighR1 = 0;
	can_filter.FilterIdLowR2 = 0;
	can_filter.FilterIdHighR2 = 0;

	can_filter.FilterMaskIdHigh = 0;
	can_filter.FilterMaskIdLow = 0

	can_filter.FilterFIFOAssignment = 0;
	can_filter.FilterNumber = 0;
	can_filter.FilterMode = MASK;
	can_filter.FilterScale = SINGLE_32;
	can_filter.FilterActivation = 1;
	CAN_init(CAN1, CAN_CONFIG_1);
	CAN_initFilter(&can_filter);
	CAN_setSlaveStartBank(14);

#endif

#ifdef CAN_FILTER_MASK
	/* Init RCC */
	//RCC_voidInitSysClock();

	/* Init GPIO Port A pin6 for output push-pull (2mhz)*/
	GPIO_enablePortClock(GPIO_PortA);
	GPIO_setupPinMode(GPIO_PortA, PIN6, OUTPUT_SPEED_2MHZ_PP);
	GPIO_setPinValue(GPIO_PortA, PIN6, LOGIC_LOW);

	/* Init systick */
	STK_init();

	/* Init CAN & filter */
	CAN_FilterInitTypeDef can_filter = { 0 };
	CanRxMsg can_rx_msg = { 0 };

	u32 ext_filter_id = 0xBD;
	u16 std_filter_id = 0x3AF;

	u32 filter_mask = 0;
	can_filter.FilterIdLowR1 = 0xFFFF;
	can_filter.FilterIdHighR1 = 0xFFFF;

	can_filter.FilterIdLowR2 = 0xFFFF;
	can_filter.FilterIdHighR2 = 0xFFFF;

	//	can_filter.FilterIdLowR1 = 0;
	//	can_filter.FilterIdHighR1 = (std_filter_id <<5);

	//	can_filter.FilterIdLowR2 =  0;
	//	can_filter.FilterIdHighR2 = (std_filter_id <<5);

	can_filter.FilterMaskIdHigh = 0;
	// Check all bits EXCEPT first 2 (RTR, 0 bit)
	can_filter.FilterMaskIdLow = 0;

	//can_filter.FilterMaskIdHigh =0xFFE0;
	//can_filter.FilterMaskIdLow  = 0;

	can_filter.FilterFIFOAssignment = 0;

	can_filter.FilterNumber = 0;
	can_filter.FilterMode = LIST;
	can_filter.FilterScale = SINGLE_32;
	can_filter.FilterActivation = 1;
	CAN_init(CAN1, CAN_CONFIG_1);
	CAN_initFilter(&can_filter);
	CAN_setSlaveStartBank(14);
	/* Create new message 'CURT' DLC = 4*/
	CanTxMsg can_tx_msg = { 0 };
	can_tx_msg.Data[0] = 'C';
	can_tx_msg.Data[1] = 'U';
	can_tx_msg.Data[2] = 'R';
	can_tx_msg.Data[3] = 'T';
	can_tx_msg.DLC = 4;
	can_tx_msg.IDE = CAN_STANDARD_IDENTIFIER;
	can_tx_msg.RTR = 0;
	can_tx_msg.StdId = 0xF0;

	CAN1->MCR &= ~(1 << INRQ);
#endif

	for (;;) {
		CAN_transmit(CAN1, &can_tx_msg);
		for(int i = 0;i<200000;i++);
		CAN_receive(CAN1, CAN_RX_FIFO_1, &can_rx_msg);
		if (can_rx_msg.Data[0] == 'C' && can_rx_msg.Data[1] == 'U'
				&& can_rx_msg.Data[2] == 'R' && can_rx_msg.Data[3] == 'T') {
			GPIO_togglePinValue(GPIO_PortC, PIN13);
			for (int i = 0; i < 2000000; ++i)
				;
			GPIO_togglePinValue(GPIO_PortC, PIN13);
			for (int i = 0; i < 2000000; ++i)
				;
			can_rx_msg.Data[0] = 0;
			can_rx_msg.Data[1] = 0;
			can_rx_msg.Data[2] = 0;
			can_rx_msg.Data[3] = 0;
			can_rx_msg.Data[4] = 0;

		}
	}
}