#include "../BluePill Drivers/CURT_RCC/CURT_RCC_headers/RCC_interface.h"
#include "../BluePill Drivers/CURT_USART2/CURT_USART_headers/USART_interface.h"
#include "../BluePill Drivers/LIB/STD_TYPES.h"
#include "../BluePill Drivers/CURT_CAN/CURT_CAN_headers/CAN_interface.h"
void initCANPeriph() {
	/* Init CAN & filter */
	CAN_init(CAN1, CAN_CONFIG_1);
	CAN_appendDeviceToBus(0x6AC, CAN_STANDARD_IDENTIFIER);
	CAN_setSlaveStartBank(14);
	CAN_setMode(CAN1, CAN_Mode_Normal);
}
int main(void) {
	RCC_voidInitSysClock();
//	USART_Config_Typedef usart2_config = { .baud_rate = 9600, .cpha =
//			USART_CPHA_FIRST, .cpol = USART_CPOL_LOW, .parity =
//			USART_PARITY_NONE, .stop_bits = USART_STOPBITS_1, .word_length =
//			USART_WORDLENGTH_8BIT };
//	USART_init(USART2, &usart2_config);
	u8 arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
	/* Loop forever */
	for (;;) {
		CAN_sendMessage(arr, 8, CAN_STANDARD_IDENTIFIER, 0x6AC);
		for (int x = 0; x < 80000; x++)
			;
//		USART_sendChar(USART2, 'a');
//		for (int i = 0; i > 80000; i++)
//			;
//		USART_sendString(USART2, arr, sizeof(arr) / sizeof(arr[0]));
//		for (int i = 0; i > 80000; i++)
//			;

	}
}
