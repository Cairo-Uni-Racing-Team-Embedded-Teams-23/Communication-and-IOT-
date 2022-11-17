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
	/* Init RCC */
	RCC_voidInitSysClock();
	/* Init GPIO Port A pin6 for output push-pull (2mhz)*/
	GPIO_enablePortClock(GPIO_PortC);
	GPIO_setupPinMode(GPIO_PortC, PIN13, OUTPUT_SPEED_2MHZ_PP);
	GPIO_setPinValue(GPIO_PortC, PIN13, LOGIC_HIGH);

	/* Init systick */
	STK_init();

	/* Init CAN & filter */

	CAN_init(CAN1, CAN_CONFIG_1);

	CAN_appendDeviceToBus(0xBCD, CAN_EXTENDED_IDENTIFIER);
	CAN_appendDeviceToBus(0xFCD, CAN_EXTENDED_IDENTIFIER);
	CAN_appendDeviceToBus(0x992, CAN_EXTENDED_IDENTIFIER);
	CAN_appendDeviceToBus(0xAFFC7A2, CAN_STANDARD_IDENTIFIER);
	CAN_setSlaveStartBank(14);

	CAN_setMode(CAN1, CAN_Mode_Normal);
	u8 mydata[10] = "HelloCAN";
	u8 buff[8] = { 0 };
	u8 len = 0;
	u32 devid = 0;
	for (;;) {
		/* Invalid ID, expected to fail */
		CAN_sendMessage(mydata, 5, CAN_EXTENDED_IDENTIFIER, 0xCCB);
		CAN_receiveMessage(buff, &len, devid);
		buff[0] = 0;
		buff[1] = 0;
		buff[2] = 0;
		buff[3] = 0;
		buff[4] = 0;

		/* Valid ID, expected to go through */
		CAN_sendMessage(mydata, 5, CAN_EXTENDED_IDENTIFIER, 0xBCD);
		CAN_receiveMessage(buff, &len, devid);
		buff[0] = 0;
		buff[1] = 0;
		buff[2] = 0;
		buff[3] = 0;
		buff[4] = 0;
		/* Invalid ID, expected to fail */
		CAN_sendMessage(mydata, 5, CAN_EXTENDED_IDENTIFIER, 0xDDD);
		buff[0] = 0;
		buff[1] = 0;
		buff[2] = 0;
		buff[3] = 0;
		buff[4] = 0;

		/* Valid ID, expected to go through */
		CAN_sendMessage(mydata, 5, CAN_EXTENDED_IDENTIFIER, 0xFCD);
		CAN_receiveMessage(buff, &len, devid);
		buff[0] = 0;
		buff[1] = 0;
		buff[2] = 0;
		buff[3] = 0;
		buff[4] = 0;

		/* Valid ID, expected to go through */
		CAN_sendMessage(mydata, 5, CAN_EXTENDED_IDENTIFIER, 0x992);
		CAN_receiveMessage(buff, &len, devid);
		buff[0] = 0;
		buff[1] = 0;
		buff[2] = 0;
		buff[3] = 0;
		buff[4] = 0;
		/* Valid ID, expected to go through */
		CAN_sendMessage(mydata, 5, CAN_STANDARD_IDENTIFIER, 0x7A2);
		CAN_receiveMessage(buff, &len, devid);
		buff[0] = 0;
		buff[1] = 0;
		buff[2] = 0;
		buff[3] = 0;
		buff[4] = 0;

//		CAN_transmit(CAN1, &can_tx_msg);
//		for (int i = 0; i < 2000000; i++)
//			;
//		CAN_receive(CAN1, CAN_RX_FIFO_1, &can_rx_msg);
//		if (can_rx_msg.Data[0] == 'C' && can_rx_msg.Data[1] == 'U'
//				&& can_rx_msg.Data[2] == 'R' && can_rx_msg.Data[3] == 'T') {
//			GPIO_togglePinValue(GPIO_PortC, PIN13);
//			for (int i = 0; i < 2000000; ++i)
//				;
//			GPIO_togglePinValue(GPIO_PortC, PIN13);
//			for (int i = 0; i < 2000000; ++i)
//				;
//			can_rx_msg.Data[0] = 0;
//			can_rx_msg.Data[1] = 0;
//			can_rx_msg.Data[2] = 0;
//			can_rx_msg.Data[3] = 0;
//			can_rx_msg.Data[4] = 0;
//
//		}
//		can_tx_msg.StdId = std_filter_id;

	}
}
