/**
 * @file main.c
 * @author Hazem Montasser	(h4z3m.private@gmail.com)
 * @author Abd El Rahman Assem
 * @brief  Main program for BMS CAN slave device.
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
#include "../BluePill Drivers/CURT_USART/CURT_USART_headers/USART_interface.h"

#define CAN_BUFF_SIZE (10UL)

// extern void initialise_monitor_handles(void);

void dumb_delay() {
  for (int i = 0; i < 300000; i++)
    ;
}

void toggle_led() {
  for (int i = 0; i < 5; i++) {
    GPIO_togglePinValue(GPIO_PortC, PIN13);
    dumb_delay();
  }
}
void initCorePeriph() {
  /* Init RCC */
  RCC_voidInitSysClock();

  /* Init systick */
  STK_init();
}

void initGPIOPeriph() {
  /* Init GPIO Port A pin6 for output push-pull (2mhz)*/
  GPIO_enablePortClock(GPIO_PortC);
  GPIO_setupPinMode(GPIO_PortC, PIN13, OUTPUT_SPEED_2MHZ_PP);
  GPIO_setPinValue(GPIO_PortC, PIN13, 1);
}

void initCANPeriph() {
  /* Init CAN & filter */
  CAN_init(CAN1, CAN_CONFIG_1);
  CAN_appendDeviceToBus(0x6AC, CAN_STANDARD_IDENTIFIER);
  CAN_setSlaveStartBank(14);
  CAN_setMode(CAN1, CAN_Mode_Normal);
}

void initUSART() {
  RCC_voidEnableClock(APB1, RCC_APB1_USART3EN);
  GPIO_enablePortClock(GPIO_PortB);
  GPIO_setupPinMode(GPIO_PortB, PIN10, OUTPUT_SPEED_50MHZ_AFPP);
  GPIO_setupPinMode(GPIO_PortB, PIN11, INPUT_PULLUP_PULLDOWN);
  MUSART_voidInit(USART3);
}

int main(void) {
  initCorePeriph();
  initGPIOPeriph();
  initCANPeriph();
  initUSART();
  /* For receiving data */
  u8 buff[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
  //	buff[CAN_BUFF_SIZE - 1] = '\0'; /* Null terminator for USART
  // sendString*/
  u8 len = 0;
  u32 devid = 0;

  //	initialise_monitor_handles();
  //	printf("[Receiver] Entering main loop...\n");
  for (;;) {

    while (CAN_receiveMessage(buff, &len, &devid) != CAN_Status_OK)
      ;

    toggle_led();
    for (int i = 0; i < 8; ++i) {
      MUSART_voidSendChar(USART3, buff[i]);
    }
    dumb_delay();
  }
}
