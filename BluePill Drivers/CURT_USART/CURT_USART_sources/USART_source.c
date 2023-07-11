#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "../CURT_USART_headers/USART_interface.h"
#include "../CURT_USART_headers/USART_config.h"
#include "../CURT_USART_headers/USART_private.h"

u8 USART1_u8RxBuffer[20] = { 0 };
u8 USART1_u8Count = 0;
u8 USART2_u8RxBuffer[20] = { 0 };
u8 USART2_u8Count = 0;
u8 USART3_u8RxBuffer[20] = { 0 };
u8 USART3_u8Count = 0;

void MUSART_voidInit(USART_Regs *USARTx) {
	/* Calculate BRR value */
	u32 local_u32Mantissa = (F_CPU / (16 * USARTX_BAUD_RATE));
	u32 local_u32Fraction = ((F_CPU * 100 / (16 * USARTX_BAUD_RATE)) % 100)
			* 16;
	USARTx->BRR = (local_u32Mantissa << 4) | (local_u32Fraction / 100);

	/* Clear Status register */
	USARTx->SR = 0;

	/* Enable USART1
	 * Enable RX
	 * Enable TX
	 */
	SET_BIT(USARTx->CR1, 13);
	SET_BIT(USARTx->CR1, 2);
	SET_BIT(USARTx->CR1, 3);
	/* Enable RXNEIE */
	SET_BIT(USARTx->CR1, 5);

	/* Check for Parity */
#if (USARTX_PARITY == PARITY_DISABLE)
	{
		CLR_BIT(USARTx->CR1, 10);
	}
#elif (USARTX_PARITY == EVEN_PARITY)
	{
		SET_BIT(USARTx->CR1, 10);
		CLR_BIT(USARTx->CR1, 9);
	}
	#elif (USARTX_PARITY == ODD_PARITY)
	{
		SET_BIT(USARTx->CR1, 10);
		SET_BIT(USARTx->CR1, 9);
	}
	#endif

	/* Check for Data Length */
#if(DATA_LENGTH == DATA_LENGTH_8)
	{
		CLR_BIT(USARTx->CR1, 12);
	}
#elif(DATA_LENGTH == DATA_LENGTH_9)
	{
		SET_BIT(USARTx->CR1, 12);
	}
	#endif

	/* Check for Stop bits */
#if(STOP_BITS == ONE_STOP_BIT)
	{
		CLR_BIT(USARTx->CR2, 12);
		CLR_BIT(USARTx->CR2, 13);
	}
#elif(STOP_BITS == HALF_STOP_BIT)
	{
		SET_BIT(USARTx->CR2, 12);
		CLR_BIT(USARTx->CR2, 13);
	}
	#elif(STOP_BITS == TWO_STOP_BIT)
	{
		CLR_BIT(USARTx->CR2, 12);
		SET_BIT(USARTx->CR2, 13);
	}
	#elif(STOP_BITS == ONE_AND_HALF_STOP_BIT)
	{
		SET_BIT(USARTx->CR2, 12);
		SET_BIT(USARTx->CR2, 13);
	}
	#endif

	/* Baud rate 9600 ==> BRR 0x341= */
	//USART1->BRR = 0x341;
	/* Baud rate 115200 ==> BRR = 0x54 */

}

void MUSART_voidSendChar(USART_Regs *USARTx, u8 copy_u8Char) {
	USARTx->DR = copy_u8Char;
	while (!GET_BIT(USARTx->SR, 6))
		; /* Wait until transmission is complete */
	CLR_BIT(USARTx->SR, 6); /* Clear TC flag */
}

u8 MUSART_voidReceiveChar(USART_Regs *USARTx) {
	while (!GET_BIT(USARTx->SR, 5))
		; /* Wait until the Receiving is complete */
	/* Return the first 8 bits only of the data register */
	return ((USARTx->DR) & 0xFF);
}

void MUSART_voidSendString(USART_Regs *USARTx, const u8 *copy_u8String) {
	u8 local_u8Count = 0;
	while (copy_u8String[local_u8Count] != '\0') {
		MUSART_voidSendChar(USARTx, copy_u8String[local_u8Count]); /* Send Char */
		local_u8Count++;
	}
}

void MUSART_voidReceiveString(USART_Regs *USARTx, u8 *copy_u8String) {
	u8 local_u8Count = 0;
	copy_u8String[local_u8Count] = MUSART_voidReceiveChar(USARTx);
	/* Receive until '@' is pressed */
	while (copy_u8String[local_u8Count] != '@') {
		local_u8Count++;
		copy_u8String[local_u8Count] = MUSART_voidReceiveChar(USARTx);
	}
	copy_u8String[local_u8Count] = '\0';
}

u32 MUSART_u32ReceiveInteger(USART_Regs *USARTx, u8 *copy_u8String) {
	/* Get the Integer as an an array of characters (ASCII) */
	MUSART_voidReceiveString(USARTx, copy_u8String);
	/* Convert each element in the array into integer then form the entire number */
	u32 local_u32Result = 0;
	for (u8 i = 0; copy_u8String[i] != '\0'; i++) {
		local_u32Result = local_u32Result * 10 + (copy_u8String[i] - '0');
	}
	return local_u32Result;
}
