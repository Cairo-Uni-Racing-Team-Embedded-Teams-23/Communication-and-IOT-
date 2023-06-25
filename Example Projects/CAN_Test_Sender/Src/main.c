/**
 * @file main.c
 * @author Hazem Montasser	(h4z3m.private@gmail.com)
 * @brief CAN test project for sender side. It sends 10 messages, 2 of which will be invalid since the
 * receiver side only filters certain ID's:
 * 	0x7CD, 0x7BD, 0x792, 0x3C7A2, 0x299A2
 * @version 0.1
 * @date 2023-01-27
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "../BluePill Drivers/CURT_GPIO/CURT_GPIO_headers/GPIO_INTERFACE.h"
#include "../BluePill Drivers/CURT_RCC/CURT_RCC_headers/RCC_interface.h"
#include "../BluePill Drivers/CURT_Systick/CURT_Systick_headers/SYSTICK_INTERFACE.h"
#include "../BluePill Drivers/CURT_NVIC/CURT_NVIC_headers/NVIC_interface.h"
#include "../BluePill Drivers/CURT_CAN/CURT_CAN_headers/CAN_interface.h"

//extern void initialise_monitor_handles(void);

void dumb_delay() {
	for (int i = 0; i < 400000; i++)
		;
}

int main(void) {
	/* Init RCC */
	RCC_voidInitSysClock();

	/* Init GPIO Port A pin6 for output push-pull (2mhz)*/
	GPIO_enablePortClock(GPIO_PortC);
	GPIO_setupPinMode(GPIO_PortC, PIN13, OUTPUT_SPEED_2MHZ_PP);
	GPIO_setPinValue(GPIO_PortC, PIN13, 1);

	/* Init systick */
	STK_init();

	/* Init CAN & filter */
	CAN_init(CAN1, CAN_CONFIG_1);

	CAN_appendDeviceToBus(0x7CD, CAN_STANDARD_IDENTIFIER);
	CAN_appendDeviceToBus(0x7BD, CAN_STANDARD_IDENTIFIER);
	CAN_appendDeviceToBus(0x792, CAN_STANDARD_IDENTIFIER);
	CAN_appendDeviceToBus(0x3C7A2, CAN_EXTENDED_IDENTIFIER);
	CAN_appendDeviceToBus(0x299A2, CAN_EXTENDED_IDENTIFIER);

	CAN_setSlaveStartBank(14);

	u8 msg1[10] = "CURT";
	u8 msg2[10] = "Hello";
	u8 msg3[10] = "World";
	u8 msg4[10] = ":)";
	u8 invalid_msg[] = "This message will not arrive";
	/* For receiving data */
	CAN_setMode(CAN1, CAN_Mode_Normal);

	for (;;) {

		/*--------------------Standard identifier messages------------------*/

		CAN_sendMessage(msg1, 4, CAN_STANDARD_IDENTIFIER, 0x7CD);
		dumb_delay();

		CAN_sendMessage(msg2, 5, CAN_STANDARD_IDENTIFIER, 0x7BD);
		dumb_delay();

		//---------Invalid: Expected to fail
		CAN_sendMessage(invalid_msg, 8, CAN_STANDARD_IDENTIFIER, 0xabc);
		dumb_delay();

		CAN_sendMessage(msg3, 5, CAN_STANDARD_IDENTIFIER, 0x792);
		dumb_delay();

		CAN_sendMessage(msg4, 2, CAN_STANDARD_IDENTIFIER, 0x792);
		dumb_delay();

		//---------Invalid: Expected to fail
		CAN_sendMessage(invalid_msg, 8, CAN_STANDARD_IDENTIFIER, 0xFAC);
		dumb_delay();

		/*--------------------Extended identifier messages------------------*/

		//---------Invalid: Expected to fail
		CAN_sendMessage(invalid_msg, 8, CAN_EXTENDED_IDENTIFIER, 0xAFFC7B2);
		dumb_delay();

		CAN_sendMessage(msg1, 4, CAN_EXTENDED_IDENTIFIER, 0x3C7A2);
		dumb_delay();

		CAN_sendMessage(msg2, 5, CAN_EXTENDED_IDENTIFIER, 0x3C7A2);
		dumb_delay();

		CAN_sendMessage(msg3, 5, CAN_EXTENDED_IDENTIFIER, 0x299A2);
		dumb_delay();

		//---------Invalid: Expected to fail
		CAN_sendMessage(invalid_msg, 8, CAN_EXTENDED_IDENTIFIER, 0xAFF);
		dumb_delay();

		CAN_sendMessage(msg4, 2, CAN_EXTENDED_IDENTIFIER, 0x299A2);
		dumb_delay();

		while (1)
			;
	}
}

