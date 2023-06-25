/******************************************************************************
 *
 * Module: SysTick Blink led example.
 * File Name: main.c
 *
 * Description:
 * 			- Sets up system clock to external crystal clock
 * 			- Initializes Systick with max value 0x00FFFFFF
 *			- Blinks the LED every 16.7s (if Fsystick=1MHz)
 *
 * Date Created: 6/11/2022
 *
 * Author: Hazem Montasser
 *******************************************************************************/

#include <stdint.h>

#include "../BluePill Drivers/CURT_GPIO/CURT_GPIO_headers/GPIO_INTERFACE.h"
#include "../BluePill Drivers/CURT_RCC/CURT_RCC_headers/RCC_interface.h"
#include "../BluePill Drivers/CURT_Systick/CURT_Systick_headers/SYSTICK_INTERFACE.h"
#include "../BluePill Drivers/CURT_NVIC/CURT_NVIC_headers/NVIC_interface.h"
#include "../BluePill Drivers/CURT_CAN/CURT_CAN_headers/CAN_interface.h"

int main() {

	RCC_voidInitSysClock();
	GPIO_enablePortClock(GPIO_PortC);
	GPIO_setupPinMode(GPIO_PortC, PIN13, OUTPUT_SPEED_2MHZ_PP);
	GPIO_setPinValue(GPIO_PortC, PIN13, 0);
	STK_init();
	// Infinite loop
	while (1) {

//		GPIO_togglePinValue(GPIO_PortC, PIN13);
		/**
		 * Assuming FCPU  = 8MHz
		 * Fsystick = FCPU/8 = 1MHz
		 * Ttick = 1/1Mhz = 1us
		 * Ttimer = Max Value * Ttick = 2^24 * 10^-6 = 16.7s
		 */
//		STK_setBusyWait(1);

	}
}
