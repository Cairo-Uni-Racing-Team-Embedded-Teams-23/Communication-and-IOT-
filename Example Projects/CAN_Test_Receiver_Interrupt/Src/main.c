/**
 * @file main.c
 * @author Hazem Montasser	(h4z3m.private@gmail.com)
 * @brief CAN test project for receiver side. For each message received, the user LED on the bluepill
 * flashes once. Per sender project configuration, the LED should flash 8 times.
 * @version 0.1
 * @date 2023-01-27
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../BluePill Drivers/CURT_CAN/CURT_CAN_headers/CAN_interface.h"
#include "../BluePill Drivers/CURT_GPIO/CURT_GPIO_headers/GPIO_INTERFACE.h"
#include "../BluePill Drivers/CURT_NVIC/CURT_NVIC_headers/NVIC_interface.h"
#include "../BluePill Drivers/CURT_RCC/CURT_RCC_headers/RCC_interface.h"
#include "../BluePill Drivers/CURT_Systick/CURT_Systick_headers/SYSTICK_INTERFACE.h"

// extern void initialise_monitor_handles(void);

void dumb_delay() {
	for (int i = 0; i < 300000; i++)
		;
}

void toggle_led() {
	GPIO_togglePinValue(GPIO_PortC, PIN13);
	dumb_delay();
	GPIO_togglePinValue(GPIO_PortC, PIN13);
}

void CAN_handler() {

	toggle_led();

}

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

	CAN_appendDeviceToBus(0x7BD, CAN_STANDARD_IDENTIFIER);
	CAN_appendDeviceToBus(0x7CD, CAN_STANDARD_IDENTIFIER);
	CAN_appendDeviceToBus(0x792, CAN_STANDARD_IDENTIFIER);
	CAN_appendDeviceToBus(0x3C7A2, CAN_EXTENDED_IDENTIFIER);
	CAN_appendDeviceToBus(0x299A2, CAN_EXTENDED_IDENTIFIER);

	CAN_setSlaveStartBank(14);

	/* For receiving data */
	u8 buff[8] = {5 };
	u8 len = 0;
	u32 devid = 2;

	CAN_setMode(CAN1, CAN_Mode_Normal);
	CAN_receiveMessage_Interrupt(&buff, &len, &devid);
	CAN_attachCallback(CAN_Interrupt_FIFO0, CAN_handler);
	CAN_activateInterrupt(CAN1,CAN_Interrupt_FIFO0);
	//	initialise_monitor_handles();
	//	printf("[Receiver] Entering main loop...\n");
	for (;;) {
	}
}
