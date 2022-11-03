/******************************************************************************
 *
 * Module: SysTick Blink led example.
 * 			- Sets up system clock to external crystal clock
 * 			- Initializes Systick with max value 0x00FFFFFF
 *
 * File Name: .
 *
 * Description: file for
 *
 * Date Created:
 *
 * Author: Hazem Montasser
 *
 *******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"
#include "CURT_GPIO/CURT_GPIO_headers/GPIO_INTERFACE.h"
#include "CURT_RCC/CURT_RCC_headers/RCC_interface.h"
#include "CURT_Systick/CURT_Systick_headers/SYSTICK_INTERFACE.h"

int main() {

	RCC_voidInitSysClock();

	GPIO_enablePortClock(GPIO_PortA);
	GPIO_setupPinMode(GPIO_PortA,PIN6 ,OUTPUT_SPEED_2MHZ_PP);
	//RCC_configMCO(RCC_MCO_Src_SYSCLK);

	STK_init();
	// Infinite loop
	while (1) {

		GPIO_togglePinValue(GPIO_PortA, PIN6);
		/**
		 * Assuming FCPU  = 8MHz
		 * Fsystick = FCPU/8 = 1MHz
		 * Ttick = 1/1Mhz = 1us
		 * Ttimer = Max Value * Ttick = 2^24 * 10^-6 = 16.7s
		 *
		 *
		 */
		STK_setBusyWait(1);
	}
}
